<?php

class McryptConfig {
	private $key, $iv;
  	public function __construct($key = "", $iv = "") {
    	if(CRYPT_BLOWFISH != 1) {
      		throw new Exception("mcrypt not supported in this installation. See http://php.net/crypt");
    	}
    	if ($key == "") $this->makeKey();
    	else $this->key = $key;
    	if ($iv == "") $this->makeIv();
    	else $this->iv = $iv;
 	}
 	
 	private function makeIv() {
 		$iv_size = mcrypt_get_iv_size(MCRYPT_BLOWFISH, MCRYPT_MODE_CBC);
    	$IV = mcrypt_create_iv($iv_size, MCRYPT_RAND);
 		
 		$this->iv = $IV;
 	}
 	
 	private function makeKey() {
 		$key_size = mcrypt_get_key_size(MCRYPT_BLOWFISH, MCRYPT_MODE_CBC);
 		$bytes = $this->getRandomBytes($key_size);
 		$Key = $this->encodeBytes($bytes);
 		
 		$this->key = $Key;
 	}
 	
 	public function getKey() {
 		return $this->key;
 	}
 	
 	public function getIv() {
 		return $this->iv;
 	}
 	
 	private $randomState;
 	private function getRandomBytes($count) {
    $bytes = '';

    if(function_exists('openssl_random_pseudo_bytes') &&
        (strtoupper(substr(PHP_OS, 0, 3)) !== 'WIN')) { // OpenSSL slow on Win
      $bytes = openssl_random_pseudo_bytes($count);
    }

    if($bytes === '' && is_readable('/dev/urandom') &&
       ($hRand = @fopen('/dev/urandom', 'rb')) !== FALSE) {
      $bytes = fread($hRand, $count);
      fclose($hRand);
    }

    if(strlen($bytes) < $count) {
      $bytes = '';

      if($this->randomState === null) {
        $this->randomState = microtime();
        if(function_exists('getmypid')) {
          $this->randomState .= getmypid();
        }
      }

      for($i = 0; $i < $count; $i += 16) {
        $this->randomState = md5(microtime() . $this->randomState);

        if (PHP_VERSION >= '5') {
          $bytes .= md5($this->randomState, true);
        } else {
          $bytes .= pack('H*', md5($this->randomState));
        }
      }

      $bytes = substr($bytes, 0, $count);
    }

    return $bytes;
  }
 	
 	private function encodeBytes($input) {
    	// The following is code from the PHP Password Hashing Framework
    	$itoa64 = './ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';

    	$output = '';
    	$i = 0;
    	do {
      		$c1 = ord($input[$i++]);
      		$output .= $itoa64[$c1 >> 2];
      		$c1 = ($c1 & 0x03) << 4;
      		if ($i >= 16) {
        		$output .= $itoa64[$c1];
        		break;
      		}

      		$c2 = ord($input[$i++]);
      		$c1 |= $c2 >> 4;
      		$output .= $itoa64[$c1];
      		$c1 = ($c2 & 0x0f) << 2;

      		$c2 = ord($input[$i++]);
      		$c1 |= $c2 >> 6;
      		$output .= $itoa64[$c1];
      		$output .= $itoa64[$c2 & 0x3f];
    	} while (1);

    return $output;
  }

}

class Mcrypter {
	private $input, $config, $isEnc;
  	public function __construct($input,McryptConfig $config, $isEnc) {
  	
  		
  		$this->input = $input;
  		$this->config = $config;
  		$this->isEnc = $isEnc;
  		
  	}
  	
  	public function getAsIs() {
  		return $input;
  		}
  	
  	public function getEncrypt($escape = true) {
  		if ($this->isEnc === true) return $this->input;
    	$output = mcrypt_encrypt(MCRYPT_BLOWFISH, $this->config->getKey(), $this->input, MCRYPT_MODE_CBC, $this->config->getIv());
    	if(strlen($output) % 8 == 0)
    		if($this->safeCheck($output))
    			if ($escape) return addslashes($output); else return $output;

    return false;
  }
  
  	public function getDecrypt() {
  		if ($this->isEnc === false) return $this->input;
  		//if(strlen(stripslashes($this->input)) % 8 != 0) {echo "Helppppp!" .  strlen($this->input); return false;}
    	if ($escaped) $output = mcrypt_decrypt(MCRYPT_BLOWFISH, $this->config->getKey(), $this->input, MCRYPT_MODE_CBC, $this->config->getIv());
    	else $output = mcrypt_decrypt(MCRYPT_BLOWFISH, $this->config->getKey(), $this->input, MCRYPT_MODE_CBC, $this->config->getIv());
      		return rtrim($output);

  }
  
  	public function search($str) {
  		$temp = $this->getDecrypt();
  		if(strpos($temp,$str) === false ) return false;
  		return true;
  	
  	}
  
  	private function safeCheck($item) {
  		if (strlen($item) == 0) return false;
  		if (strlen($item) == strlen($this->input))
  			if (strpos($this->input,substr($input,0,round((strlen($item)/2), 0, PHP_ROUND_HALF_UP))) !== false)
  				return false;
  		return true;
  	}
}
?>