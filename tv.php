<html>
    <head>
        <title>
            lydPlayer - TV
        </title>
    </head>
    <body>
        <video id="tv-feed" controls="controls" autoplay="autoplay">
<?php echo "<source src='video.php?path= " . urlencode("/jupiter/TV" . $_GET['path']) . "' type='video/ogg' />"; ?>
        </video>
    </body>
</html>