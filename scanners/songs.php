<?php


// include getID3() library (can be in a different directory if full path is specified)
require_once('../lib/ID3/getid3/getid3.php');
require_once ('../lib/tau.inc');

// Initialize getID3 engine
$getID3 = new getID3;

$cxn = mysqli_connect($host, $dbuser,$dbpasswd,$dbname);

$DirectoriesToScan[] = '/jupiter/Music'; // change to whatever directory you want to scan
//$DirectoriesToScan[] = $_GET['path'];

while (count($DirectoriesToScan) > 0) {
			foreach ($DirectoriesToScan as $DirectoryKey => $startingdir) {
				if ($dir = opendir($startingdir)) {
					set_time_limit(30);
					$flush = flush();
					while (($file = readdir($dir)) !== false) {
						if (($file != '.') && ($file != '..')) {
							$RealPathName = realpath($startingdir.'/'.$file);
							if (is_dir($RealPathName)) {
								if (!in_array($RealPathName, $DirectoriesScanned) && !in_array($RealPathName, $DirectoriesToScan)) {
									$DirectoriesToScan[] = $RealPathName;
								}
							} elseif (is_file($RealPathName)) {
                                                            
								set_time_limit(30);
								$ThisFileInfo = $getID3->analyze($RealPathName);
						
								getid3_lib::CopyTagsToComments($ThisFileInfo);
						
								// output desired information in whatever format you want
                                                                
                                                                $sql = "SELECT * FROM songs WHERE Path='" . mysqli_real_escape_string($cxn, $ThisFileInfo['filenamepath']) . "'";
                                                                $result = mysqli_query($cxn, $sql);
                                                                if (mysqli_num_rows($result) < 1) {             //new
                                                                

                                                                    $sql = "INSERT INTO songs (Title, Artist, Album, Length, Path, Type) VALUES";
                                                                    $sql .= "('" . $ThisFileInfo['comments_html']['title'][0] . "','" . $ThisFileInfo['comments_html']['artist'][0] . "','" . $ThisFileInfo['comments_html']['album'][0] . "'," . $ThisFileInfo['playtime_seconds'] . ",'" . $ThisFileInfo['filenamepath'] . "','" . $ThisFileInfo['fileformat'] . "')";
                                                                    $result = mysqli_query($cxn, $sql);
                                                                    if (!$result) echo mysqli_error($cxn);
                                                                }
							}
						}
					}
					closedir($dir);
				} else {
					//echo '<div style="color: red;">Failed to open directory "<b>'.htmlentities($startingdir).'</b>"</div><br>';
				}
				$DirectoriesScanned[] = $startingdir;
				unset($DirectoriesToScan[$DirectoryKey]);
			}
}

?>

