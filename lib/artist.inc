<?php
/**
 * Description of artist
 *
 * @author williampoynter
 */

class artistList {
    
    private $Artists;
    
    public function __construct($artistList = "") {
        
        $this->Artists = array();
        if (!empty($artistList) && is_object($artistList))
        $this->mergeList($artistList);
    }
    
    public function newArtist(song $song) {
        
        foreach ($this->Artists as $artist) 
            if ($artist->get("Name") == $song->get("artist")) {
            $artist->addSong($song);
            return 1;
        }
            $artist = new artist("",$song->get("artist"));
            array_push($this->Artists, $artist);
            end($this->Artists);
            end($this->Artists)->set("ARID", key($this->Artists));
            end($this->Artists)->addSong($song);
    }
    
    public function addArtist(artist $artist) {

        $this->Artists[$artist->get("ARID")] = $artist;
    }
    
    public function sort() {
        
        function cmpArt ($a, $b) {
                
            return strcmp(strtolower($a->get("Name")),  strtolower($b->get("Name")));
        } 

        uasort($this->Artists, "cmpArt");
        return true;
    }
    
    public function output($SIDs = array(), $format = "table", $style="even"){
        
        if (empty($this->Artists)) return "";
        switch ($format) {
            case "table":
            default :
                $output = "";
                foreach ($this->Artists as $artist)
                    if (empty ($SIDs)) $output .= "<tr id='artist-" . $artist->get("ARID") . "' ><td><a href='javascript://' onClick='artistClick(" . $artist->get("ARID") . ")'>" . $artist->get("Name") . "</a></td></tr>";
                    else if ($artist->hasSongIDs($SIDs)) $output .= "<tr id='artist-" . $artist->get("ARID") . "' ><td><a href='javascript://' onClick='artistClick(" . $artist->get("ARID") . ")'>" . $artist->get("Name") . "</a></td></tr>";
                break;
        }
        return $output;
    }
    
    public function getList() { return $this->Artists; }
    
    public function mergeList(artistList $list) {
        
        $this->Artists=$this->Artists+$list->getList();
    }
    
    public function getArtist($ARID) { return $this->Artists[$ARID];}
}

class artist {
    
    private $ARID, $Name;
    private $Songs;
    
    public function __construct($ARID = "", $Name = "") {
        
        $this->ARID = $ARID;
        $this->Name = $Name;
        $this->Songs = array();
    }
    
    public function addSong(song $song) {
        
        array_push($this->Songs, $song);
    }
    
    
    public function format($layout = "table",$style = "even") {

        if ($layout == "table")
            if ($style == "even")
                return "<tr id='artist-" . $this->ARID . "' class='even-row'><td><a onClick=artistClick(" . $this->ARID . ") href='javascript://' >" . $this->Name . "</a></td></tr>";
            elseif ($style == "odd")
                return "<tr id='artist-" . $this->ARID . "' class='odd-row'><td><a onClick=artistClick(" . $this->ARID . ") href='javascript://' >" . $this->Name . "</a></td></tr>";
        return false;
    }
    
    public function getSongIDs() {
        $output = array();
        foreach ($this->Songs as $song) {
            $output[] = $song->get("SID");
        }
        return $output;
    }
    
    public function hasSongIDs($SIDs) {
        
        foreach ($this->Songs as $song) {
            if (in_array($song->get("SID"),$SIDs)) return true;
        }
        return false;
    }
    
    
    public function get($var) { return $this->$var;}
    public function set($var,$val) {
        
        $this->$var = $val;
        return true;
    }
  
}

?>
