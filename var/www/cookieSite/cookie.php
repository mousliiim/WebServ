<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Cookies</title>
</head>
<body>
	<h1>Cookie stocker:</h1>
	<?php
		if(isset($_COOKIE['nom'])) {
			echo "Nom : " . $_COOKIE['nom'] . "<br>";
		}
		if(isset($_COOKIE['prenom'])) {
			echo "Prénom : " . $_COOKIE['prenom'] . "<br>";
		}
		if(isset($_COOKIE['adresse'])) {
			echo "Adresse : " . $_COOKIE['adresse'] . "<br>";
		}
	?>
</body>
</html>