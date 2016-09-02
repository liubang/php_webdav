PHP_ARG_ENABLE(webdav, whether to enable webdav support,
[  --enable-webdav           Enable webdav support])



if test "$PHP_WEBDAV" != "no"; then
  PHP_SUBST(WEBDAV_SHARED_LIBADD)

  PHP_NEW_EXTENSION(webdav, webdav.c, $ext_shared)
fi