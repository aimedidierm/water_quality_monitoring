<?php
ini_set('display_errors',1);
ini_set('display_startup_errors',1);
error_reporting(E_ALL);
require 'php-includes/connect.php';
if(isset($_POST['temp'])&&($_POST['ppm'])){
    $temp=$_POST['temp'];
    $ppm=$_POST['ppm'];
    $sql ="INSERT INTO lever (c,ppm) VALUES (?,?)";
    $stm = $db->prepare($sql);
    $stm->execute(array($temp,$ppm));
}
?>