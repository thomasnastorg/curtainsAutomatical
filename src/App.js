import React from 'react';
import './myTheme.css';
import Panneaux from './Module/Module'
import Freebox from './Module/Freebox_module'
import Light from './Module/Light_SL_LC_01'



function App() {
  return (
    <div className="container">

      <Freebox />
      <Light />
      <Panneaux name="room" />
      <Panneaux name="kinchen" />
      <Panneaux name="coucou" />
    </div>
  );
}


export default App;


