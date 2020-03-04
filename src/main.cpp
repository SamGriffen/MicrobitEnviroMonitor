/**
 * Code for Microbit based Environmental Monitoring station.
 * 
 * Data is received via serial, in the following format:
 * [temperature, in... centidegrees? Divide value by 100 to get degrees celsius], [humidity, divide by 1024 to get % relative humidity], [soil moisture. 0-1023, 0 being dry, 1023 being wet]
 * 
 * TODO: Make values autorefresh. This will need to be some really dodgy, fast JS
 */

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#define DEBUG

// Struct for storing current reading data
struct Data{
  double temp;
  double humidity;
  double soil_moist;
} data;

#ifdef DEBUG
// If there is debugging enabled, declare a function for printing the data read
void printData(Data dat){
  Serial.print("Temperature: ");Serial.println(dat.temp);
  Serial.print("Humidity: ");Serial.println(dat.humidity);
  Serial.print("Soil Moisture: ");Serial.println(dat.soil_moist);

}
#endif

char buffer[32]; // Buffer for storing incoming serial data for processing

bool reading = false; // Represents whether serial data is currently being read
int buf_cur = 0; // Current position in buffer

// Methods for handling Serial data
void incoming();
void processBuffer();

/* NETWORK SETUP */
// Network credentials
const char* ssid = "Rosa";
const char* password = "denbigh05";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Method for processing HTML templates
String processor(const String& var);

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  Serial2.begin(9600); // Initialise Serial communication with the microbit

  if(!SPIFFS.begin(true)){ // Attempt to initialise SPIFFS
    #ifdef DEBUG
    Serial.println("SPIFFS could not be initialised.");
    #endif
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    #ifdef DEBUG
    Serial.println("Connecting to WiFi..");
    #endif
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Configure all the routes on the HTTP server

  // Serve basic webpage
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Serve request for page data
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    char buf[64];

    // Convert all floats to strings
    char temp[6];
    dtostrf(data.temp, 4,1, temp);

    char humidity[6];
    dtostrf(data.humidity, 3,1, humidity);

    char soil[6];
    dtostrf(data.soil_moist, 3,1, soil);


    sprintf(buf, "{temp:%s, humidity:%s, soil_moist:%s}", temp, humidity, soil);
    request->send(200, "application/json", buf);
  });

  // Serve stylesheet
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css","text/css");
  });

  // Serve SVG images
  server.on("/drop.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/drop.svg","image/svg+xml");
  });

  server.on("/temp.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/temp.svg","image/svg+xml");
  });

  // Serve JavaScript file
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/main.js","text/javascript");
  });

  server.begin();
}

void loop() {
  if(Serial2.available() > 0){ // Handle incoming Serial
    incoming();
  }
}

/**
 * Process the HTML template, replacing variables with data from the microbit
 */
String processor(const String& var){
  if(var == "TEMP")return String(data.temp, 1);
  if(var == "HUMIDITY")return String(data.humidity, 1);
  if(var == "SOIL")return String(data.soil_moist, 1);
  return String();
}

/**
 * Process an incoming character on Serial
 */
void incoming(){
  char c = Serial2.read(); // Read the next serial character

    if(reading){
      buffer[buf_cur] = c;
      buf_cur++;
    }

    if(c == '\n' && !reading){
      reading = true; // if serial is not currently being read, start reading it
      #ifdef DEBUG
      Serial.println("Started reading");
      #endif
    }

    else if(c == '\n' && reading){ // end of a data string
      #ifdef DEBUG
      Serial.println("Finished reading. Read:");
      Serial.println(buffer);
      #endif
      buffer[buf_cur] = '\0'; // Null terminate the buffer
      reading = false;
      buf_cur = 0; // reset reading flag, and buffer counter
      processBuffer(); // Process the data that was read
    }
}

/**
 * Process the data buffer, extracting the data into the 'data' struct
 */
void processBuffer(){
  #ifdef DEBUG
  Serial.println("Reading temperature");
  #endif
  char * tok = strtok(buffer, ","); // Get the first token

  if(tok == NULL)return; // Could not read temperature

  data.temp = (double)atoi(tok)/100.0; // Get the temperature

  #ifdef DEBUG
  Serial.println("Reading humidity");
  #endif
  tok = strtok(NULL, ","); // Get the second token

  if(tok == NULL)return; // Could not read humidity

  data.humidity = (double)atoi(tok)/1024.0; // Get the humidity

  #ifdef DEBUG
  Serial.println("Reading soil moisture");
  #endif
  tok = strtok(NULL, ","); // Get the third token

  if(tok == NULL)return; // Could not read soil moisture

  data.soil_moist = atoi(tok)/1024.0; // Get the soil moisture

  #ifdef DEBUG
  printData(data);
  #endif
}