PBKDF2-GCC-PolarSSL-source
==========================

GCC and PolarSSL library based PBKDF2 implementation. Works in Linux and Windows with MinGW.


Ideally, you should download your own copy of PolarSSL source code and compile it yourself (at this time, 1.3.4 is what it was compiled with) and extract it so that you have (assume backslashes on Windows, obviously):
pbkdf2_polarssl.c
config.h
etc.
etc.
polarssl-1.3.4/include/*
polarssl-1.3.4/library/*

The Releases section will have the source code used to compile each particular executable, as well as the executable itself.

To compile on Windows, the easiest way is to install MinGW via the MinGW Builds installer, which can be found at http://sourceforge.net/projects/mingwbuilds/    (or, apparently, at links off of there since they've joined the overall MinGW-w64 project for both 32-bit and 64-bit Windows MinGW).
