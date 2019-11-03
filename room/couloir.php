<?php require_once '/var/www/html/header.php'; ?>
<!DOCTYPE html>
<html>
<head>
    <title>Couloir</title>

    <link href="/../css/app.css" rel="stylesheet">

</head>
<body>

  <div class="chart-container">
    <canvas id="line-chartcanvas"></canvas>
  </div>

  <!-- javascript -->
  <div id="demo"></div>
  <script src="/../lib/jquery.min.js"></script>
    <script src="/../Chart.js_master/Chart.min.js"></script>

    <script src="/../Chart.js_master/line_db-php.js"> </script>
<button id="month" type="button" class="btn btn-secondary">Joure</button>
<button id="month" type="button" class="btn btn-secondary">Mois</button>
<button id="month" type="button" class="btn btn-secondary">Année</button>

</body>
</html>
