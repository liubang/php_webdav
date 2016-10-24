<?php

$webdav = new Webdav("linger.iliubang.cn");

//$arr = array('name' => 'liubang', 'age' => 23, 'gender' => 'nan');
// $res = $webdav->post('/', "name=liubang&age=sadgad");
//$res = $webdav->post('/', $arr);

//echo $res;


$res = $webdav->upload("Makefile", "/test/Makefile");
var_dump($res);


//$res = $webdav->get("/test/4.jpg", "/home/liubang/workspace/c/php_webdav/4.jpg");

//var_dump($res);

// $res = $webdav->delete('/test/Makefil');
//var_dump($res);

