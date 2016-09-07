<?php

$webdav = new Webdav("webdav.iliubang.cn");

var_dump($webdav);

$res = $webdav->upload("1.jpg", "/test/4.jpg");
var_dump($res);


$res = $webdav->get("/test/4.jpg", "/home/liubang/workspace/c/php_webdav/4.jpg");

var_dump($res);

