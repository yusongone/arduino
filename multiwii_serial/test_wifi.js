
var SerialPort = require("serialport").SerialPort

//var serialPort = new SerialPort("/dev/tty.song-DevB", {
//var serialPort = new SerialPort("/dev/tty.Bluetooth-Incoming-Port", {
//var serialPort = new SerialPort("/dev/tty.usbmodem1411", {
var serialPort = new SerialPort("/dev/tty.usbserial-A9MH5RRR", {
  //  baudrate:115200
    //baudrate:57600
    baudrate:9600
});

  serialPort.open(function () {
    var _headString="";
    var buf;
    var count=0;
    var datalength;
    var s="";
    serialPort.on('data', function(data) {
       s+=data;
        console.log(data);
        //stream.write(s);
      //    stream.end();
     });
    setTimeout(function(){
      serialPort.write("AT+CIFSR=?\n",function(err,res){});
    },1000);
  });


