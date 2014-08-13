/*****************************************************

This file has all headers to be included 
including this file is suffice to access all functions

******************************************************/

#ifndef __HEADERS_H__
#define __HEADERS_H__

/* standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* Work around for a bug in FFmpeg that prevents C++ access to Fmpeg lib */
#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

/* FFmpeg headers They are C headers hence to use with C++ declare as extern */
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


//UNIX headers
//#include<unistd.h>

//C++ headers
#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
using namespace std;

/* User defined headers */
#include "dwt.h"
#include "utils.h"
#include "ViBE.h"

#endif /* end of headers.h */