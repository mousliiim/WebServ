<!DOCTYPE html>
<html>
<head>
    <title>Formulaire avec Cookies</title>
</head>
<body>

<?php
// Vérifie si le formulaire a été soumis
if(isset($_POST['submit'])) {
    // Récupère les données du formulaire
    $nom = $_POST['nom'];
    $prenom = $_POST['prenom'];
    $adresse = $_POST['adresse'];

    // Crée des cookies pour stocker les données
    setcookie('nom_cookie', $nom, time() + 3600); // Le cookie expire dans 1 heure
    setcookie('prenom_cookie', $prenom, time() + 3600);
    setcookie('adresse_cookie', $adresse, time() + 3600);

    // Affiche un message de confirmation
    echo "Informations sauvegardées dans les cookies.";
}
?>

<h2>Formulaire de Données</h2>
<form method="POST" action="">
    <label for="nom">Nom :</label>
    <input type="text" id="nom" name="nom"><br><br>

    <label for="prenom">Prénom :</label>
    <input type="text" id="prenom" name="prenom"><br><br>

    <label for="adresse">Adresse :</label>
    <input type="text" id="adresse" name="adresse"><br><br>

    <input type="submit" name="submit" value="Sauvegarder">
</form>

<h2>Données stockées en cookie :</h2>
<?php
if(isset($_COOKIE['nom_cookie'])) {
    echo "Nom : " . $_COOKIE['nom_cookie'] . "<br>";
}
if(isset($_COOKIE['prenom_cookie'])) {
    echo "Prénom : " . $_COOKIE['prenom_cookie'] . "<br>";
}
if(isset($_COOKIE['adresse_cookie'])) {
    echo "Adresse : " . $_COOKIE['adresse_cookie'] . "<br>";
}
?>

</body>
</html>
