<?php
session_start();
if(!empty($_POST)){
	$errors = array();
	require_once 'inc/db.php';
	require_once 'inc/functions.php';
	if(empty($_POST['Name']) ||  !preg_match('/^[a-zA-Z ]+$/', $_POST['Name'])){
		$errors['Name'] = "oups there is a problem with name";
	}
	if(empty($_POST['Last_name']) ||  !preg_match('/^[a-zA-Z ]+$/', $_POST['Last_name'])){
		$errors['Last_name'] = "oups there is a problem with Last_name";
	}
	if(empty($_POST['email']) || !filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
			$errors['email'] = "Your email is invalid";
	}else{
		$req = $pdo->prepare('SELECT id FROM users WHERE email = ?');
		$req->execute([$_POST['email']]);
		$user = $req->fetch();
		if($user){
			$errors['email'] = 'This email is already used for another account';
		}
	}
	if(empty($_POST['password']) || $_POST['password'] != $_POST['password_2']){
		$errors['password'] = "vous devez  rentre un mots de passe valide";
	}
	if(empty($errors)){
		$req = $pdo->prepare("INSERT INTO users SET Name = ?, Last_name = ?, password = ?, email = ?,confirmation_token = ?");
		$password = password_hash($_POST['password'], PASSWORD_BCRYPT);
		$token = str_random(60);
		$req->execute([$_POST['Name'], $_POST['Last_name'], $password, $_POST['email'],  $token]);
		$user_id = $pdo->lastInsertId();
		mail($_POST[email], 'confirmation de votre compt',"Afin de valider votre compt merci de cliquer sur ce lien http://192.168.1.107/confirm.php?id=$user_id&token=$token");
		$_SESSION['flash']['success'] = ' un email de confirmation vous a été envoyé pour valider  votre compte';
		header('Location: index.php');
		exit();

	}
}
?>
<link href="css/app.css" rel="stylesheet" >
<div class="card border-primary mb-3 card-me"  style="max-width:500;">
  			<div class="card-header "><h1>Register</h1>

<?php if(!empty($errors)): ?>
		<div class="alert alert-danger">
			<p>you have not completed the form correctly</p>
			<ul>
			<?php foreach($errors as $error): ?>
				<li><?= $error; ?></li>
			<?php endforeach; ?>
			</ul>
		</div>
<?php endif; ?>



  			</div>


			<div class="card-body ">

	<p class="card-text card-me"><form action="" method="POST">

		<div class="form-group">
			<label for="">Name</label>

			<input type="text" name="Name"  class="form-control" required>

		</div>
		<div class="form-group">
			<label for="">Last_name</label>

			<input type="text" name="Last_name"  class="form-control" required>

		</div>
		<div class="form-group">
			<label for="">Email</label>

			<input type="email" name="email" class="form-control" required>
		</div>

		<div class="form-group">
			<label for="">Password</label>

			<input type="password" name="password" class="form-control" required>

		<div class="form-group">
			<label for="">confirm your passwords</label>

			<input type="password" name="password_2" class="form-control" required>
		</div>

		<button type="submit" class="btn btn-primary">Submit</button>


   		</p>
  			</div>
</div>

		</label>
		</div>

	</form>
