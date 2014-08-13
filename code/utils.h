/* headers for all utility functions */
#ifndef __UTILS_H__
#define __UTILS_H__

/* function to convert regular RGB image to grey scale */
void rgb_to_gray(AVFrame *pFrame,uint8_t *pFrameGray,int width,int height);

/* generate P6 or P5 ppm file to save frame as image */
void write_to_ppm(AVFrame *pframe,int width,int height,char *type,ofstream &fp);
void write_to_ppm(uint8_t *pframe,int width,int height,char *type,FILE *fp);

/* erosion operation (post-processing) */
void erode(uint8_t *a,int width, int height,uint8_t *kernel, int k_size);

/*dilation operation (post-processing) */
void dilate(uint8_t *a,int width, int height,uint8_t *kernel, int k_size);

/*Canny Edge Detection*/
bool canny(uint8_t *image,int width,int height);

/* Gaussian blur*/
void gaussian(uint8_t * image, int height, int width, int *gaussianMask);

/*ostu thresholding*/
int ostu( uint8_t * image, int height,int width);

/* get gray 8 bit pixel from a frame */
inline uint8_t get_gray_pixel(int x,int y,AVFrame *pFrame)
{
	uint8_t p=*(pFrame->data[0]+x*pFrame->linesize[0]+y);
	return p;
}

/* put gray 8 bit pixel to a frame */
inline void put_gray_pixel(uint8_t p,int x,int y,AVFrame *pFrame)
{
	*(pFrame->data[0]+x*pFrame->linesize[0]+y)=p;
}
#endif /* end of utils.h*/
