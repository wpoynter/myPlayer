<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

echo "<html>
<head>

</head>
<body>";

echo "<div style='height: 30px; width: 100%; background: white; position: fixed; top: 0; left: 0; z-index: 10;'><center><audio controls='controls' autoplay='autoplay'><source src='song.php?path=" . $_GET['song'] . "' /></audio></center></div>";

echo "<div style='top: 40px; position: absolute; z-index: 9;'>";
include("list.php");//?path=" . $_GET['path']);


echo "</div>\n</body>
</html>";

?>
