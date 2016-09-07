# php_webdav扩展

一个很简单的php_webdav扩展，仅仅用来研究webdav协议的原理

- 支持文件的上传
- 支持文件的下载



#安装


```bash
cd php_webdav
phpize
./configure --with-php-config={your_php_bin_path}/php-config
make && sudo make install

```

# 使用

```php
<?php
$web = new Webdav("webdav.iliubang.cn");
var_dump($web);
//本地文件，目标路径
$res = $web->upload("1.jpg", "/test/1.jpg",);
var_dump($res);
//远程文件，存放的本地路径
$res = $webdav->get("/test/4.jpg", "/home/liubang/workspace/c/php_webdav/4.jpg");
var_dump($res);


==================
liubang@shop-dev:~ $ php test.php
object(Webdav)#1 (1) {
  ["_host":protected]=>
  string(18) "webdav.iliubang.cn"
}
bool(true)
bool(true)

```