
const { Client } = require('index');

const client = new Client();

client.getDevice({ host: '192.168.1.45' }).then((device)=>{
  device.getSysInfo().then(console.log);
  device.setPowerState(true);
});
