<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

//require_once ('lib/tau.inc');

//session_start();

/*$cxn = mysqli_connect($host, $dbuser,$dbpasswd,$dbname);

            $sql = "SELECT * FROM songs WHERE SID=" . $_GET['SID'];
            $result = mysqli_query($cxn, $sql);        
            $row = mysqli_fetch_assoc($result);
            
            foreach ($row as  $key => $value)
                $_SESSION['screen']['song'][lcfirst ($key)] = $value;
            
            include('music.html');
            //echo json_encode($row);
            echo $row['Path'];*/
            echo "song.php?path=/Users/williampoynter/Music/iTunes/iTunes Media/Music/Pink Floyd/The Wall-Disc 1/01 In The Flesh.mp3";
            exit();
?>
