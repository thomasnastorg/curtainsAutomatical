import React , {Component} from "react";


class SingeIn extends Component {
    render(){
        return(
            
               
               /*
                    
                    <div class="card-header">Singe in</div>
                    <div class="card-body">
                    <p>Email</p>
                    <input></input>
                    <p>Password</p>
                    <input></input>
                    <p></p>
                    <input type="checkbox" id="Remember"/>
                    <label for="Remember" className="txte-link">Remember</label>
                    <p className="txte-link">Forget Passwords</p>
                    <p className="txte-link">Register</p>
                    </div>
                    <button className="button">Submit</button>
                    */
                
            <form>
                 <h3>Sign In</h3>
 
                 <div className="form-group">
                     <label>Email address</label>
                     <input type="email" className="form-control" placeholder="Enter email" />
                 </div>
 
                 <div className="form-group">
                     <label>Password</label>
                     <input type="password" className="form-control" placeholder="Enter password" />
                 </div>
 
                 <div className="form-group">
                     <div className="custom-control custom-checkbox">
                         <input type="checkbox" className="custom-control-input" id="customCheck1" />
                         <label className="custom-control-label" htmlFor="customCheck1">Remember me</label>
                     </div>
                 </div>
 
                 <button type="submit" className="btn btn-primary btn-block">Submit</button>
                 <p className="forgot-password text-right">
                     Forgot <a href="#">password?</a>
                 </p>
             </form>
                
                
        );
        

    }


}
export default SingeIn;
/* 
1 creat page 


*/