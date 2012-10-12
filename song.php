<?php

require_once('lib/ID3/getid3/getid3.php');
include('lib/functions.inc');

$myFile = $_GET['path'];

$filename = "song.mp3";

$toReplace = array();
$afterReplace = array();
$toReplace[] = " "; $afterReplace[] = "\ ";
$toReplace[] = "("; $afterReplace[] = "\(";
$toReplace[] = ")"; $afterReplace[] = "\)";
$toReplace[] = "="; $afterReplace[] = "\=";
$toReplace[] = "&"; $afterReplace[] = "\&";

$mm_type="application/octet-stream";

header("Cache-Control: public, must-revalidate");
header("Pragma: hack"); // WTF? oh well, it works...
header("Content-Type: " . $mm_type);
if (empty($_GET['rate'])) {
    session_start();
    switch ($_SESSION['streamRate']){

        case "320":
            $rate = "320k";
            $multipler = 40000;
            $coef = 4;
            break;
        case "192":
            $rate = "192k";
            $multipler = 24000;
            $coef = 2;
            break;
        case "96":
        default:
            $rate = "96k";
            $multipler = 12000;
            $coef = 1;
            break;
    }
    session_write_close();
} else {
    $rate = $_GET['rate'] . "k";
    $multipler = $_GET['rate']*125;
    if ($rate == "320k") $coef = 4;
    elseif ($rate == "192k") $coef = 2;
    else $coef = 1;
}

$getID3 = new getID3;
$ThisFileInfo = $getID3->analyze($myFile);
header("Content-Length: " .(string)round($ThisFileInfo['playtime_seconds']*$multipler) );
header('Content-Disposition: attachment; filename="'.$filename.'"');
header("Content-Transfer-Encoding: binary\n");
$descriptorspec = array(
   0 => array("pipe", "r"),  // stdin is a pipe that the child will read from
   1 => array("pipe", "wb"),  // stdout is a pipe that the child will write to
   2 => array("file", "/tmp/error-output.log", "a") // stderr is a file to write to
);

$cwd = '/tmp';
//$process = proc_open('/usr/bin/php', $descriptorspec, $pipes, $cwd);
$process = proc_open('ffmpeg -i ' . str_replace($toReplace, $afterReplace,$myFile) . ' -v 0 -ab ' . $rate . ' -f mp3 -', $descriptorspec, $pipes, $cwd);
if (is_resource($process)) {
    fclose($pipes[0]);

    //stream_set_blocking($pipes[1],0);
    //stream_set_read_buffer($pipes[1],8192*$coef*2);
    
    while (true) {
        if (checkKill() === 1) exit();
        $contents = fread($pipes[1], 8192*$coef);
        if(strlen($contents) == 0 && feof($pipes[1])) break;
        echo $contents;
        flush();
        time_nanosleep(0, 100000000);
    }
    
    fclose($pipes[1]);

    $return_value = proc_close($process);   
}

?>