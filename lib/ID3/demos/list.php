<?php
/////////////////////////////////////////////////////////////////
/// getID3() by James Heinrich <info@getid3.org>               //
//  available at http://getid3.sourceforge.net                 //
//            or http://www.getid3.org                         //
/////////////////////////////////////////////////////////////////
//                                                             //
// /demo/demo.simple.php - part of getID3()                    //
// Sample script for scanning a single directory and           //
// displaying a few pieces of information for each file        //
// See readme.txt for more details                             //
//                                                            ///
/////////////////////////////////////////////////////////////////

//die('Due to a security issue, this demo has been disabled. It can be enabled by removing line '.__LINE__.' in '.$_SERVER['PHP_SELF']);

echo '<html><head>';
echo '<title>getID3() - /demo/demo.simple.php (sample script)</title>';
echo '<style type="text/css">BODY,TD,TH { font-family: sans-serif; font-size: 9pt; }</style>';
echo '</head><body>';


// include getID3() library (can be in a different directory if full path is specified)
//require_once('../getid3/getid3.php');

// Initialize getID3 engine
$getID3 = new getID3;
$counter =0;
$DirectoriesToScan[] = '/jupiter/Music'; // change to whatever directory you want to scan
//$dir[] = opendir($DirectoryToScan);
echo '<table border="1" cellspacing="0" cellpadding="3">';
echo '<tr><th>Filename</th><th>Artist</th><th>Title</th><th>Bitrate</th><th>Playtime</th></tr>';
while (count($DirectoriesToScan) > 0) {
			foreach ($DirectoriesToScan as $DirectoryKey => $startingdir) {
				if ($dir = opendir($startingdir)) {
					set_time_limit(30);
					flush();
					while (($file = readdir($dir)) !== false) {
						if (($file != '.') && ($file != '..')) {
							$RealPathName = realpath($startingdir.'/'.$file);
							if (is_dir($RealPathName)) {
								if (!in_array($RealPathName, $DirectoriesScanned) && !in_array($RealPathName, $DirectoriesToScan)) {
									$DirectoriesToScan[] = $RealPathName;
								}
							} elseif (is_file($RealPathName)) {
							
								set_time_limit(30);
								$counter++;
								/*$ThisFileInfo = $getID3->analyze($RealPathName);
						
								getid3_lib::CopyTagsToComments($ThisFileInfo);
						
								// output desired information in whatever format you want
								echo '<tr>';
								echo '<td>'.$ThisFileInfo['filenamepath'].'</TD>';
								echo '<td>'.(!empty($ThisFileInfo['comments_html']['artist']) ? implode('<BR>', $ThisFileInfo['comments_html']['artist']) : '&nbsp;').'</td>';
								echo '<td>'.(!empty($ThisFileInfo['comments_html']['title'])  ? implode('<BR>', $ThisFileInfo['comments_html']['title'])  : '&nbsp;').'</td>';
								echo '<td align="right">'.(!empty($ThisFileInfo['audio']['bitrate'])        ? round($ThisFileInfo['audio']['bitrate'] / 1000).' kbps'   : '&nbsp;').'</td>';
								echo '<td align="right">'.(!empty($ThisFileInfo['playtime_string'])         ? $ThisFileInfo['playtime_string']                          : '&nbsp;').'</td>';
								echo '</tr>';*/
							}
						}
					}
					closedir($dir);
				} else {
					echo '<div style="color: red;">Failed to open directory "<b>'.htmlentities($startingdir).'</b>"</div><br>';
				}
				$DirectoriesScanned[] = $startingdir;
				unset($DirectoriesToScan[$DirectoryKey]);
			}
}
echo '</table>';
echo "Counter: " . $counter . "<br>";
?>
</body>
</html>