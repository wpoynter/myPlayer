<?php

require_once('lib/user.inc');

session_start();

if (!empty($_POST['fusername']) && !empty($_POST['fpassword'])) {
    $user = new user();
    if (!$user->login($_POST['fusername'], $_POST['fpassword'])) {
        
        include('login.inc');
        echo "<style type='javascript/text'>\n";
        echo "document.getElementById('notice').innerHTML='<span>Nope no good!</span>'";
        echo "\n</style>";
        exit();
    }
   $_SESSION['user'] = $user;     
}

if (empty($_SESSION['user']) || !$_SESSION['user']->allowed()) {
    include('login.inc');
    exit();
}

include("home.html");

?>
