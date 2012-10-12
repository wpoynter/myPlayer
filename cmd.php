<?php

require_once('lib/ID3/getid3/getid3.php');
include('lib/functions.inc');

$myFile = $_GET['path'];

session_start();

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

$rate = "96k";
$multipler = 12000;

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

    while (true) {

        time_nanosleep(0, 100000000);
        if (checkKill() === 1) exit();
        $contents = fread($pipes[1], 8192);
        if (strlen($contents) == 0) break;
        echo $contents;
        flush();
    }
    
    fclose($pipes[1]);

    $return_value = proc_close($process);   
}
     
?>
