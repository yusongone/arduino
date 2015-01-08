
var SerialPort = require("serialport").SerialPort

//var serialPort = new SerialPort("/dev/tty.song-DevB", {
var serialPort = new SerialPort("/dev/tty.usbmodem1411", {
    baudrate:115200
});



serialPort.open(function () {

  serialPort.on('data', function(data) {
    console.log("get a data");
    console.log(data);
  });

var count=0;
  setInterval(function(){
    var msg = new Buffer(16);
      msg.writeInt16LE(1500, 0);
      msg.writeInt16LE(1500, 2);
      msg.writeInt16LE(1500, 4);
      msg.writeInt16LE(1500, 6);
      msg.writeInt16LE(1000, 8);
      msg.writeInt16LE(0, 10);
      msg.writeInt16LE(0, 12);
      msg.writeInt16LE(0, 14);
      send({id:200,data:msg});
    return;
    if(false&&count>5){
    }else{
  var msg = new Buffer(16);
    msg.writeInt16LE(1500, 0);
    msg.writeInt16LE(1500, 2);
    msg.writeInt16LE(1500, 4);
    msg.writeInt16LE(1000, 6);
    msg.writeInt16LE(1000, 8);
    msg.writeInt16LE(0, 10);
    msg.writeInt16LE(0, 12);
    msg.writeInt16LE(0, 14);
      send({id:200,data:msg});
      send(101);
    }
    count++;

  //send(100);
  },2000);
});
exports.send=function(json){
  var msg = new Buffer(16);
    msg.writeInt16LE(parseInt(json.pi)||1500, 0);
    msg.writeInt16LE(1500, 2);
    msg.writeInt16LE(parseInt(json.yaw)||1500, 4);
    msg.writeInt16LE(parseInt(json.th)||1500, 6);
    msg.writeInt16LE(parseInt(json.au1)||1500, 8);
    msg.writeInt16LE(0, 10);
    msg.writeInt16LE(0, 12);
    msg.writeInt16LE(0, 14);
      send({id:200,data:msg});
}

function send(message) {
  var sendHeader = [0x24, 0x4D, 0x3C];
  var size, len, msgId, data;
  if('number' === typeof message) {
    msgId = message;
    len = 0;
    size = 7;
  } else if('object' === typeof message) {
    msgId = message.id;
    data = message.data;
    len = data.length;
    size = 7 + data.length;
  }
  var msg = new Buffer(size);
  new Buffer(sendHeader).copy(msg, 0);            // header
  msg.writeUInt8(len, 3);                             // length
  msg.writeUInt8(msgId, 4);                           // message id
  if(data) {
    data.copy(msg, 5);                                // data
  }
  msg.writeUInt8(calculateChecksum(msg), 5 + len);  // checksum
  msg.writeUInt8(0, 6 + len);                         // derp data to force wii to comply
  serialPort.write(msg, function (err, result) {
    if(err) {
      console.log("err",err);
    } else {
      console.log("result",result);
    }
  });
};

function calculateChecksum(buffer) {
  var data = Array.prototype.slice.call(buffer, 3);
  if(data[0] === 0) {
    // out message
    return data[1];
  } else {
    // in message
    return data
      .slice(0, data[0])
      .reduce(function(tot, cur) { return tot ^ cur; }, 0);
  }
};
