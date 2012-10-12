<?php

include_once("tau.inc");
include_once("mcrypt.inc");
include_once("bcrypt.inc");

/**
 * Description of user
 *
 * @author williampoynter
 */
class user {
    
    private $IPAddress, $OS, $Browser, $BrowserVersion, $cxn;
    private $currentMedia, $currentPath, $currentProgress, $currentStatus;
    
    public $music, $TV, $movie, $books;
    
    private $screen;
    
    private $UID, $Username, $Password, $Salt, $DateAdded;
    
    public function __construct() {
        
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
    
    public function startNewMedia($Media, $Path, $Progress = 0) {
        
        if ((!empty($this->currentMedia) || !empty($this->currentPath) || !empty($this->currentProgress)) && $this->currentStatus != "Finished") {
            
            //submit log of previous media
        }
        
        $this->currentMedia = $Media;
        $this->currentPath = $Path;
        $this->currentProgress = $Progress;
        $this->currentStatus = "Playing";
        
    }
    
    public function updateProgress($newProgress) {
        
        $this->currentProgress = $newProgress;
    }
    
    public function download() {
	$sql = "SELECT * FROM users WHERE Username ='" . $this->Username . "'";
    $result = mysqli_query($this->getCxn(),$sql)
               or die("Couldn't load user.");
    $U_limit = mysqli_num_rows($result);
	if ($U_limit <= 0 ) return "No users found.";
	elseif ($U_limit > 1) return "Too many users found for this function.";
	else {
    	$user = mysqli_fetch_assoc($result); 

		$this->Salt = $user['Salt'];
                $this->Username = $user['Username'];
		$this->DateAdded = $user['DateAdded'];
		$this->Password = $user['Password'];
		$this->UID = $user['UID'];

		return $true;
	}
    }

    public function upload() {
            $sql = "SELECT * FROM users WHERE Username ='" . $this->Username . "'";
            if ($this->UID !="") $sql .= " AND UID = '$this->UID'";
        $result = mysqli_query($this->getCxn(),$sql)
                or die("Couldn't locate user.");
        $num_rows = mysqli_num_rows($result);
            if ($num_rows <= 0 ) {
                    if ($this->UID !="") return "No user detected in the upload function using the username: $this->Username and UID: $this->UID";
                    $sql = "INSERT INTO users (Username,Password,Salt,DateAdded)";
                    $sql .= " VALUES ('" . $this->Username . "', '";
                    $sql .=  $this->Password . "', '";
                    $sql .= $this->Salt . "'," . $this->DateAdded .")";
            $result = mysqli_query($this->getCxn(),$sql)
                or die("Couldn't create user." . mysqli_error($this->getCxn()));
            }
            elseif ($num_rows > 1) return "Multiple users detected in the upload function using the username: $this->Username and UID: $this->UID";
            else {
                    if ($this->UID =="") { 
                            $user_data = mysqli_fetch_assoc($result); 
                            $UID = $user_data['UID'];
                            return "One user detected, already with username: $this->Username and UID: $UID";
                    }
                    $sql = "UPDATE users SET Password='" . $this->Password ."'";
                    $sql .= ", Salt='" . $this->Salt . "'";
                    $sql .= " WHERE UID='" . $this->UID . "' AND Username='" . $this->Username . "'";

            $result = mysqli_query($this->getCxn(),$sql)
                or die("Couldn't upload user data.");

            }
            return true;
    }

	public function setData($array) {
		foreach ($array as $key => $val) {
			if($val == "") $this->$key = ""; 
                        else {
                            if($key != "Password") $this->$key = $val;
			}
		}
	}
        
	public function setPassword($input) {
		$bcrypt = new Bcrypt(15);
		if ($this->Salt == "" || $this->DateAdded == "") return false;
		$entry = $this->Salt . $input . $ssalt . $this->DateAdded;
		$temp = $bcrypt->hash($entry);
		if ($temp !== false) $this->Password = $temp;
		else return false;
		return true;
	}
	
	public function set($var, $val) {
                if($var == "Password") return false;
		if($val == "") $this->$var = "";
                $this->$var = $val;
	}	
	
	public function book() {
            foreach ($this as $key => $value)
                $out[$key] = $value;
            return $out;
	}
	
	public function get($var = "") {
		if ($this->$var == "") return "";
		return $this->$var;
	}
	
	public function login($username, $password) {
		$sql = "SELECT * FROM users WHERE Username='" . $username . "'";
		$result = mysqli_query($this->getCxn(),$sql)
               		or die("Couldn't find users." . mysqli_error($this->getCxn()));
        if (mysqli_num_rows($result) == 1) {
        	$user = mysqli_fetch_assoc($result);
        	$bcrypt = new Bcrypt(15);
			$entry = $user['Salt'] . $password . $ssalt . $user['DateAdded'];
			if ($bcrypt->verify($entry, $user['Password']) !== true) return false;
			$this->Salt = $user['Salt'];
			$this->DateAdded = $user['DateAdded'];
			$this->Password = $user['Password'];
			$this->UID = $user['UID'];
                        $this->Username = $user['Username'];
                        
                        //logging
                        /*if (!empty($_SERVER['REMOTE_ADDR'])) {
 			$info=file_get_contents('http://api.hostip.info/get_html.php?ip='.@$_SERVER['REMOTE_ADDR']);
 			list ($country,$city) = explode ("\n", $info);
 			$country = str_replace("Country: ", "", $country);
 			$city = str_replace("City: ", "", $city);
                        }
                        $logging = array(	"UID" 		=> $this->UID,
 							"Action"	=> "Logged in",
 							"Date"		=> time(),
 							"Successful"=> "Yes",
 							"EffectedID"=> NULL,
 							"IPAddress"	=> @$_SERVER['REMOTE_ADDR'],
 							"City"		=> $city,
 							"Country"	=> $country,
 							"Reason"	=> NULL,
 							"HumanNotes"=> NULL);
                        pushLog($logging);*/
			return true;
		}
		return false;
	}
        
        public function create() {

        $this->Salt = saltGen();
        $this->DateAdded = time();
		
	}
        
        public function allowed() {
            
            if (empty($this->UID)) return false;
            return true;
        }
    
}

?>
