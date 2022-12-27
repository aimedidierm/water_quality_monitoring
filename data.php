<?php
ini_set('display_errors',1);
ini_set('display_startup_errors',1);
error_reporting(E_ALL);
require 'php-includes/connect.php';
if(isset($_REQUEST['temp'])&&($_REQUEST['ppm'])){
    $temp=$_REQUEST['temp'];
    $ppm=$_REQUEST['ppm'];
    $sql ="INSERT INTO lever (c,ppm) VALUES (?,?)";
    $stm = $db->prepare($sql);
    $stm->execute(array($temp,$ppm));
}
?>