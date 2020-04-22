var mqtt = require('mqtt');
var client  = mqtt.connect('mqtt://192.168.1.105:1883');
client.on('connect', function () {
setInterval(function() {
client.publish('myTopic', 'Hello mqtt');
console.log('Message Sent');
}, 5000);
});