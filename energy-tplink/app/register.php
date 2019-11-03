<?php
	require_once '/var/www/html//inc/functions.php';
$db =new PDO("mysql:host=localhost;dbname=home","root","mounmaya20");
$results["error"]= false;
$results["message"] = [];
/*$conn = mysqli_connect("localhost", "root", "mounmaya20", "home");
$results["error"]= false;
$results["message"] = [];

if ($_SERVER['REQUEST_METHOD'] =='POST'){

    $name = $_POST['name'];
		$Last_name =$_POST['last_name'];
    $email = $_POST['email'];
    $password = $_POST['password'];

    $password = password_hash($password, PASSWORD_DEFAULT);



    $sql = "INSERT INTO users (name, Last_name, email, password) VALUES ('$name', '$email', '$last_name', '$password')";

    if ( mysqli_query($conn, $sql) ) {
        $result["success"] = "1";
        $result["message"] = "success";

        echo json_encode($result);
        mysqli_close($conn);

    } else {

        $result["success"] = "0";
        $result["message"] = "error";

        echo json_encode($result);
        mysqli_close($conn);
    }
}*/

if (isset($_POST)){

  if(!empty($_POST['Name']) && !empty($_POST['last_name']) && !empty($_POST['email']) && !empty($_POST['password']) && !empty($_POST['password2'])){

$Name = $_POST['Name'];
$last_name = $_POST['last_name'];
$email = $_POST['email'];
$password = $_POST['password'];
$password2 = $_POST['password2'];
;
//vérification du pseudo


if(strlen($Name) < 2 || !preg_match("/[a-zA-Z ]/", $Name) || strlen($Name) > 600){
  $results["error"] = true;
  $results["message"] = "pseudo invalide";
}else {
  // vérification que le pseudo n'exite pas
//  $requete = $db->prepare("SELECT id FROM users WHERE ")
}
if(strlen($last_name) < 2 || !preg_match("/[a-zA-Z ]/", $last_name)  || strlen($last_name) > 600){

	$results["error"] = true;
	$results["message"] = "last name invalide";
}else{
  // vérification que le pseudo n'exite pas
//  $requete = $db->prepare("SELECT id FROM users WHERE ")
}
}
//vérifivcation de l'email
if(!filter_var($email, FILTER_VALIDATE_EMAIL)){
  $results["error"] = true;
  $results["message"]["email"] = "email invalide";
}else{
  //v"vérification que l'email n'exite pas
$requete = $db->prepare("SELECT id FROM users WHERE email = :email");
$requete->execute([':email' => $email]);
$row = $requete->fetch();
if ($row){
	$results["error"] = true;
	$results["message"]["email"] = "l'email exite déjà";
	}
}
//vérification du password
if($password !== $password2){
$results["error"] = true;
$results["message"] = "password diferent";
}
if($results["error"] === false){

  //$sql = $db->prepare("INSERT INTO users(Name ,last_name, email, password)")
  $password = password_hash($_POST['password'], PASSWORD_BCRYPT);
  /*$sql = $db->prepare("INSERT INTO users SET Name = ?, Last_name = ?, password = ?, email = ?,confirmation_token = ?");
  $token = str_random(60);
  $sql->execute([$_POST['Name'], $_POST['Last_name'], $password, $_POST['email'],  $token]);
  mail($_POST[email], 'confirmation de votre compt',"Afin de valider votre compt merci de cliquer sur ce lien http://192.168.1.107/confirm.php?id=$user_id&token=$token");
if(!$sql){
  $results["error"] = true;
  $results["message"] = "une erreur c'est produit lor de l'inscription";
}*/



}else{
    $results["error"] = true;
    $results["message"] = "veuillez remplir tous les champs";
  }
	echo ($last_name);
echo (strlen($last_name) < 2 || !preg_match("/[a-zA-Z ]/", $last_name)  || strlen($last_name) > 600);
  echo json_encode($results);
}

 ?>
