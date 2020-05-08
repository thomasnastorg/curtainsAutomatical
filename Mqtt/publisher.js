var mqtt = require('mqtt');
var client = mqtt.connect('mqtt://192.168.1.105:1883');
var topic = 'toto'
client.on('connect', function () {
    setInterval(function () {
        client.publish(topic, 'Hello mqtt');
        console.log('Message Sent');
    }, 5000);
});