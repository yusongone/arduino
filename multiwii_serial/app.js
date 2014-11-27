
var SerialPort = require("serialport").SerialPort

//var serialPort = new SerialPort("/dev/tty.song-DevB", {
var serialPort = new SerialPort("/dev/tty.usbmodem1411", {
    baudrate: 115200
});


serialPort.open(function () {
  console.log('open');

  serialPort.on('data', function(data) {
    var d=data.toString("ascii");
    console.log("data",d);
    console.log('data received: ' + data);
  });

 // var hex_command=getCommand("$ M > 100 ");
  var hex_command=new Buffer([0x24,0x4D,0x3C,0x00,0x64,0x64]);
  console.log(hex_command);
  serialPort.write(hex_command, function(err, results) {
    console.log('err ' + err);
    console.log('results ' + results);
  });
});

function getCommand(str){
  var buf=new Buffer(str.length);
 for(var i=0;i<str.length;i++){
   buf.fill(str[i],i,i+1);
 } 
 return buf;
}
