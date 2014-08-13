#include "headers.h"

/* function to convert RGB image to grey scale */
void rgb_to_gray(AVFrame *pFrame,uint8_t *pFrameGray,int width,int height)
{
	uint8_t *rgb=pFrame->data[0];
	int rgbsize=pFrame->linesize[0];
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			pFrameGray[i*width+j]=.299f*rgb[i*rgbsize+3*j]+.587f*rgb[i*rgbsize+3*j+1]+.114f*rgb[i*rgbsize+3*j+2];
		}
	}
}
/*generate ppm image file frame frame */
void write_to_ppm(AVFrame *pFrame,int width,int height,char *type,ofstream &pFile)
{
	int x,y,pixel_width=1;
	pFile<<type<<"\n"<<width<<" "<<height<<"\n255\n";
	if(type[1]=='6')
		pixel_width=3;
	// Write pixel data
	for(y=0; y<height; y++)
		pFile.write((char*)pFrame->data[0]+y*pFrame->linesize[0],width*pixel_width);
}
void write_to_ppm(uint8_t *pFrame,int width,int height,char *type,FILE *pFile)
{
	int x,y;
	fprintf(pFile, "%s\n%d %d\n255\n",type, width, height);
	// Write pixel data
	for(x=0;x<height;x++)
		for(y=0; y<width; y++)
			fputc((uint8_t)pFrame[x*width+y],pFile);
}
void erode(uint8_t *a,int width, int height,uint8_t *kernel, int k_size)
{
	uint8_t *b = new uint8_t[width*height];
	int i;
	
	int j,k,l,mid=k_size/2;
	for(i=1;i<height-1;i++)
	{
		for(j=1;j<width-1;j++)
		{
			b[i*width+j]=255;
			if(a[i*width+j]!=255)
			{
				b[i*width+j]=0;
				continue;
			}
			for(k=0;k<k_size;k++)
			{
				for(l=0;l<k_size;l++)
				{
					if(kernel[k*k_size+l]!=a[(i+k-mid)*width+(j+l-mid)])
					{
						b[i*width+j]=0;
						break;
					}
				}
				if(l!=k_size)
					break;
			}
		}
	}
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
			a[i*width+j]=b[i*width+j];
delete[] b;
}
void dilate(uint8_t *a,int width, int height,uint8_t *kernel, int k_size)
{
	uint8_t *b = new uint8_t[width*height];
    
	int i;
	//int **b = new int*[width];
	int j,k,l,mid=k_size/2;
	for(i=1;i<height-1;i++)
	{
		for(j=1;j<width-1;j++)
		{
			b[i*width+j]=0;
			if(a[i*width+j]!=0)
			{
				b[i*width+j]=255;
				continue;
			}
			for(k=0;k<k_size;k++)
			{
				for(l=0;l<k_size;l++)
				{
					if(kernel[k*k_size+l]!=a[(i+k-mid)*width+(j+l-mid)])
					{
						b[i*width+j]=255;
						break;
					}
				}
				if(l!=k_size)
					break;
			}
		}
	}
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
			a[i*width+j]=b[i*width+j];
delete[] b;
}
void gaussian(uint8_t * image, int height, int width, int *gaussianMask)
{
	int x,y,rowOffset,colOffset, colTotal,rowTotal,neighbourOffset;
	for (x = 2; x < height-2; x++) 
		{
			for (y = 2; y < width-2; y++)
		       	{
				int newPixel = 0;
				for ( rowOffset=-2; rowOffset<=2; rowOffset++) 
				{
					for (colOffset=-2; colOffset<=2; colOffset++) 
					{
						rowTotal = x + rowOffset;
						colTotal = y + colOffset;
						neighbourOffset = rowTotal*width + colTotal;
						newPixel += image[neighbourOffset] * gaussianMask[((2 + rowOffset) * 5) + (2 + colOffset)];
					}
				}
				image[x * width + y] = newPixel / 159;
			}
		}
}

int ostu( uint8_t * image, int height,int width)
{

	int hist[256] ;
	double prob[256], omega[256]; /* prob of graylevels */
	double myu[256];   /* mean value for separation */
      	double max_sigma, sigma[256]; /* inter-class variance */
  	int i, x, y; 
  	int threshold; /* threshold*/
  
 	 /* Histogram generation */
 	 for (i = 0; i < 256; i++) 
		 hist[i] = 0;
  	for (x = 0; x < height; x++)
	{
    		for (y = 0; y < width; y++) 
		{	i = x * width + y;
      			hist[image[i]]++;
    		}
	}
	
	  /* calculation of probability density */
  	for ( i = 0; i < 256; i ++ ) 
	{
    		prob[i] = (double)hist[i] / (height * width);
  	}
  
  	/* omega & myu generation */
  	omega[0] = prob[0];
 	myu[0] = 0.0;       

  	for (i = 1; i < 256; i++)
       	{
    		omega[i] = omega[i-1] + prob[i];
    		myu[i] = myu[i-1] + i*prob[i];
  	}
  
  	/* sigma maximization
     	sigma stands for inter-class variance 
     	and determines optimal threshold value */
  
	threshold = 0;
 	 max_sigma = 0.0;
  	for (i = 0; i < 255; i++) 
	{
    		if (omega[i] != 0.0 && omega[i] != 1.0)
		{

      			sigma[i] = pow(myu[255]*omega[i] - myu[i], 2)/ (omega[i]*(1.0 - omega[i]));
		}
    		else
		{
      			sigma[i] = 0.0;
		}
    		if (sigma[i] > max_sigma) 
		{
      			max_sigma = sigma[i];
      			threshold = i;
    		}
  	}
	return threshold;

}

