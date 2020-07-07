import React, { Component } from 'react'
import mqtt from 'mqtt'
import iro from '@jaames/iro';


var client = mqtt.connect('ws://192.168.1.105:4000')

var colorPicker = new iro.ColorPicker("#picker", {
  // Set the size of the color picker
  width: 200,
  // Set the initial color to pure red
  color: "#f00",
  layout: [
    { 
      component: iro.ui.Wheel,
      options: {}
    },
  ]
});


export class Light extends Component {
  constructor(props) {
    super(props);
    this.state = {
      eta: "ON"
    }
    this.handleClick = this.handleClick.bind(this)
  }
  componentDidMount() {
    this.client = mqtt.connect('ws://192.168.1.105:4000')
    this.client.on("connect", () => {
      console.log("Connected to MQTT")
      this.client.subscribe('state/state', console.log) //position 0
    })

    this.client.on('message', (topic, message) => {
      this.updateEta(message.toString())
    })

  }
  updateEta(message) {
    if (message == "ON") {
      this.setState({ eta: "ON" })
    } if (message == "OFF") {
      this.setState({ eta: "OFF" })
    } else {
      console.log("message Unkonwn")
    }
  }
  componentWillMount() {

    if (this.client)
      this.client.end()
  }
  //handleOnchange = (e) =>this.setState({brightness: e.target.brightness} )

  handleClick() {
    if (this.state.eta == "ON") {
      this.client.publish('state/set', "OFF")
    } else {
      this.client.publish('state/set', "ON")
    }
  }
  

  render() {
    return (

      <div className="frame">

        <div className="text-center-Dark">
          LED
                </div >
        <div>
          <button onClick={() => this.handleClick()} className='bouton-state'  >
            {this.state.eta}
          </button>
        </div>
      
        <div className="slidecontainer">
          <input type="range" min="0" max="255" value={this.state.brightness} className="slider" onChange={this.handleOnchange} />
          <div>{this.state.brightness}</div>
        </div>
        <div id="picker"></div>
        
      </div>
    )
  }
}


export default Light










