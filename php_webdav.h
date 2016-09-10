/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: liubang <it.liubang@gmail.com>                               |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_WEBDAV_H
#define PHP_WEBDAV_H

extern zend_module_entry webdav_module_entry;
#define phpext_webdav_ptr &webdav_module_entry

#define PHP_WEBDAV_VERSION 				"0.1.0"
#define PHP_WEBDAV_AUTHOR				"liubang <it.liubang@gmail.com>"
#define PROPERTIES_HOST					"_host"

#define BUF_SIZE 	20480
#define SOCK_PORT	80

typedef int sockopt_t;


#ifdef PHP_WIN32
#	define PHP_WEBDAV_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_WEBDAV_API __attribute__ ((visibility("default")))
#else
#	define PHP_WEBDAV_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#ifdef ZTS
#define WEBDAV_G(v) TSRMG(webdav_globals_id, zend_webdav_globals *, v)
#else
#define WEBDAV_G(v) (webdav_globals.v)
#endif

PHP_METHOD(webdav, __construct);
PHP_METHOD(webdav, upload);
PHP_METHOD(webdav, get);
PHP_METHOD(webdav, delete);

#endif	/* PHP_WEBDAV_H */
