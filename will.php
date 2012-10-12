<?php

//include('lib/functions.inc');

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/*
session_start();
session_unset();
session_destroy();

require_once ('lib/tau.inc');

session_start();

if (isset($_GET['SID'])) { 
    echo "song.php?path=/Users/williampoynter/Music/iTunes/iTunes Media/Music/Pink Floyd/The Wall-Disc 1/01 In The Flesh.mp3";
    exit();
}

$cxn = mysqli_connect($host, $dbuser,$dbpasswd,$dbname);

$sql = "SELECT * FROM songs";

$result = mysqli_query($cxn, $sql);

$artists = array();
$albums = array();
$titles = array();
$lengths = array();

while($row = mysqli_fetch_assoc($result)) {

    if (!in_array($row['Artist'], $artists)) {
        
        $artists[] = $row['Artist'];
    }
    
    if (!in_array($row['Album'], $albums)) {
        
        $artists[] = $row['Album'];
    }
    
    $titles[$row['SID']] = $row['Title'];
    $lengths[$row['SID']] = $row['Length'];
}

$i =0;
foreach ($titles as $key => $value ) {
    
    if ($i%2 == 0) $screen['queue']['songs'] .= "<tr stlye='display: block; height: 10px;' class='even-row'><td><a style='display: block; width: 100%; color: black;' onClick='songDblClick(\"$key\")' href='javascript://' >" . $value . "</a></td><td>" . date("i:s",round($lengths[$key])) . "</tr>";
    else $screen['queue']['songs'] .= "<tr class='odd-row'><td><a style='display: block; width: 100%; color: black;' href='music.php?FLAG=songToPlay&SID=$key' >" . $value . "</a></td><td>" . date("i:s",round($lengths[$key])) . "</tr>";
    $i++;
}

foreach ($artists as $key => $value ) {
    
    $screen['queue']['artists'] .= "<option value=" . $key . " >" . $value . "</option>";
}

foreach ($albums as $key => $value ) {
    
    $screen['queue']['albums'] .= "<option value=" . $key . " >" . $value . "</option>";
}

$_SESSION['screen'] = $screen;

include('will.html');

$one = array();
$two = array();

$one[] = "a";
$one[] = "b";
$one[] = "c";

$one[] = "d";
$one[] = "e";
$one[] = "f";

var_dump($one);
echo "<br><br>";
unset($one[2]);
var_dump($one);

//session_start();
//$_SESSION['willPlayer'] = true;
//echo setcookie("willPlayer", true, time()+3600) . "<br>";
//session_write_close();
//setKill(1);
//sleep(4);
//setKill(0);
//session_start();
//$_SESSION['willPlayer'] = false;
//session_write_close();
//echo setcookie("willPlayer", false, time()+3600) . "<br>";

include('lib/user.inc');

$user = new user();

$user->create();

$user->set("Username", "solaris");
$user->setPassword("GeF0rc34");

$user->upload();

echo "done";*/

function cmp($a, $b) {
    
    return strcasecmp($a, $b);
}

$dir = '/jupiter/TV' . $_GET['a'];
$items = array();
$directories = array();
if ($handle = opendir($dir)) {
    echo "<b>Directory handle: $handle</b><br>\n";
    $temp = strripos($_GET['a'], "/");
    if ($temp !== 0)
        echo "<a href='?a=" . urlencode(substr($_GET['a'], 0, $temp)) . "'>Up</a><br>";
    else 
        echo "<a href='?'>Up</a><br>";
    echo "<b>Entries:</b><br>\n";

    /* This is the correct way to loop over the directory. */
    while (false !== ($entry = readdir($handle))) {
        if (substr($entry, 0, 1) != ".") {
                if (!is_dir("$dir/$entry")) $items[] = "<a href='tv.php?path=" . urlencode($_GET['a'] . "/" .$entry) . "'>" . $entry . "</a><br>\n";
                else $directories[] = "<a href='?a=" . urlencode($_GET['a'] . "/" .$entry) . "' >" . $entry . "/</a><br>\n";
        }
    }
    
    closedir($handle);

    usort($directories,"cmp");
    usort($items,"cmp");
    foreach ($directories as $value)
        echo $value;
    foreach ($items as $value)
        if (!in_array($value, $directories)) echo $value;
}

?>
