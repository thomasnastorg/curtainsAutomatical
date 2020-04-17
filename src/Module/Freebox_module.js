import React, { Component } from 'react'



class Freebox extends Component{
    constructor(props){
        super(props)
    
        this.state = {
            "app_id": "fr.freebox.home",
            "app_name": "Test App",
            "app_version": "0.0.1",
            "device_name": "compte de thomas"
        }
    }
    componentWillMount() {
        this.getData()
      }

    getData(){
        /*var xhr = new XMLHttpRequest() 
        xhr.overrideMimeType("application/json");
        xhr.addEventListener('load', () => {
            // update the state of the component with the result here
            console.log(xhr.responseText)
          })
        xhr.open('POST', 'http://mafreebox.freebox.fr/api/v4/login/authorize/',true)
        //xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
        //xhr.setRequestHeader("Content-type", this.state)
       
        xhr.send(/*JSON.stringify({"app_id": "fr.freebox.home","app_name": "Test App","app_version": "0.0.1","device_name": "compte de thomas"}))*/
       
      
        /*fetch('http://mafreebox.freebox.fr/api/v4/login/authorize/')
        .then((response) => {
          return response.json();
        })
        .then((data) => {
          console.log(data);
        });*/
      
       
    }
    render() {
       
        return (
            <div className="frame">
              <form onSubmit={this.handleSubmit} crossOrigin="anonymous"></form>
                <div className="text-center-Dark">
                    freebox
                </div >
                <div className = "text-Dark">
                    <p>debit</p>
                    <h5> 2 up</h5>
                    
                </div>
            </div>
            )

        }
 }

    export default Freebox


    

/*request.onreadystatechange = function() {
  if(this.readyState == this.HEADERS_RECEIVED) {

    // Get the raw header string
    var headers = request.getAllResponseHeaders();

    // Convert the header string into an array
    // of individual headers
    var arr = headers.trim().split(/[\r\n]+/);

    // Create a map of header names to values
    var headerMap = {};
    arr.forEach(function (line) {
      var parts = line.split(': ');
      var header = parts.shift();
      var value = parts.join(': ');
      headerMap[header] = value;
    });
  }
}*/