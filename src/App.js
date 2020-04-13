import React from 'react';
import './myTheme.css'; 
import Panneaux from './Module'



function App()  {
  return(
    <div className="container">
      
    <Panneaux name = "chambre"/>
    <Panneaux name = "room"/>
    <Panneaux name = "kinchen"/>
    <Panneaux name = "Freebox"/>
    </div>
    );
}


export default App;



