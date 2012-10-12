<?php
$host="localhost";
$dbuser="willPlayer";
$dbpasswd = "D1Ff3r3nC3";
$dbname = "willPlayer";
$dbport = "3306";

$central = array("key" => "lTtNb2pFH.2.C3RT/Blk66", "iv" => "85236741");

$ssalt = "Epsilon43Omega";

function saltGen(){ 
    $alphNums = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";        
    $newString = str_shuffle(str_repeat($alphNums, rand(1, 4))); 
    
    return substr($newString, rand(0,strlen($newString)-4), 4); 
}

?>
