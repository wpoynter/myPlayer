<?php
/**
 * @author Multi-threaded script by Nicolas Iglesias
 * @copyright 2008
 */
require_once ("thread_class.php");
$pathToPhp = "/usr/bin/php";
$A = new Threader("$pathToPhp -f test.php",null, "a");

/**
 * First argument: external script or command (required).
 * Second argument: arguments that your external script or command will receive (optional).
 * Third argument: name of thread (optional).
 */
$B = new Threader("$pathToPhp -f test.php",null, "b");
$C = new Threader("$pathToPhp -f test.php",null, "c");
$D = new Threader("$pathToPhp -f test.php",null, "d");
$E = new Threader("$pathToPhp -f test.php",null, "e");
$F = new Threader("$pathToPhp -f test.php",null, "f");

/**
 * We check if any of the 'active' states of our threads are true;
 * then we display its output using 'listen'.
 */
while ($A->active || $B->active || $C->active || $D->active || $E->active || $F->
    active)
{
    echo "[Thread ".$A->threadName."] => " . $A->listen();
    echo "[Thread ".$B->threadName."] => " . $B->listen();
    echo "[Thread ".$C->threadName."] => " . $C->listen();
    echo "[Thread ".$D->threadName."] => " . $D->listen();
    echo "[Thread ".$E->threadName."] => " . $E->listen();
    echo "[Thread ".$F->threadName."] => " . $F->listen();
}
?>