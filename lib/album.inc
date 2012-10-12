<?php
/**
 * Description of album
 *
 * @author williampoynter
 */

class albumList {
    
    private $Albums;
    
    public function __construct($albumList = "") {
        
        $this->Albums = array();
        if (!empty($albumList) && is_object($albumList))
        $this->mergeList($albumList);
    }
    
    public function newAlbum(song $song) {
        
        foreach ($this->Albums as $album) 
            if ($album->get("Name") == $song->get("album")) {
            $album->addSong($song);
            return 1;
        }
            $album = new album("",$song->get("album"));
            array_push($this->Albums, $album);
            end($this->Albums);
            end($this->Albums)->set("ALID", key($this->Albums));
            end($this->Albums)->addSong($song);
    }
    
    public function addAlbum(album $album) {

        $this->Albums[$album->get("ALID")] = $album;
    }
    
    public function sort() {
        
        function cmpAlb ($a, $b) {
                
            return strcmp(strtolower($a->get("Name")),  strtolower($b->get("Name")));
        } 

        uasort($this->Albums, "cmpAlb");
        return true;
    }
    
    public function output($SIDs = array(), $format = "table", $style="even"){
        
        if (empty($this->Albums)) return "";
        switch ($format) {
            case "table":
            default :
                $output = "";
                foreach ($this->Albums as $album)
                    if (empty ($SIDs)) $output .= "<tr id='album-" . $album->get("ALID") . "' ><td><a href='javascript://' onClick='albumClick(" . $album->get("ALID") . ")'>" . $album->get("Name") . "</a></td></tr>";
                    else if ($album->hasSongIDs($SIDs)) $output .= "<tr id='album-" . $album->get("ALID") . "' ><td><a href='javascript://' onClick='albumClick(" . $album->get("ALID") . ")'>" . $album->get("Name") . "</a></td></tr>";
                    break;
        }
        return $output;
    }
    
    public function getList() { return $this->Albums; }
    
    public function mergeList(albumList $list) {
        
        $this->Albums=$this->Albums+$list->getList();
    }
    
    public function getAlbum($ALID) { return $this->Albums[$ALID];}
}


class album {
    
    private $ALID, $Name;
    private $Songs;
    
    public function __construct($ALID = "", $Name = "") {
        
        $this->ALID = $ALID;
        $this->Name = $Name;
        $this->Songs = array();
    }
        
    public function addSong(song $song) {
        
        array_push($this->Songs, $song);
    }
    
    public function format($layout = "table",$style = "even") {

        if ($layout == "table")
            if ($style == "even")
                return "<tr class='even-row'><td><a onClick=albumClick(" . $this->ALID . ") href='javascript://' >" . $this->Name . "</a></td></tr>";
            elseif ($style == "odd")
                return "<tr class='odd-row'><td><a onClick=albumClick(" . $this->ALID . ") href='javascript://' >" . $this->Name . "</a></td></tr>";
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
