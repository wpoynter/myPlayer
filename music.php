<?php

require_once ('lib/tau.inc');
require_once ('lib/song.inc');
require_once ('lib/artist.inc');
require_once ('lib/album.inc');
require_once ('lib/user.inc');

session_start();

if (isset($_GET['FLAG'])) {
    
    error_reporting(E_ERROR | E_PARSE);
    
    switch ($_GET['FLAG']) {
        
        case "artistSelected":
            $_SESSION['list']['songs'] = $_SESSION['list']['library'];
            $artist = $_SESSION['list']['artists']->getArtist($_GET['ARID']);
            $SIDs = $artist->getSongIDs();
            foreach ($_SESSION['list']['songs'] as $key => $song) {
                if (!in_array($song->get("SID"), $SIDs)) {
                    unset($_SESSION['list']['songs'][$key]);
                }
            }
            if (empty($_SESSION['crit']['first'])) $_SESSION['crit']['first'] = "artists";
            else $_SESSION['crit']['second'] = "artists";
            echo "Hello";
            exit();
        case "albumSelected":
            $_SESSION['list']['songs'] = $_SESSION['list']['library'];
            $album = $_SESSION['list']['albums']->getAlbum($_GET['ALID']);
            $SIDs = $album->getSongIDs();
            foreach ($_SESSION['list']['songs'] as $key => $song) {
                if (!in_array($song->get("SID"), $SIDs)) {
                    unset($_SESSION['list']['songs'][$key]);
                }
            }
            if (empty($_SESSION['crit']['first'])) $_SESSION['crit']['first'] = "albums";
            else $_SESSION['crit']['second'] = "albums";
            echo "Hello";
            exit();
        case "NEXT":
            if (!empty($_SESSION['currentTranscode']['pid'])){ exec("ps aux | grep ffmpeg | grep -v 'sh -c' | grep  -v 'grep' | awk '{print $2}' | xargs kill -9",$output);
            mail("poynter.william@gmail.com","here",$output);
            }
            array_shift($_SESSION['list']['queue']);
            echo urlencode(reset($_SESSION['list']['queue'])->get('path')). "&rate=" . $_SESSION['streamRate'];
            exit();
        case "changeRate":
            $_SESSION['streamRate'] = $_GET['rate'];
            exit();
        case "songToPlay":

            $_SESSION['list']['queue'] = array();
            foreach ($_SESSION['list']['songs'] as $SID => $row) {
                if ($SID >= $_GET['SID']) $_SESSION['list']['queue'][$SID] = $row;
            }
            echo urlencode($_SESSION['list']['songs'][$_GET['SID']]->get('path')). "&rate=" . $_SESSION['streamRate'];
            exit();
        case "UPDATE":
            if (empty($_SESSION['list']['queue'])) $screen['list']['queue'] = "";
            else {
                foreach ($_SESSION['list']['queue'] as $row) {     //updating queue
                    //echo "Here: " . $song->format() . "<br>";
                    if ($i%2 == 0) $screen['list']['queue'] .= $row->format();
                    else $screen['list']['queue'] .= $row->format("table","odd");
                    $i++;
                }
            }
            
            if (empty($_SESSION['list']['songs'])) $screen['list']['songs'] = "";
            else {
                $screen['list']['songs'] = "<tr><th>Title</th><th>Length</th></tr>";
                foreach (@$_SESSION['list']['songs'] as $song) {     //updating songs
                    //echo "Here: " . $song->format() . "<br>";
                    $SIDs[] = $song->get("SID");
                    if ($i%2 == 0) $screen['list']['songs'] .= $song->format();
                    else $screen['list']['songs'] .= $song->format("table","odd");
                    $i++;
                }
            }
            
            $screen['list']['artists'] = $_SESSION['list']['artists']->output(($_SESSION['crit']['first'] == "artists" ? "" : $SIDs));             //updating artists
            $screen['list']['albums'] = $_SESSION['list']['albums']->output(($_SESSION['crit']['first'] == "albums" ? "" : $SIDs));             //updating albums
            
            echo json_encode($screen['list']);
            exit();
    }
    
} else {
    
    
    if (empty($_SESSION['user']) || !$_SESSION['user']->allowed()) {
        header('Location: index.php');
        exit();
    }
    
    if (empty($_SESSION['list']['library'])) {

        $cxn = mysqli_connect($host, $dbuser,$dbpasswd,$dbname);
        $sql = "SELECT * FROM songs";// WHERE Path LIKE '%.flac%'";
        $result = mysqli_query($cxn, $sql);

        $list = array();
        while($row = mysqli_fetch_assoc($result)) {

            if (substr($row['Path'], -4) == ".mp3" || substr($row['Path'], -5) == ".flac") $list[$row['SID']] = new Song($row['Title'], $row['Artist'], $row['Album'], $row['Length'], $row['Path'], $row['SID'], $row['Type']);
        }

        $i = 0;

        $artists = new artistList();
        $albums = new albumList();
        $screen['list']['songs'] = "<tr><th>Title</th><th>Length</th></tr>";

        foreach ($list as $song) {
            if ($i%2 == 0) $screen['list']['songs'] .= $song->format();
            else $screen['list']['songs'] .= $song->format("table","odd");
            $artists->newArtist($song);
            $albums->newAlbum($song);
            $i++;
        }

        $artists->sort();
        $albums->sort();

        $_SESSION['list']['artists'] = $artists;
        $_SESSION['list']['albums'] = $albums;
    }
    else {
        $_SESSION['list']['songs'] = $_SESSION['list']['library'];
        $screen['list']['songs'] = "<tr><th>Title</th><th>Length</th></tr>";
            foreach (@$_SESSION['list']['songs'] as $song) {     //updating songs
                //echo "Here: " . $song->format() . "<br>";
                if ($i%2 == 0) $screen['list']['songs'] .= $song->format();
                else $screen['list']['songs'] .= $song->format("table","odd");
                $i++;
            }
        
    }
$screen['list']['artists'] = $_SESSION['list']['artists']->output();
$screen['list']['albums'] = $_SESSION['list']['albums']->output();

$_SESSION['screen'] = $screen;
$_SESSION['list']['songs'] = $list;
$_SESSION['list']['library'] = $list;

if (substr($_SERVER['REMOTE_ADDR'],0,8) == "192.168.") $_SESSION['streamRate'] = 320;
else $_SESSION['streamRate'] = 96;

$rates = array(96,192,320);

include('javascript.inc');
include('music.html');

echo "<script type='text/javascript'>";

foreach ($rates as $rate)
    echo "document.getElementById(\"rate-" . $rate . "\").style.fontWeight=\"" . ($_SESSION['streamRate'] == $rate ? 800 : 400) . "\";\n";

echo "</script>";

}

?>
