<?php
/**
 * filename: data.php
 * description: this will return the score of the teams.
 */

//setting header to json

header('Content-Type: application/json');

//database
define('DB_HOST', 'localhost');
define('DB_USERNAME', 'root');
define('DB_PASSWORD', 'mounmaya20');
define('DB_NAME', 'home');

//get connection
$mysqli = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

if(!$mysqli){
  die("Connection failed: " . $mysqli->error);
}


//query to get data from the table
$results = [];
$sql = mysqli_query($mysqli,"SELECT * FROM plant");

while ($row = mysqli_fetch_array($sql)) {
    $results[] =  [
        'humidity'  =>  $row['Humidity'],
        'temps'     =>  date('d/m/Y  H:i:s',strtotime($row['temps']))
    ];
}
//$gg = ['data' =>$results];
/*class Personne
{
  var $nom;
  var $prenom;
  var $annee;

  function Personne($id)
  {

    $this->ID= $dbdata['ID'];
    $this->Humidity = $dbdata['Humidity'];
    $this->temps= $dbdata['temps'];
    $this->Nom_de_la_plante= $dbdata['Nom_de_la_plante'];
  }
}
 $dbdata = array();
while ( $id = $sql->fetch_assoc())  {
 $dbdata[]=$id;
}*/


echo json_encode($results);






/*
//execute query
$result = $mysqli->query($query);

//loop through the returned data
$data = array();
foreach($result as $row) {
  $data[] = $row;
}

//free memory associated with result
$result->close();

//close connection
$mysqli->close();

//now print the data
print json_encode($data);*/
