import React, { Component } from 'react'
import mqtt from 'mqtt'
import { json } from 'body-parser';
//import { SketchPicker } from 'react-color';

var client = mqtt.connect('ws://192.168.1.105:4000')

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

      if(console.log(message.toString()) == "ON"){
        this.handleClick('OFF')
      }else{
        this.handleClick('ON')
      }
      

    })
  }

  componentWillMount() {

    if (this.client)
      this.client.end()
  }
  //handleOnchange = (e) =>this.setState({brightness: e.target.brightness} )

  handleClick() {
    (this.setState(state=>({eta: !state.eta  })))
    
  }

  render() {
    return (

      <div className="frame">

        <div className="text-center-Dark">
          LED
                </div >
        <div>
          <button onClick={() => this.handleClick()} className='bouton' size='5' >
            {this.state.eta ? 'ON' : 'OFF'}
          </button>
        </div>
        <div>
          <input type="text" value="brightness" name="brightness" size="10" />
        </div>
        <div>
          <input type="text" value="red" name="red" size="10" />
          <input type="text" value="bleu" name="bleu" size="10" />
          <input type="text" value="grenne" name="grenne" size="10" />
        </div>

        <button className='bouton'>
          sudmit
                </button>


      </div>
    )
  }
}


export default Light




/*
 <div>RED</div>
                <div className = "slidecontainer">
                <input type="range" min="0" max="255" value={this.state.brightness} className="slider" onChange={this.handleOnchange} />
                <div className="brightness">{this.state.brightness}</div>
                </div>
*/





