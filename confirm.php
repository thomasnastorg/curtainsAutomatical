<?php
$user_id = $_GET['id'];
$token = $_GET['token'];
require 'inc/db.php';
$req = $pdo->prepare('SELECT confirmation_token FROM users WHERE id = ?');
$req->execute([$user_id]);
$user = $req->fetch();
session_start();
if($user && $user->confirmation_token == $token){
	session_start();
	$pdo->prepare('UPDATE users SET confirmation_token = NULL, confirmed_at = NOW() where id= ?')->execute([$user_id]);
$_SESSION['flash']['success'] = 'votre compte a bien été validé';
	$_SESSION['auth'] = $user;
	header ('Location: account.php');
}else{
	$_SESSION['flash']['danger'] = "ce tokenn'est plus valide";
	header ('Location: index.php');
}

?>
