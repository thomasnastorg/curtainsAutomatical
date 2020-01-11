import React , { Component } from "react";

constructor() {
  super();
    this.state = {
      cont = 0
    }
}

class Home extends Component {
  render(){
    return(
      <h1>kkkkk {this.props.name}</h1>
    );
  }
}
export default Home;
