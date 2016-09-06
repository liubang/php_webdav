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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <getopt.h>
#include "php_webdav.h"


zend_class_entry *webdav_ce;

static int error(char *err){
	perror(err);
	exit(EXIT_FAILURE);
}

char *file_content(char * file_location, size_t *size){
	FILE *shell;
	unsigned char *buffer;
	shell = fopen(file_location,"r");
	if(shell == NULL)
		error(file_location);

	fseek(shell, 0, SEEK_END);
	size = ftell(shell);
	fseek(shell, 0, SEEK_SET);

	buffer = (char *)malloc(size+1);
	fread(buffer,1,size,shell);
	fclose(shell);
	return buffer;
}

static char* substring(char *ch, int pos, int length)
{
	char *pch = ch;
	char *subch = (char *)malloc(sizeof(char) * (length + 1));

	int i;
	pch = pch + pos;
	for (i = 0; i < length; i++)
	{
		subch[i] = *(pch++);
	}

	subch[length] = '\0';
	return subch;
}

static int request(char *target, char *file, char *create, char *path, char **response)
{
	size_t size;
	unsigned char *conteudo = file_content(file, &size);
	int msocket,recebidos;
	char resposta[5000];
	struct sockaddr_in addr;

	msocket = socket(AF_INET, SOCK_STREAM, 0);
	if(msocket == -1)
		error("Fail to create socket ");

	struct hostent *host;
	host = gethostbyname(target);

	if(host == NULL)
		error("Fail to gethostbyname ");

	addr.sin_family 	= host->h_addrtype;
	addr.sin_port		= htons(80);
	addr.sin_addr		= *((struct in_addr *)host->h_addr);

	memset(&addr.sin_zero,0,sizeof(addr.sin_zero));

	if(connect(msocket,(struct sockaddr*)&addr,sizeof(addr)) == -1)
		error("Fail to connect");

	char *put = malloc(1024);

	sprintf(put,"PUT %s%s HTTP/1.1\r\nContent-Length: %d\r\nHost: %s\r\nConnection: close\r\n\r\n",path,create,size,target);

	if (send(msocket,put,strlen(put),0) < 0) {
		error("Fail to send header");
	}
	if (send(msocket,(void *)conteudo, size, 0) < 0) {
		error("Fail to send content");
	}

	while((recebidos = recv(msocket,resposta,5000,0))){
		resposta[recebidos] = '\0';
		*response = resposta;
	}

	close(msocket);
	free(put);
	return 0;
}

PHP_METHOD(webdav, __construct)
{
	char *host;
	int host_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &host, &host_len) == FAILURE)
		RETURN_FALSE;
	zend_update_property_string(webdav_ce, getThis(), ZEND_STRL(PROPERTIES_HOST), host TSRMLS_CC);
}

const zend_function_entry webdav_methods[] = {
		PHP_ME(webdav, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
		PHP_ME(webdav, upload, NULL, ZEND_ACC_PUBLIC)
		{NULL, NULL, NULL}
};

PHP_METHOD(webdav, upload)
{
	char *file;
	int file_len;
	char *create;
	int create_len;
	char *path;
	int path_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss", &file, &file_len, &create, &create_len, &path, &path_len) ==  FAILURE)
		RETURN_FALSE;

	char *response;
	zval *z_host;
	char *host;
	z_host = zend_read_property(webdav_ce, getThis(), ZEND_STRL(PROPERTIES_HOST), 0 TSRMLS_CC);
	host = Z_STRVAL_P(z_host);

	if (request(host, file, create, path, &response) == 1) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "%s", "上传文件失败");
	}

	char *status_code = substring(response, 9, 3);
	if (strcmp(status_code, "204") == 0 || strcmp(status_code, "201") == 0) {
		RETURN_TRUE;
	}
	RETURN_STRING(status_code, 1);
}

PHP_MINIT_FUNCTION(webdav)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "Webdav", webdav_methods);
	webdav_ce = zend_register_internal_class(&ce TSRMLS_CC);
	zend_declare_property_null(webdav_ce, ZEND_STRL(PROPERTIES_HOST), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(webdav)
{
	return SUCCESS;
}

PHP_RINIT_FUNCTION(webdav)
{
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(webdav)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(webdav)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "webdav support", "enabled");
	php_info_print_table_end();
}


zend_module_entry webdav_module_entry = {
	STANDARD_MODULE_HEADER,
	"webdav",
	NULL,
	PHP_MINIT(webdav),
	PHP_MSHUTDOWN(webdav),
	PHP_RINIT(webdav),		
	PHP_RSHUTDOWN(webdav),	
	PHP_MINFO(webdav),
	PHP_WEBDAV_VERSION,
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_WEBDAV
ZEND_GET_MODULE(webdav)
#endif
