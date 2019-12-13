<?php
$file = "cache.log";
$handle= fopen($file,"r");
$data = "";
 while (!feof ($handle)) {
 $buffer  = fgets($handle, 50000);

     $buffer = trim($buffer);
     if($buffer){
     if(!$data)
     {
        $data = $buffer;
     }else{
     if($buffer != $data)
     {
     var_dump(false);
     }else{
     }
     }
     }
 }
