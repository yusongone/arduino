
var SerialPort = require("serialport").SerialPort

//var serialPort = new SerialPort("/dev/tty.song-DevB", {
//var serialPort = new SerialPort("/dev/tty.usbmodem1421", {
var serialPort = new SerialPort("/dev/tty.usbmodem1411", {
//var serialPort = new SerialPort("/dev/tty.usbserial-A7026DQB", {
    baudrate:115200
   // baudrate:9600
});



  send=function(a){
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
      buf.writeUInt8("$".charCodeAt(0),0);
      buf.writeUInt8("B".charCodeAt(0),1);
      buf.writeUInt8("<".charCodeAt(0),2);
      buf.writeUInt8(0,3);//data length
      buf.writeUInt8(a,4);//data length
      var z=getSum(buf);
      buf.writeUInt8(z,5);//61
      port.write(buf,function(err,res){
        console.log(res);
      });
      function getSum(buffer) {
        var data = Array.prototype.slice.call(buffer, 3);
        if(data[0] === 0) {
          // out message
          return data[1];
        } else {
          // in message
          return data
            .slice(0, data.length)
            .reduce(function(tot, cur) {var temp=tot^cur; return temp; }, 0);
        }
      };
  };

serialPort.open(function () {
  var headString="";
  var buf=new Buffer(100);
  var datalength=0;
  var subIndex=0;
  var tartData=0;
  var startData=0;
  serialPort.on('data', function(data) {
    var bytes=data;
    var str="";
   for(var i=0;i<bytes.length;i++){
     var dd=bytes[i];
      str+=String.fromCharCode(dd)
   }
        console.log(str);
    return;
   for(var i=0;i<bytes.length;i++){
        var tempByte=bytes[i];
        if(startData==1){//get dataLength;
            buf[subIndex++]=tempByte;
            dataLength=tempByte;
            startData++;
        }else if(startData==2){//get msgId
            buf[subIndex++]=tempByte;
            startData++;
        }else if(startData>2){
            if(dataLength==0){
                buf[subIndex++]=tempByte;
                if(checkSum(buf)){
                    switchCMD(buf);
                };
                startData=0;
                subIndex=0;
            }else{
                buf[subIndex++]=tempByte;
                dataLength--;
            }
        }else if(tempByte==36||tempByte==66||tempByte=='>'||tempByte==60){
            headString+= String.fromCharCode(tempByte);
            if(headString=="$B>"||headString=="$B<"){
                startData=1;
                headString="";
            }
        }else{
            headString="";
        }
    }
  });
  //send();
  function checkSum(buf){
    var c=buf[0];//datalength;
    for(var i=1;i<=subIndex-2;i++){
        c=(c^(buf[i]&0xff));
    };
    if(c==buf[subIndex-1]){
        return true;
    }
    return false;
  }

});
exports.send=send;
function switchCMD(buf){
  var dataLength=buf[0];
  var msId=buf[1];
  switch(msId){
    case 205:
      console.log("a",(buf[2]&0xff)<<0|(buf[3]&0xff)<<8);
      console.log("b",(buf[4]&0xff)<<0|(buf[5]&0xff)<<8|(buf[6]&0xff)<<16);
      console.log("c",(buf[7]&0xff)<<0|(buf[8]&0xff)<<8);
      console.log("d",(buf[9]&0xff)<<0|(buf[10]&0xff)<<8);
      console.log("e",(buf[11]&0xff)<<0);
      break;
  }
}
