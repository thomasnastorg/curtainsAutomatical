import React , { Component } from "react";



class Home extends Component {
  constructor() {
    super();
      this.state = {
        cont = 0
      }
  }
  
  render(){
    return(
      <h1>kkkkk {this.props.name}</h1>
    );
  }
}
export default Home;
