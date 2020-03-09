// Function to update the data onscreen
function update(){
    var oReq = new XMLHttpRequest();
    oReq.addEventListener("load", receive);
    oReq.open("GET", "/data");
    oReq.send();
}

// Function to receive data from the previously made GET request
function receive () {
    data = JSON.parse(this.responseText);

    console.log(data);

    document.querySelector("#temp-text > span").innerHTML = data.temp;
    document.querySelector("#humidity-text > span").innerHTML = data.humidity;
    document.querySelector("#soil-text > span").innerHTML = data.soil_moist;
    document.querySelector("#soil-text > span").innerHTML = data.pump_on ? "ON" : "OFF";

    setTimeout(update, 1000); // Update again in half a second
}

// On window load, run the update function
window.onload = update;