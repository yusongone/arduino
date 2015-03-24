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


    var buf=new Buffer(7);  
      buf.fill(0);
      buf.writeInt8("$".charCodeAt(0),0);
      buf.writeInt8("B".charCodeAt(0),1);
      buf.writeInt8("<".charCodeAt(0),2);
      buf.writeUInt8(3,3);//data length
      buf.writeUInt8((1234>>0)&0xff,4);//msgId
      buf.writeUInt8((1234>>8)&0xff,5);//R
      buf.writeUInt8(0x10,6);
console.log(checksum(buf));
