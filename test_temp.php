<?php require_once '/var/www/html/header.php'; ?>
<!DOCTYPE html>
<html>
<head>
    <title>ChartJS - Line</title>

    <link href="css/app.css" rel="stylesheet">

</head>
<body>

  <div class="chart-container">
    <canvas id="line-chartcanvas"></canvas>
  </div>

  <!-- javascript -->
  <div id="demo"></div>
  <script src="lib/jquery.min.js"></script>
    <script src="Chart.js_master/Chart.min.js"></script>

    <script src="Chart.js_master/line_db-php.js"></script>
<button id="month" >Overall (Monthly)</button>

</body>
</html>
