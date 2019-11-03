#!/bin/bash
DB_USER="root"
DB_PASSWD="mounmaya20"
DB_NAME="home"
DB_host="127.0.0.1"
TABLE="serveur"
datee=$(date +"%F")
heuree=$(date +"%H:%M:%S")
dist=`vcgencmd measure_temp`
tres="${dist: 5: 4}"
echo "$tres"
echo "$datee"
echo "$heuree"
mysql -u"root" -p"mounmaya20" -D"home" << EOF
insert into $TABLE (id, temp, date, heure) VALUES (NULL, "$tres", "$datee", "$heuree")
EOF
