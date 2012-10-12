<?php
/**
 * Description of musicLibrary
 *
 * @author williampoynter
 */

require_once ('tau.inc');
require_once ('song.inc');
require_once ('artist.inc');
require_once ('album.inc');
require_once ('user.inc');

class musicLibrary {
    
    private $library, $artists, $albums, $queue;
    
    private $cxn;
    
    public function __construct() {
        
        $this->init();
        $this->cxn = &$GLOBALS['cxn'];
    }
    
    public function getCxn() { 
	global $host, $dbuser, $dbpasswd, $dbname;
	if (@!mysqli_ping($this->cxn)) {
		$GLOBALS['cxn'] = mysqli_connect($host, $dbuser,$dbpasswd,$dbname);
		$this->cxn = &$GLOBALS['cxn'];
	}
	return $this->cxn; 
    }
    
    public function load($method = "a") {
        
        switch ($method) {
            
            case "r":
                $this->init();
            case "a":       //append, ammend and alter (I.e. don't remove what is alread loaded
                $sql = "SELECT * FROM songs";
                $result = mysqli_query($cxn, $sql);
                while($row = mysqli_fetch_assoc($result)) {

                    $library['SID'] = new Song($row['Title'], $row['Artist'], $row['Album'], $row['Length'], $row['Path'], $row['SID'], $row['Type']);
                    $this->artists->newArtist(end($library['SID']));
                    $this->albums->newAlbum(end($library['SID']));
                }
                break; 
        }
    }
    
    public function getScreen($list = "all", $filter = "") {
        
        $output = array();
        if (strpos($list, "library") || $list == "all") {
            
        }
        if (strpos($list, "queue") || $list == "all") {
            
        }
        if (strpos($list, "artists") || $list == "all") {
            
        }
        if (strpos($list, "albums") || $list == "all") {
            
        }
        if (count($output) == 1) return end($output);
        if (count($output) > 1) return $output;
        return "";
    }
    
    public function sort($list = "all") {
        
        switch ($list) {
            
            case "library":
                sortSongs($this->library);
                break;
            case "queue":
                sortSongs($this->queue);
                break;
            case "artists":
                $this->artists->sort();
                break;
            case "albums":
                $this->albums->sort();
                break;
            case "all":
                sortSongs($this->library);
                sortSongs($this->queue);
                $this->artists->sort();
                $this->albums->sort();
                break;
        }
    }
    
    public function init() {
        $this->albums = new albumList();
        $this->artists = new artistList();
        $this->library = array();
        $this->queue = array();
    }
    
    public function set($var, $val) {
        if($val == "") $this->$var = "";
        $this->$var = $val;
    }
    
    public function get($var = "") {
        if ($this->$var == "") return "";
        return $this->$var;
    }
    
}

?>
