var http = require('http');
http.createServer(function (req, res) {
   res.writeHead(200, {'Content-Type': 'text/plain'});
   res.end('Robotize My Stuff !\n');
}).listen(1337, '192.168.1.107');
