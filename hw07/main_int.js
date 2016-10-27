var b = require('bonescript');
var inputPin = 'P9_28';
var outputPin = 'P9_27';
b.pinMode(inputPin, b.INPUT);
b.pinMode(outputPin, b.OUTPUT);

b.attachInterrupt(inputPin, true, b.CHANGE, interruptCallback);
setTimeout(detach, 120000);

function interruptCallback(x) {
    //console.log(JSON.stringify(x));
    b.digitalWrite(outputPin, b.digitalRead(inputPin));
    console.log("callback handler"+b.digitalRead(inputPin));
}

function detach() {
    b.detachInterrupt(inputPin);
    console.log('Interrupt detached');
}