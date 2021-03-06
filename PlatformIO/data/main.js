var pump_on = false;

function begin(){
    document.querySelector("#soil-text .bottom-row #pump-switch").addEventListener('change', () =>{
        pump_on = !pump_on;
        set_pump();
        set_plant();
    });

    update();
}

// Function to update the data onscreen
function update(){
    var oReq = new XMLHttpRequest();
    oReq.addEventListener("load", receive);
    oReq.open("GET", "/data");
    oReq.send();

    setTimeout(update, 2000); // Update again in half a second
}

function set_plant(){
    if(pump_on){
        document.querySelector("#soil-humidity .icon-box img#pump-on").classList.remove("hidden");
        document.querySelector("#soil-humidity .icon-box img#pump-off").classList.add("hidden");
    }
    else{
        document.querySelector("#soil-humidity .icon-box img#pump-on").classList.add("hidden");
        document.querySelector("#soil-humidity .icon-box img#pump-off").classList.remove("hidden");
    }
}

// Method to set the pump state
function set_pump(){
    var oReq = new XMLHttpRequest();
    var params = `pump_on=${pump_on}`;

    oReq.open("POST", "/set_pump", true);
    oReq.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    oReq.send(params);
}

// Function to receive data from the previously made GET request
function receive () {
    data = JSON.parse(this.responseText);

    console.log(data);

    document.querySelector("#temp-text > span").innerHTML = data.temp;
    document.querySelector("#humidity-text > span").innerHTML = data.humidity;
    document.querySelector("#soil-text .top-row > span").innerHTML = data.soil_moist;
    pump_on = data.pump_on;
    document.querySelector("#soil-text .bottom-row #pump-switch").checked = data.pump_on;
    document.querySelector("#wind-text .top-row > span").innerHTML = data.wind_speed;
    document.querySelector("#wind-text .bottom-row > span").innerHTML = data.wind_dir;

    set_plant();
}

// On window load, run the begin method
window.onload = begin;