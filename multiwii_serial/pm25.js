
var SerialPort = require("serialport").SerialPort

var serialPort = new SerialPort("/dev/tty.song-DevB", {
//var serialPort = new SerialPort("/dev/tty.Bluetooth-Incoming-Port", {
//var serialPort = new SerialPort("/dev/tty.usbmodem1411", {
    baudrate:115200
});

var fs = require('fs');
var stream = fs.createWriteStream("my_file2.txt");
stream.once('open', function(fd) {
  serialPort.open(function () {
    var _headString="";
    var buf;
    var count=0;
    var datalength;
    serialPort.on('data', function(data) {
      var s=data.toString();
      console.log(s);
        stream.write(s);
      //    stream.end();
      });
  });
});


