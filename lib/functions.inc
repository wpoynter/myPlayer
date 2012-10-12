<?php

function setKill($input) {
    if ($input != 0 && $input != 1) return false;
    $handle = fopen("/var/tmp/kill-switch.dat", "w+");
    if (!$handle) return false;
    if (!fwrite($handle, (int)$input)) {fclose($handle); return false;}
    return fclose($handle);
}

function checkKill() {
    $handle = fopen("/var/tmp/kill-switch.dat", "r");
    if (!$handle) return false;
    $data = fread($handle,10);
    if (!fclose($handle)) return false;
    if ($data === false) return false;
    if ($data == 0) return 0;
    if ($data == 1) return 1;
    return false;
}

?>
