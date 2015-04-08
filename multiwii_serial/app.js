
var SerialPort = require("serialport").SerialPort

//var serialPort = new SerialPort("/dev/tty.song-DevB", {
//var serialPort = new SerialPort("/dev/tty.usbmodem1421", {
var serialPort = new SerialPort("/dev/tty.usbmodem1411", {
   // baudrate:115200
    baudrate:9600
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
            .reduce(function(tot, cur) {var temp=tot^cur; return temp; }, 0);
        }
      };
  };

serialPort.open(function () {
  var _headString="";
  var buf;
  var count=0;
  var datalength;
  serialPort.on('data', function(data) {
    for(var i=0;i<data.length;i++){
      console.log(data[i]);
    }
    return;
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
      if(data[i]==0x24||data[i]==0x4d||data[i]==0x3e||data[i]==0x3c){
        _headString+=String.fromCharCode(data[i]).toString();
        if(_headString=="$M>"){
          console.log("fefe");
          count=1;
          _headString="";
        }
      }else{
        _headString="";
      }
    }

//    decode(data);
  });
  //send();

});
exports.send=send;

