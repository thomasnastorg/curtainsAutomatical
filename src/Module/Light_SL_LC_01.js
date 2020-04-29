import React, { Component } from 'react'
//import { Connector } from 'mqtt-react';
import mqtt from 'mqtt'



export class Light extends Component{
    state ={
        value: 50,
        redBleuGrenne: "50, 12, 23"
        
    }
    componentDidMount() {
      this.client = mqtt.connect('ws://192.168.1.105:8000')  
      this.client.on("connect", ()=> {
        
         console.log("connected")
       
      })

      this.client.on('message',  (topic, message) => {
        // message is Buffer
        console.log(message.toString())
      })
    }
    componentWillMount(){
      if(this.client)
      this.client.end()
    }
    handleOnchange = (e) =>this.setState({value: e.target.value} )
    
    


    render() {
        return(
          
            <div className="frame">
                
                <div className="text-center-Dark">
                    LED
                </div >
                <div>RED</div>
                <div className = "slidecontainer">
                <input type="range" min="0" max="255" value={this.state.value} className="slider" onChange={this.handleOnchange} />
                <div className="value">{this.state.value}</div>
                </div>
                
               
            </div>
        )
    }
}


export default Light




