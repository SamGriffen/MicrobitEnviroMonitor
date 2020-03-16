/**
 * Code for Microbit based Environmental Monitoring station.
 * 
 * Data is received via serial, in the following format:
 * [temperature, in... centidegrees? Divide value by 100 to get degrees celsius], [humidity, divide by 1024 to get % relative humidity], [soil moisture. 0-1023, 0 being dry, 1023 being wet], [wind speed in m/s], [wind direction string], [mm of rain]
 * 
 * TODO: Make SOIL_DRY adjustable without reprogramming. This poses a security risk, so will need to be secure and able to detect misuse (Such as leaving the pump on indefinitely)
 * TODO: Handle rain gauge
 */

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

// #define DEBUG

// Define the point at which the soil is defined as "dry". Any value below this will activate the pump
// TODO: Make this editable via the frontend interface
#define SOIL_DRY 600

// Define pump output, and pump state flag
#define PUMP_PIN 5
bool pump_on = false; // Pump state. True = on, false = off


#define PUMP_BUTTON 18 // For attaching a pump activate button. When pressed, the pump will activate for roughly a minute.


// Network credentials
const char* ssid = "Rosa";
const char* password = "denbigh05";

// Struct for storing current reading data
struct Data{
  double temp; // Temperature in degrees celsius
  double humidity; // Relative humidity [%]
  int soil_moist; // Soil moisture. A reading between 0 and 1024. This needs to be manually read and tuned, it doesn't really mean a whole lot
  double wind_speed; // Wind speed in meters per second
  char wind_dir[3];  // Wind direction, string containing "N", "NE", "E", "SE", "S" "SW", "W", or "NW"
  double rain;  // mm of rainfall since last reading was sent
} data;

#ifdef DEBUG
// If there is debugging enabled, declare a function for printing the data read
void printData(Data dat){
  Serial.print("Temperature: ");Serial.println(dat.temp);
  Serial.print("Humidity: ");Serial.println(dat.humidity);
  Serial.print("Soil Moisture: ");Serial.println(dat.soil_moist);
  Serial.print("Wind Speed ");Serial.println(dat.wind_speed);
  Serial.print("Wind Direction: ");Serial.println(dat.wind_dir);
  Serial.print("Last Hour of Rain: ");Serial.println();
}
#endif

char buffer[32]; // Buffer for storing incoming serial data for processing

bool reading = false; // Represents whether serial data is currently being read
int buf_cur = 0; // Current position in buffer

// Methods for handling Serial data
void incoming();
void processBuffer();

/* NETWORK SETUP */

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Method for processing HTML templates
String processor(const String& var);

// Configure the pump button interrupt routine
unsigned long press_length = 60000; // When the button is pressed, leave the pump on for a minute
unsigned long press_time = 0;
bool pressed = false;

void IRAM_ATTR ISR(){
  pump_on = true;
  press_time = millis();
  pressed = true;
}

void setup() {
  pinMode(PUMP_BUTTON, INPUT_PULLUP); // Set the pump input button as a pulup input

  attachInterrupt(PUMP_BUTTON, ISR, FALLING);

  Serial.begin(9600);

  Serial2.begin(9600); // Initialise Serial communication with the microbit

  // Initialise the pump
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, pump_on);

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
    char buf[256];
    memset(buf, 0, 256);

    // Convert all floats to strings
    char temp[6];
    dtostrf(data.temp, 4,1, temp);

    char humidity[6];
    dtostrf(data.humidity, 3,1, humidity);

    char wind[5];
    dtostrf(data.wind_speed, 4, 2, wind);

    sprintf(buf, "{\"temp\":%s, \"humidity\":%s, \"soil_moist\":%d, \"wind_speed\":%s, \"wind_dir\":\"%s\", \"pump_on\":%d}", temp, humidity, data.soil_moist, wind, data.wind_dir, pump_on);

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
  
  server.on("/plant.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/plant.svg","image/svg+xml");
  });

  server.on("/plant_water.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/plant_water.svg","image/svg+xml");
  });

  server.on("/wind.svg", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS,"/wind.svg"
    ,"image/svg+xml");
  });

  // Serve JavaScript file
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/main.js","text/javascript");
  });

  // Admin interface - Crudely password protected by ADMIN_PASS
  server.begin();
}

void loop() {
  if(Serial2.available() > 0){ // Handle incoming Serial
    incoming();
  }

  // if(millis()%1000 == 0){
  //   pump_on = random(10) > 5;
  //   digitalWrite(PUMP_PIN, pump_on);
  // }

  // Control the pump, only if the pump button has not been activated
  if(!pressed){
    if(data.soil_moist <= SOIL_DRY){
      pump_on = true;
    }
    else {
      pump_on = false;
    }
  }

  // If the button timeout has been reached, turn off pump
  if(pressed && (millis() - press_time > press_length)){
    pressed = false;
    pump_on = false;
  }

  digitalWrite(PUMP_PIN, pump_on); // Set the pump output
}

/**
 * Process the HTML template, replacing variables with data from the microbit
 */
String processor(const String& var){
  if(var == "TEMP")return String(data.temp, 1);
  if(var == "HUMIDITY")return String(data.humidity, 1);
  if(var == "SOIL")return String(data.soil_moist, 1);
  if(var == "PUMP")return String(pump_on ? "ON" : "OFF");
  if(var == "WIND_SPEED")return String(data.wind_speed, 1);
  if(var == "WIND_DIR")return String(data.wind_dir);
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

  data.soil_moist = atoi(tok); // Read soil moisture content

  #ifdef DEBUG
  Serial.println("Reading wind speed");
  #endif
  tok = strtok(NULL, ","); // Get the fourth token

  if(tok == NULL)return; // Could not read wind speed

  data.wind_speed = atoi(tok); // Read wind speed

  #ifdef DEBUG
  Serial.println("Reading wind direction");
  #endif
  tok = strtok(NULL, ","); // Get the fifth token

  if(tok == NULL)return; // Could not read  wind direction

  strcpy(data.wind_dir, tok); // Read wind direction

  #ifdef DEBUG
  Serial.println("Reading rainfall");
  #endif
  tok = strtok(NULL, ","); // Get the sixth token

  if(tok == NULL)return; // Could not read wind speed

  data.rain = atoi(tok); // Read rainfall

  #ifdef DEBUG
  printData(data);
  #endif
}