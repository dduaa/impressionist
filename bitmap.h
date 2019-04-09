//
// bitmap.h
//
// header file for MS bitmap format
//
//

#ifndef BITMAP_H
#define BITMAP_H

#ifndef BITMAP_H										// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <vfw.h>												// Header File For Video For Windows
//#include "NeHeGL.h"
//#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BMP_BI_RGB        0L

typedef unsigned short	BMP_WORD; 
typedef unsigned int	BMP_DWORD; 
typedef int				BMP_LONG; 
 
typedef struct { 
	BMP_WORD	bfType; 
	BMP_DWORD	bfSize; 
	BMP_WORD	bfReserved1; 
	BMP_WORD	bfReserved2; 
	BMP_DWORD	bfOffBits; 
} BMP_BITMAPFILEHEADER; 
 
typedef struct { 
	BMP_DWORD	biSize; 
	BMP_LONG	biWidth; 
	BMP_LONG	biHeight; 
	BMP_WORD	biPlanes; 
	BMP_WORD	biBitCount; 
	BMP_DWORD	biCompression; 
	BMP_DWORD	biSizeImage; 
	BMP_LONG	biXPelsPerMeter; 
	BMP_LONG	biYPelsPerMeter; 
	BMP_DWORD	biClrUsed; 
	BMP_DWORD	biClrImportant; 
} BMP_BITMAPINFOHEADER; 

// global I/O routines
extern unsigned char* readBMP( char* fname, int& width, int& height );
extern void writeBMP( char* iname, int width, int height, unsigned char* data ); 

#endif