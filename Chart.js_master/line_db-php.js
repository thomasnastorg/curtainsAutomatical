// Fermeture
(function(){
	/**
	 * Fonction pour arrondir un nombre.
	 *
	 * @param	{String}	type	Le type d'arrondi.
	 * @param	{Number}	value	Le nombre à arrondir.
	 * @param	{Integer}	exp		L'exposant (le logarithme en base 10 de la base pour l'arrondi).
	 * @returns	{Number}			La valeur arrondie.
	 */
	function decimalAdjust(type, value, exp) {
		// Si l'exposant vaut undefined ou zero...
		if (typeof exp === 'undefined' || +exp === 0) {
			return Math[type](value);
		}
		value = +value;
		exp = +exp;
		// Si value n'est pas un nombre
        // ou si l'exposant n'est pas entier
		if (isNaN(value) || !(typeof exp === 'number' && exp % 1 === 0)) {
			return NaN;
		}
		// Décalage
		value = value.toString().split('e');
		value = Math[type](+(value[0] + 'e' + (value[1] ? (+value[1] - exp) : -exp)));
		// Re "calage"
		value = value.toString().split('e');
		return +(value[0] + 'e' + (value[1] ? (+value[1] + exp) : exp));
	}

	// Arrondi décimal
	if (!Math.round10) {
		Math.round10 = function(value, exp) {
			return decimalAdjust('round', value, exp);
		};
	}
})();
var canvas = document.getElementById("month");
$.getJSON( "http://192.168.1.107/data.php", function( datas ) {
    x = []
    y = []
    r = []


    $.each(datas, function(i, data){
      var convertions = ((data.humidity/1205)*100);

      x[i] = [Math.round10(convertions, -2)]
      y[i] =[ data.temps]
       console.log(Math.round10(convertions, -2));
    })

})
.done(function() {
    var ctx = $("#line-chartcanvas");
  var myLineChart = new Chart(ctx, {
        type: 'line',
        data: {
        labels: y,
        datasets: [{
          label:'Citronnier',
          fill: true,
    lineTension: 0.3,
    backgroundColor: "rgba(0,255,0,0.4)",
    borderColor: "green", // The main line color
    borderCapStyle: 'square',
    pointBorderColor: "white",
    pointBackgroundColor: "green",
    pointBorderWidth: 1,
    pointHoverRadius: 8,
    pointHoverBackgroundColor: "yellow",
    pointHoverBorderColor: "green",
    pointHoverBorderWidth: 2,
    pointRadius: 4,
    pointHitRadius: 10,
            data: (x),
            borderWidth: 5,
            spanGaps: true,
        }]
    },
    options: {
         title: {
         display: true,
 position: "top",
 text: "Humidite",
 fontSize: 18,
                       },
legend: {display: true, position: "bottom"}
         }
    });
});
