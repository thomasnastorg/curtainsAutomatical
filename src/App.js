import React from 'react';
import './myTheme.css'; 
import Panneaux from './Module/Module'
import Freebox from './Module/Freebox_module'



function App()  {
  return(
    <div className="container">
      
      <Freebox />
    <Panneaux name = "chambre"/>
    <Panneaux name = "room"/>
    <Panneaux name = "kinchen"/>
    <Panneaux name = "coucou"/>
    </div>
    );
}


export default App;



