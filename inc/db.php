<?php
$servername = "localhost";
$username = "root";
$password = "mounmaya20";
$dbname = "home";

$conn = mysqli_connect($servername, $username, $password, $dbname);




$pdo = new PDO('mysql:host=localhost;dbname=home', 'root', 'mounmaya20');

$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

$pdo->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_OBJ);

?>
