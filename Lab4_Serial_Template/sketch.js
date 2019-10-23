/*
This P5 sketch is a template for getting started with Serial Communication. 
The SerialEvent callback is where incoming data is received 


By Arielle Hein, adapted from ITP Phys Comp Serial Labs
Edited March 12 2019

*/


var serial; //variable to hold an instance of the serial port library
var portName = '/dev/cu.usbmodem14101'; //fill in with YOUR port
var greencircleSize = 0;
var bluecircleSize = 0;
var potInput = 0;
var forceInput = 0;

var x, y;
var score = 0;
const radius = 100;
var r, g, b;

function setup() {
  createCanvas(windowWidth, windowHeight);
  serial = new p5.SerialPort(); //a new instance of serial port library
  
  //list of ports
  // serial.on('list', printList); //set a callback function for the serialport list event
  // serial.list(); //list the serial ports

  //set up events for serial communication
  serial.on('connected', serverConnected);
  serial.on('open', portOpen);
  serial.on('data', serialEvent);
  serial.on('error', serialError);
  serial.on('close', portClose);

  //open our serial port
  serial.open(portName);
  
  //set up for game
  x = random(windowWidth);
  y = random(windowHeight);
  r = random(255);
  g = random(255);
  b = random(255);
}


function draw() {
  background("white");
  noStroke();
  fill(r, g, b);
  ellipse(x, y, bluecircleSize, bluecircleSize);
  fill("black");
  textSize(24);
  text("Score: " + score, windowWidth - 150, windowHeight - 30);
}

function mousePressed() {
  var d = dist(mouseX, mouseY, x, y);
  if (d < radius) {
    score++;
    newCircle();
  }
  if (score >= 10){
    textSize(48);
    text("You Won!", 10,50);
    serial.write('B');
    noLoop();
  }
}

function newCircle() {
  if (forceInput > 50){
    r = random(255);
    g = random(255);
    b = random(255);
  }
  x = random(windowWidth);
  y = random(windowHeight);
}
setInterval(newCircle, 1000);


// Part 2: interface that visualizes arduino circuit
// function draw() {
//   background("plum");
  
// //   changes w/Pot values (green LED)
//   ellipse(250, height/2, 20 + greencircleSize, 20 + greencircleSize);
//   fill("green");
//   noStroke();

// //   changes w/force sensor values (blue LED)
//   ellipse(50, height/2, 20 + bluecircleSize, 20 + bluecircleSize);
//   fill("blue");
//   noStroke();
// }

// Part 2: data sent to arduino for mouse click = LED on
// function mouseClicked()
// {
//   if(mouseX > 100){
//   	serial.write('H');
//   }
//   if(mouseX < 100){
//   	serial.write('L');
//   }
// }


//all my callback functions are down here:
//these are useful for giving feedback

function serverConnected(){
	console.log('connected to the server');
}

function portOpen(){
  console.log('the serial port opened!');
}

//THIS IS WHERE WE RECEIVE DATA!!!!!!
//make sure you're reading data based on how you're sending from arduino
function serialEvent(){
  //receive serial data here  
  var data = serial.readLine();
  if (data.length > 0){
    // console.log(data);
    var sensors = split(data, ",");
    if (sensors.length > 2){
      bluecircleSize = int(sensors[1]);
      potInput = int(sensors[0]);
      greencircleSize = int(sensors[3]);
      forceInput = int(sensors[2]);
    }
  }
}

function serialError(err){
  console.log('something went wrong with the port. ' + err);
}

function portClose(){
  console.log('the port was closed');
}

// get the list of ports:
function printList(portList) {
   // portList is an array of serial port names
   for (var i = 0; i < portList.length; i++) 
   {
     // Display the list the console:
     print(i + " " + portList[i]);
   }
}