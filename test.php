<?php

$webdav = new Webdav("linger.iliubang.cn");

$arr = array('name' => 'liubang', 'age' => 23);
$res = $webdav->post('/', $arr);

var_dump($res);

//var_dump($webdav);

//$res = $webdav->upload("Makefile", "/test/Makefile");
//var_dump($res);


//$res = $webdav->get("/test/4.jpg", "/home/liubang/workspace/c/php_webdav/4.jpg");

//var_dump($res);

// $res = $webdav->delete('/test/Makefil');
//var_dump($res);

