<?php
if(!empty($_POST) && !empty($_POST['email']) && !empty($_POST['password'])){
    require_once 'inc/db.php';
    $req = $pdo->prepare('SELECT * FROM users WHERE (email = :username) AND confirmed_at IS NOT NULL');
    $req->execute(['username' => $_POST['email']]);
    $user = $req->fetch();
    if($user == null){
        $_SESSION['flash']['danger'] = 'Identifiant ou mot de passe incorrecte';
    }elseif(password_verify($_POST['password'], $user->password)){
      session_start();
      $_SESSION['auth'] = $user;
        $_SESSION['flash']['success'] = 'Vous êtes connecté';
        header('Location: home.php');
        exit();
    }else{
        $_SESSION['flash']['danger'] = 'Identifiant ou mot de passe incorrecte';
    }
}
?>
 <?php require 'inc/functions.php' ?>
<link href="css/app.css" rel="stylesheet" >

<div class=" border-primary mb-3 card-me card text-white bg-dark mb-3   "  style="max-width:500;">
            <div class="card-header "><h1>Login</h1></div>
            <div class="card-body ">

    <p class="card-text card-me"><form action="" method="POST">


        <div class="form-group">
            <label for="">Email</label>

            <input type="email" name="email" class="form-control" required>
        </div>

        <div class="form-group">
            <label for="">Password</label>

            <input type="password" name="password" class="form-control" required>

        <div class="text-right" >
          <strike >
             <a href="oups.php">Forget Passwords</a>
           </strike>
        </div>

        <div class="text-right" >

             <a href="Register.php">Register</a>
        </div>
        <br>

        <button type="submit" class="btn btn-primary">Submit</button>


        </p>
            </div>
        </div>
            </div>
    </form>
    <?php if (isset($_SESSION['flash'])): ?>
        <?php foreach ($_SESSION['flash'] as $type => $message): ?>
            <div class="alert alert-<?= $type; ?>">
                    <?= $message; ?>
            </div>
        <?php endforeach; ?>
        <?php unset($_SESSION['flash']); ?>
    <?php endif; ?>
