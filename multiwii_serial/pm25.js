
var SerialPort = require("serialport").SerialPort

//var serialPort = new SerialPort("/dev/tty.song-DevB", {
//var serialPort = new SerialPort("/dev/tty.Bluetooth-Incoming-Port", {
var serialPort = new SerialPort("/dev/tty.usbmodem1421", {
    //baudrate:115200
    baudrate:9600
});

var fs = require('fs');
var stream = fs.createWriteStream("pm001.txt");
var str="---time:"+(new Date()).getTime()+"---";
    stream.write(str);
stream.once('open', function(fd) {
  serialPort.open(function () {
    var _headString="";
    var buf;
    var count=0;
    var datalength;
    serialPort.on('data', function(data) {
      s=data.toString();
      console.log(s);
        stream.write(s);
      //    stream.end();
      });
  });
});


