<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Document</title>
</head>
<body>
	<?php
	setcookie("nom", $_POST['nom'], time()+3600);  /* expire dans 1 heure */
	setcookie("prenom", $_POST['prenom'], time()+3600);  /* expire dans 1 heure */
	setcookie("adresse", $_POST['adresse'], time()+3600);  /* expire dans 1 heure */
	?>
	<h1>Cookies enregistree</h1>
	<p><a href="cookie.php">Afficher les cookies</a></p>
</body>
</html>
