<?php

$webdav = new Webdav("webdav.iliubang.cn");

var_dump($webdav);

$res = $webdav->upload("1.jpg", "/text/3.jpg");
var_dump($res);
