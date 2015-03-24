
var SerialPort = require("serialport").SerialPort

//var serialPort = new SerialPort("/dev/tty.song-DevB", {
//var serialPort = new SerialPort("/dev/tty.usbmodem1421", {
var serialPort = new SerialPort("/dev/tty.usbmodem1411", {
   // baudrate:115200
    baudrate:9600
});



  var send=function(){
    var port=serialPort; 
    //port_message_send(port, 100,100 );
    /*
    var buf=new Buffer(6);  
      buf.fill(0);
      buf.writeInt8("$".charCodeAt(0),0);
      buf.writeInt8("M".charCodeAt(0),1);
      buf.writeInt8("<".charCodeAt(0),2);
      buf.writeInt8(0,3);
      buf.writeUInt8(102,4);
      buf.writeUInt8(checksum(buf),5);
      port.write(buf,function(err,res){
        console.log(res);
      });
      return;
      */
    var buf=new Buffer(6);  
      buf.fill(0);
      buf.writeInt8("$".charCodeAt(0),0);
      buf.writeInt8("B".charCodeAt(0),1);
      buf.writeInt8("<".charCodeAt(0),2);
      buf.writeUInt8(0,3);//data length
      buf.writeUInt8(201,4);//data length
      var z=checksum(buf);
      buf.writeUInt8(z,5);//61
      port.write(buf,function(err,res){
        console.log(res);
      });
      function checksum(buffer) {
        var data = Array.prototype.slice.call(buffer, 3);
        if(data[0] === 0) {
          // out message
          return data[1];
        } else {
          // in message
          return data
            .slice(0, data.length)
            .reduce(function(tot, cur) {var temp=tot^cur;console.log("----------"+temp); return temp; }, 0);
        }
      };
  };

serialPort.open(function () {
  var _headString="";
  var buf;
  var count=0;
  var datalength;
  serialPort.on('data', function(data) {
    console.log("fff",data);
    for(var i=0;i<data.length;i++){
      if(count==1){
          datalength=data[i];
          buf=new Buffer(datalength+2);
       }
      if(count>0){
        buf[count-1]=data[i];
        count++;
      };
      if(datalength==0){
      }else if(datalength&&(datalength+2)==count){
        console.log(buf);
        console.log(buf[1]);
        count=0;
        datalength=null;
      }
      if(data[i]==0x24||data[i]==0x4d||data[i]==0x3e){
        _headString+=String.fromCharCode(data[i]).toString();
        if(_headString=="$M>"){
          count=1;
          _headString="";
        }
      }else{
        _headString="";
      }
    }

//    decode(data);
  });
  setInterval(send,1000);

});


var msp={};
var codes;
msp.codes=codes;
codes = {
  MSP_IDENT:        100,
  MSP_STATUS:       101,
  MSP_RAW_IMU:      102,
  MSP_SERVO:        103,
  MSP_MOTOR:        104,
  MSP_RC:         105,
  MSP_RAW_GPS:      106,
  MSP_COMP_GPS:       107,
  MSP_ATTITUDE:       108,
  MSP_ALTITUDE:       109,
  MSP_BAT:        110,
  MSP_RC_TUNING:      111,
  MSP_PID:        112,
  MSP_BOX:        113,
  MSP_MISC:         114,
  MSP_MOTOR_PINS:     115,
  MSP_BOXNAMES:       116,
  MSP_PIDNAMES:       117,
  
  MSP_SET_RAW_RC:     200,
  MSP_SET_RAW_GPS:    201,
  MSP_SET_PID:      202,
  MSP_SET_BOX:      203,
  MSP_SET_RC_TUNING:    204,
  MSP_ACC_CALIBRATION:  205,
  MSP_MAG_CALIBRATION:  206,
  MSP_SET_MISC:       207,
  MSP_RESET_CONF:     208,
  MSP_SELECT_SETTING:   210,
  
  MSP_BIND:         240,
  
  MSP_EEPROM_WRITE:     250,
  
  MSP_DEBUGMSG:       253,
  MSP_DEBUG:        254,
  
  // Additional baseflight commands that are not compatible with MultiWii
  MSP_UID:        160,
  MSP_ACC_TRIM:       240,
  MSP_SET_ACC_TRIM:     239,
  MSP_GPSSVINFO:      164 // get Signal Strength (only U-Blox)
};
