<?php

require_once('lib/ID3/getid3/getid3.php');
include('lib/functions.inc');

$myFile = $_GET['path'];

$filename = "video.ogg";

$toReplace = array();
$afterReplace = array();
$toReplace[] = " "; $afterReplace[] = "\ ";
$toReplace[] = "("; $afterReplace[] = "\(";
$toReplace[] = ")"; $afterReplace[] = "\)";
$toReplace[] = "="; $afterReplace[] = "\=";
$toReplace[] = "&"; $afterReplace[] = "\&";

$mm_type="video/ogg";

header("Cache-Control: public, must-revalidate");
header("Pragma: hack"); // WTF? oh well, it works...
header("Content-Type: " . $mm_type);

$getID3 = new getID3;
$ThisFileInfo = $getID3->analyze($myFile);

header("Content-Length: " .(string)round($ThisFileInfo['playtime_seconds']*128000) );
header('Content-Disposition: attachment; filename="'.$filename.'"');
header("Content-Transfer-Encoding: binary\n");

$descriptorspec = array(
   0 => array("pipe", "r"),  // stdin is a pipe that the child will read from
   1 => array("pipe", "wb"),  // stdout is a pipe that the child will write to
   2 => array("file", "/tmp/error-output.log", "a") // stderr is a file to write to
);

$cwd = '/tmp';
$size = array();
mail("poynter.william@gmail.com","Data","here");
//$process = proc_open('/usr/bin/php', $descriptorspec, $pipes, $cwd);
$process = proc_open('ffmpeg -i ' . str_replace($toReplace, $afterReplace,$myFile) . ' -v 0 -b:v 2048k -ar 44100 -f ogg -', $descriptorspec, $pipes, $cwd);
if (is_resource($process)) {
    fclose($pipes[0]);
    
    while (true) {
        if (checkKill() === 1) break;
        $contents = fread($pipes[1], 8192);
        //$size[] = strlen($contents);
        if (strlen($contents) == 0 && feof($pipes[1])) break;
        echo $contents;
        flush();
        time_nanosleep(0, 100000);
    }
    //$sum = array_sum($size);
    //$mail = "Sum: " . $sum . "\n";
    //$mail .= "Average: " . $sum/count($size) . "\n";
    //sort($size);
    //$mail .= "Lowest: " . $size[0] . "\n";
    //$mail .= "Highest: " . end($size) . "\n";
    //$mail .= "Range: " . end($size)-$size[0] . "\n";
    fclose($pipes[1]);

    //mail("poynter.william@gmail.com","Data",$mail);
    
    $return_value = proc_close($process);   
}
?>
