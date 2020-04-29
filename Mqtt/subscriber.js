var mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://192.168.1.105:1883')
var topic = 'toto'

client.on('message',(topic, message)=>{
    message = message.toString()
    console.log(message)
})
client.on('message',(tutu, message)=>{
    message = message.toString()
    console.log(message)
})
client.on('message',(fhfhf, message)=>{
    message = message.toString()
    console.log(message)
})

client.on('connect', ()=>{
    client.subscribe(topic)
})