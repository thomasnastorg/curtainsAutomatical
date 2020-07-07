// 0 = this state is created 
// 1 = this state is everything ok 
// 2 = this state is error
// 3 = this state is format
var MongoClient = require('mongodb').MongoClient;
var masterDatabase = 0 

var url = "mongodb://localhost:27017/mydb";


//conection database and change state if posible (is her) 

//condition verication database is created if no created creat database
if (masterDatabase != stateDatabase) {
    MongoClient.connect(url, function(err, db) {
        if (err) throw err;
        var dbo = db.db("mydb");
        dbo.collection("customers").find({}, { projection: { _id: 0, name: 1 } }).toArray(function(err, result) {
          if (err) throw err;
          console.log(result);
          db.close();
        });
      });
}
//if yes verefication steta of databvese wiht number ex : 0,1,2,3..
if(){

}
