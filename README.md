# php_webdav扩展

一个很简单的php_webdav扩展，仅仅用来研究webdav协议的原理
只支持较小文件上传操作

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
$res = $web->upload("test.log", "test.log", "/test/");
var_dump($res);

==================
liubang@shop-dev:~ $ php test.php
object(Webdav)#1 (1) {
  ["_host":protected]=>
  string(18) "webdav.iliubang.cn"
}
bool(true)

```