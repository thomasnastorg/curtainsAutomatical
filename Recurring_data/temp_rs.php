<?php

require_once'/var/www/html/inc/db.php';


$outtemp = shell_exec(' vcgencmd measure_temp');
$tempt = substr($outtemp,5,4);
$datetime = new DateTime();
$jour = $datetime->format('Y-m-d');
$heure =$datetime->format('H:i:s');


echo $tempt;
echo $jour ;
echo $heure;

$req = $pdo->prepare("INSERT INTO serveur SET temp = ?, date =?, heure = ? ");
$req ->execute([$tempt,$jour,$heure]);


/*rajouter la base de donnée*/
?>
