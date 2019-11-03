<?php
require_once 'inc/db.php';
$json = [];
$stmt = $pdo->query("SELECT temp FROM serveur");
while($row = $stmt->fetch(PDO::FETCH_ASSOC)){
  $json[] = rtrim($row['temp'], "\r");
}
echo json_encode($json);
?>
