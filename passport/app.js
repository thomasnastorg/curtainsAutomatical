var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var exphbs = require('express-handlebars');
var expressValidator = require('express-validator');
var flash = require('connect-flash');
var session = require('express-session');
var passport = require('passport');
var LocalStrategy = require('passport-local');
var mysql = require('mysql');
var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "mounmaya20"
});

var routes = require('./routes/index.js');
var users = require('./routes/users.js');

//init app
var app = express();

//view Engine
app.set('views', path.join(__dirname, 'views'));
app.engine('handlebars', exphbs({defailtLayout:'layout'}));
app.set('view engine', 'handlebars');

//bodyParser middleweare

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false}));
app.use(cookieParser());

//set static Folder
app.use(express.static(path.join(__dirname,'public')));

//Epress session
app.use(session({
  secret: 'secret',
  saveUninitialized: true,
  resave: true
}));
// Passport init

app.use(passport.initialize());
app.use(passport.session());


//express Validator
app.use(expressValidator({
  errorFomatter: function(param, msg, value){
    var namepace = param.split('.')
    , root = nameespace.shift()
    , formParam = root;

    while (nameespace.length) {
      formParam += '[' + nameespace.shift() + ']';
    }
    return{
      param : formParam,
      msg : msg,
      value : value
    };
  }
}));

// connect flash
app.use(flash());

//Global vars
app.use(function (req, res, next){
  res.locals.success_msg = req.flash('success_msg')
  res.locals.error_msg = req.flash('error_msg');
  res.locals.error = req.flash('error');
  next();
});

app.use('/', routes);
app.use('/users', users);

//set port
app.set('port',(process.env.PORT || 3000));
app.listen(app.get('port'), function(){
  console.log('server started on port '+app.get('port'));
});
