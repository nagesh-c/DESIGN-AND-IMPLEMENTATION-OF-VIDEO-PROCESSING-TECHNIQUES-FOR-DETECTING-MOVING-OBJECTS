/* header for dwt operation */ 

#ifndef __DWT_H__
#define __DWT_H__

#define ALPHA 0.55
// struct to store three sub bands
struct subands
{
	int *lh;
	int *hl;
	int *hh;
};

// dwt with normalization (for experimentation)
AVFrame* dwt(AVFrame *frame,int width,int height,int level);

//same as dwt above but no normalization and return sub bands struture
struct subands* dwt2(uint8_t *frame,int width,int height,int level,struct subands *s);

//key frame determination algortihm uses DWT and params in corresponding .cpp file
bool is_key_frame(uint8_t *image,int width,int height,int frame_num);

#endif /* end of dwt.h */
