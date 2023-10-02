<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Réception des données</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f2f2f2;
            margin: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .container {
            background-color: #fff;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            width: 400px;
            padding: 20px;
            text-align: center;
        }

        h1 {
            font-size: 24px;
            margin-bottom: 20px;
        }

        p {
            font-size: 16px;
            margin-bottom: 10px;
        }

        hr {
            border: 1px solid #ccc;
            margin: 20px 0;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Réception des données</h1>

        <h2>Données POST :</h2>
        <?php foreach ($_POST as $key => $value) : ?>
            <p><strong><?= $key ?>:</strong> <?= $value ?></p>
        <?php endforeach;
		$_COOKIE['testrayan'] = "mon premier cookie";
		$val = "Valeur de test";
		
		setcookie("TestCookie", $val);
		setcookie("TestCookie", $val, time()+3600);  /* expire dans 1 heure */
		setcookie("TestCookie", $val, time()+3600, "/~rasmus/", "example.com", 1);
		?>

        <hr>

        <h2>Données GET :</h2>
        <?php foreach ($_GET as $key => $value) : ?>
            <p><strong><?= $key ?>:</strong> <?= $value ?></p>
        <?php endforeach; ?>
		<a href="http://localhost:4244/">Retour</a>
    </div>
</body>
</html>