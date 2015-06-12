var fs=require("fs");
var SerialPort = require("serialport").SerialPort

//var serialPort = new SerialPort("/dev/tty.song-DevB", {
//var serialPort = new SerialPort("/dev/tty.usbmodem1421", {
var serialPort = new SerialPort("/dev/tty.usbmodem1411", {
//var serialPort = new SerialPort("/dev/tty.usbserial-A7026DQB", {
    baudrate:115200
   // baudrate:9600
});

var z="";
/*
var stream = fs.createWriteStream("my_file2.txt");
    stream.write(s);
*/
serialPort.open(function () {
  var f="$GPRMC";
  var heading="";
  var CMD=""; 
  var startCMD=0;
  serialPort.on('data', function(data) {
    var s=data.toString();

    for(var i=0;i<s.length;i++){
      var tempChar=s[i].toString();
      if(f.indexOf(tempChar)>-1){
        heading+=tempChar;
        if(heading==f){
          startCMD=1;
        }
        if(tempChar=="$"){
          startCMD=0;
          if(CMD.length>0){
            parseCMD(CMD);
          }
        }
      }else{
        if(startCMD==1){
          CMD+=tempChar;
        }else{
          CMD="";
        };
        heading="";
      }
    }
  });
});

function parseCMD(cmd){
  var a=cmd.split(",");
      console.log((a[3]/100).toFixed(7));
      console.log((a[5]/100).toFixed(7));
}

