<script type="text/javascript">
function myNewSrc() {
    if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
    //alert(xmlhttp.responseText);
    var myAudio = document.getElementById("livesearch");
    myAudio.src = "song.php?path="+xmlhttp.responseText;
    myAudio.load();
    myAudio.play();
    updateLists();
    myAudio.addEventListener('ended', myNewSrc, false);
    }
  }
xmlhttp.open("GET","music.php?FLAG=NEXT",true);
xmlhttp.send();
}
function songDblClick(str)
{
if (str.length==0)
  { 
  return;
  }
if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
    //alert(xmlhttp.responseText);
    document.getElementById("livesearch").src="song.php?path="+xmlhttp.responseText;
    document.getElementById("livesearch").load();
    document.getElementById("livesearch").play();
    updateLists("");
    document.getElementById("livesearch").addEventListener('ended', myNewSrc, false);
    }
  }
xmlhttp.open("GET","music.php?FLAG=songToPlay&SID="+str,true);
xmlhttp.send();
}

function artistClick(str)
{
if (str.length==0)
  { 
  return;
  }
if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
        updateLists("document.getElementById('artist-"+str+"').className='highlight'");
        //document.getElementById("artist-"+str).style.background="blueViolet";
    }
  }
xmlhttp.open("GET","music.php?FLAG=artistSelected&ARID="+str,true);
xmlhttp.send();
}

function albumClick(str)
{
if (str.length==0)
  { 
  return;
  }
if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
        updateLists("document.getElementById('album-"+str+"').className='highlight'");
        //document.getElementById("artist-"+str).style.background="blueViolet";
    }
  }
xmlhttp.open("GET","music.php?FLAG=albumSelected&ALID="+str,true);
xmlhttp.send();
}

function updateLists(command)
{
if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
    var JSONtext = xmlhttp.responseText;
    var JSONobject = JSON.parse(JSONtext);
    document.getElementById("track-queue").innerHTML=JSONobject.queue;
    document.getElementById("song-list").innerHTML=JSONobject.songs;
    document.getElementById("artists-list").innerHTML=JSONobject.artists;
    document.getElementById("albums-list").innerHTML=JSONobject.albums;
    if (command.length!=0)
    { 
    eval(command);
    }
    }
  }
xmlhttp.open("GET","music.php?FLAG=UPDATE",true);
xmlhttp.send();
}

function nextTrack() {
    myNewSrc();
}

function makeRate(rate) {
    
    if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
         document.getElementById("rate-"+rate).style.fontWeight="800";
         //alert('Changed to '+rate+'k');
    }
  }
xmlhttp.open("GET","music.php?FLAG=changeRate&rate="+rate,true);
xmlhttp.send();
}

</script>