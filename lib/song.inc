<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of song
 *
 * @author williampoynter
 */
class Song {
    
    private $title, $artist, $album, $length, $path, $SID;
    
    
    public function __construct($title = "", $artist = "", $album = "", $length = "", $path = "", $SID = "", $type= "") {
        
        $this->SID = $SID;
        $this->title = $title;
        $this->artist = $artist;
        $this->album = $album;
        $this->length = $length;
        $this->path = $path;
        $this->type = $type;
    }
    
    public function format($layout = "table",$style = "even") {

        if ($layout == "table")
            if ($style == "even")
                return "<tr class='even-row'><td><a ondblClick=songDblClick(" . $this->SID . ") href='javascript://' >" . substr($this->title,0,40) . "</a></td><td>" . $this->getLength() . "</td></tr>";
            elseif ($style == "odd")
                return "<tr class='odd-row'><td><a ondblClick=songDblClick(" . $this->SID . ") href='javascript://' >" . substr($this->title,0,40) . "</a></td><td>" . $this->getLength() . "</td></tr>";
        return false;
    }
    
    public function getLength($format = "i:s") {
        return date($format,round($this->length));
    }
    
    public function get($var) { return $this->$var;}
    public function set($var,$val) {
        
        $this->$var = $val;
        return true;
    }
    
}

function sortSongs($songs = array(), $value = "title") {
        
    function cmpSong ($a, $b) {

        return strcmp(strtolower($a->get($value)),  strtolower($b->get($value)));
    } 

    uasort($songs, "cmpSong");
    return true;
 }

?>
