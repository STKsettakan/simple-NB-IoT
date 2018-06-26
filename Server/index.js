var PORT = 4444;
var dgram = require('dgram');
var server = dgram.createSocket('udp4');

var curip;
var curport;

var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);


server.on('error',function(error){
  console.log('Error: ' + error);
  server.close();
});

server.on('listening', function () {
    var address = server.address();
    console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

server.on('message', function (message, remote) {
console.log(remote.address + ':' + remote.port +' - ' + message);

curip = remote.address;
curport = remote.port;

});

function udpSend( data)
{

        server.send(data,0,data.length,curport,curip,function(error){
        if(error){
        client.close();
        reject(error)
        }else{
        console.log('Data sent !!!');
        }
        });
}



server.bind(PORT);




app.get('/', function(req, res){
res.sendFile(__dirname + '/index.html');
});


http.listen(3000, function(){
  console.log('listening on *:3000');
});

io.on('connection', function(socket){
    socket.on('chat message', function(msg){
    console.log('message: ' + msg);
    udpSend(msg);
  });
});
