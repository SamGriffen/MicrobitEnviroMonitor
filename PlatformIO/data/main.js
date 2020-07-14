// Function to update the data onscreen
function update(){
    var oReq = new XMLHttpRequest();
    oReq.addEventListener("load", receive);
    oReq.open("GET", "/data");
    oReq.send();

    setTimeout(update, 2000); // Update again in half a second
}

// Function to receive data from the previously made GET request
function receive () {
    data = JSON.parse(this.responseText);

    console.log(data);

    document.querySelector("#temp-text > span").innerHTML = data.temp;
    document.querySelector("#humidity-text > span").innerHTML = data.humidity;
    document.querySelector("#soil-text .top-row > span").innerHTML = data.soil_moist;
    document.querySelector("#soil-text .bottom-row > span").innerHTML = data.pump_on ? "ON" : "OFF";
    document.querySelector("#wind-text .top-row > span").innerHTML = data.wind_speed;
    document.querySelector("#wind-text .bottom-row > span").innerHTML = data.wind_dir;

    if(data.pump_on){
        document.querySelector("#soil-humidity .icon-box img#pump-on").classList.remove("hidden");
        document.querySelector("#soil-humidity .icon-box img#pump-off").classList.add("hidden");
    }
    else{
        document.querySelector("#soil-humidity .icon-box img#pump-on").classList.add("hidden");
        document.querySelector("#soil-humidity .icon-box img#pump-off").classList.remove("hidden");
    }
}

// On window load, run the update function
window.onload = update;