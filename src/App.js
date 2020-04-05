import React, { Component } from 'react'
import './App.css'
import GuessCount from './GuessCount'
import Card from './Card'

class App extends Component {
  handleCardClicke(card){
    console.log(card, 'clicked')
  }
  render() {
    return (
      <div className="memory"> 
      <GuessCount guesses={0}/>
      <Card card='#' feedback="hidden" onClick={this.handleCardClicke}/>
      <Card card='@' feedback="justMatched"onClick={this.handleCardClicke}/>
      <Card card='°' feedback="justMismatched"onClick={this.handleCardClicke}/>
      <Card card='d' feedback="visble"onClick={this.handleCardClicke}/>
      <Card card='w' feedback="hidden"onClick={this.handleCardClicke}/>
      <Card card='<' feedback="justMatched"onClick={this.handleCardClicke}/>
      </div>
    )
  }
}

export default App
