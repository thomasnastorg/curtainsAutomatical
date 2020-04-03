import React from "react";
import { BrowserRouter as Router, Switch, Route, Link } from "react-router-dom";
import "./App.css" ;
import Home  from "./page/home";
import Todo  from "./page/todo";
import SingeIn  from "./page/singe_in";

function App() {
  return(
    /*
    <div>
      <header className= "App-header" >
        <SingeIn/>
      </header>
    </div>*/

    <Router>
    <div className="App">
      <nav className="navbar navbar-expand-lg navbar-light fixed-top">
        <div className="container">
          <Link className="navbar-brand" to={"/sign-in"}></Link>
          <div className="collapse navbar-collapse" id="navbarTogglerDemo02">
            <ul className="navbar-nav ml-auto">
              <li className="nav-item">
                <Link className="nav-link" to={"/sign-in"}>SingeIn</Link>
              </li>
            </ul>
          </div>
        </div>
      </nav>

      <div className="auth-wrapper">
        <div className="auth-inner">
          <Switch>
            <Route exact path='/' component={SingeIn} />
            <Route path="/sign-in" component={SingeIn} />
          </Switch>
        </div>
      </div>
    </div></Router>
  );
}

export default App;
