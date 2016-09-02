cmake_minimum_required(VERSION 3.5)
project(php_webdav)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(Boost_INCLUDE_DIR /opt/app/php-5.6/include/)

set(SOURCE_FILES
    autom4te.cache/output.0
    autom4te.cache/requests
    autom4te.cache/traces.0
    build/libtool.m4
    build/mkdep.awk
    build/scan_makefile_in.awk
    build/shtool
    modules/webdav.la
    modules/webdav.so
    tests/001.phpt
    acinclude.m4
    aclocal.m4
    config.guess
    config.h
    config.h.in
    config.log
    config.m4
    config.nice
    config.status
    config.sub
    config.w32
    configure
    configure.in
    CREDITS
    EXPERIMENTAL
    install-sh
    libtool
    ltmain.sh
    Makefile
    Makefile.fragments
    Makefile.global
    Makefile.objects
    missing
    mkinstalldirs
    php_webdav.h
    run-tests.php
    webdav.c
    webdav.la
    webdav.lo
    webdav.php)

add_executable(php_webdav ${SOURCE_FILES})