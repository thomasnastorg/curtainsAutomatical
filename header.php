<?php
	require '/var/www/html/inc/functions.php';
	session_start();
	logged_only();
	 ?>

<link href="http://192.168.1.107/css/app.css" rel="stylesheet" >
<nav class="navbar navbar-expand-lg navbar-dark bg-dark">
  <a class="navbar-brand" href="http://192.168.1.107/home.php">Home</a>
  <button id="menu" class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarColor02" aria-controls="navbarColor02" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
  </button>

  <div class="collapse navbar-collapse" id="navbarColor02">
    <ul class="navbar-nav mr-auto">
			<li class="nav-item">
				<a class="nav-link" href="https://maisonfeu.freeboxos.fr:11782/login.php">Freebox</a>
			</li>
			<li class="nav-item">
				<strike>
					<a class="nav-link" href="#">Camera</a>
				</strike>
			</li>
      <li class="nav-item">
        <a class="nav-link" href="http://192.168.1.107/parametre.php">parametre</a>
      </li>
			<li class="nav-item">
				<a class="nav-link" href='http://192.168.1.107/consomation.php'>consomation</a>
			</li>
	 </ul>
<form class="form-inline my-2 my-lg-0">
	<ul class="navbar-nav mr-auto">

		<li class="nav-item">

			<a class="nav-link" href="logout.php">Déconnexion</a>

		</li>
	</ul>
</form>
  </div>
</nav>
<script> src="lib/sidebar.js" </script>

<?php if (isset($_SESSION['flash'])): ?>
		<?php foreach ($_SESSION['flash'] as $type => $message): ?>
				<div class="alert alert-<?= $type; ?>">
								<?= $message; ?>
				</div>
		<?php endforeach; ?>
		<?php unset($_SESSION['flash']); ?>
<?php endif; ?>

<?php
debug($_SESSION)
?>
