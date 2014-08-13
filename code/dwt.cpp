#include "headers.h"

struct subands *f1=NULL,*f2=NULL,*f3=NULL;
int deviation1=0,deviation2=0,deviation3=0;
float mean1=0,mean2=0,mean3=0;
float var1=0,var2=0,var3=0;
float std1=0,std2=0,std3=0;
int th1=0,th2=0,th3=0;

AVFrame* dwt(AVFrame *src,int width,int height,int level)
{
	int c,dh,dv,dd,i,**temp;
	AVFrame *dst=avcodec_alloc_frame();
	int numbytes=avpicture_get_size(PIX_FMT_GRAY8,width,height);
	uint8_t *buffer=(uint8_t*)av_malloc(numbytes);
	//int temp[height][width];
	assert(!(width > 0 && height > 0));
	
	temp = new int*[width];
	
	for(i=0;i<width;i++)
		temp[i] = new int[height];
	
	avpicture_fill((AVPicture *)dst,buffer,PIX_FMT_GRAY8,width,height);
	int min=511,max=0;
	for(int k=0;k<level;k++)
	{
		for (int y=0;y<(height>>(k+1));y++)
		{
			for (int x=0; x<(width>>(k+1));x++)
			{
				c=(get_gray_pixel(2*y,2*x,src)+get_gray_pixel(2*y,2*x+1,src)+get_gray_pixel(2*y+1,2*x,src)+get_gray_pixel(2*y+1,2*x+1,src))*0.5;
				//put_gray_pixel(c,y,x,dst);
				temp[y][x]=c;
				min=(temp[y][x]<min)?temp[y][x]:min;
				max=(temp[y][x]>max)?temp[y][x]:max;

				dh=(get_gray_pixel(2*y,2*x,src)+get_gray_pixel(2*y+1,2*x,src)-get_gray_pixel(2*y,2*x+1,src)-get_gray_pixel(2*y+1,2*x+1,src))*0.5;
				//put_gray_pixel(dh,y,x+(width>>(k+1)),dst);
				temp[y][x+(width>>(k+1))]=dh;
				min=(temp[y][x+(width>>(k+1))]<min)?temp[y][x+(width>>(k+1))]:min;
				max=(temp[y][x+(width>>(k+1))]>max)?temp[y][x+(width>>(k+1))]:max;
				

				dv=(get_gray_pixel(2*y,2*x,src)+get_gray_pixel(2*y,2*x+1,src)-get_gray_pixel(2*y+1,2*x,src)-get_gray_pixel(2*y+1,2*x+1,src))*0.5;
				//put_gray_pixel(dv,y+(height>>(k+1)),x,dst);
				temp[y+(height>>(k+1))][x]=dv;
				min=(temp[y+(height>>(k+1))][x]<min)?temp[y+(height>>(k+1))][x]:min;
				max=(temp[y+(height>>(k+1))][x]>max)?temp[y+(height>>(k+1))][x]:max;

				dd=(get_gray_pixel(2*y,2*x,src)-get_gray_pixel(2*y,2*x+1,src)-get_gray_pixel(2*y+1,2*x,src)+get_gray_pixel(2*y+1,2*x+1,src))*0.5;
				//put_gray_pixel(dd,y+(height>>(k+1)),x+(width>>(k+1)),dst);
				temp[y+(height>>(k+1))][x+(width>>(k+1))]=dd;
				min=(temp[y+(height>>(k+1))][x+(width>>(k+1))]<min)?temp[y+(height>>(k+1))][x+(width>>(k+1))]:min;
				max=(temp[y+(height>>(k+1))][x+(width>>(k+1))]>max)?temp[y+(height>>(k+1))][x+(width>>(k+1))]:max;
			}
		}
	}
	for(int y=0;y<height;y++)
		for(int x=0;x<width;x++)
			put_gray_pixel((uint8_t)(temp[y][x]*(255.0/(max-min))-(double)(min/(max-min))),y,x,dst);
	return dst;
for(i=0;i<width;i++)
	delete[] temp[i];
delete[] temp;
}
struct subands* dwt2(uint8_t *src,int width,int height,int level,struct subands *s)
{
	int width_t=width>>1;
	int height_t=height>>1;

		for (int y=0;y<height_t;y++)
		{
			for (int x=0; x<width_t;x++)
			{
/*				c=(get_gray_pixel(2*y,2*x,src)+get_gray_pixel(2*y,2*x+1,src)+get_gray_pixel(2*y+1,2*x,src)+get_gray_pixel(2*y+1,2*x+1,src))*0.5;
				//put_gray_pixel(c,y,x,dst);
				temp[y][x]=c;
*/
				s->lh[y*width_t+x]=(src[2*y*width+2*x]+src[(2*y+1)*width+2*x]-src[2*y*width+2*x+1]-src[(2*y+1)*width+2*x+1])*0.5;	
				s->hl[y*width_t+x]=(src[2*y*width+2*x]+src[2*y*width+2*x+1]-src[(2*y+1)*width+2*x]-src[(2*y+1)*width+2*x+1])*0.5;	
				s->hh[y*width_t+x]=(src[2*y*width+2*x]-src[2*y*width+2*x+1]-src[(2*y+1)*width+2*x]+src[(2*y+1)*width+2*x+1])*0.5;	
			}
		}
	return s;
}

bool is_key_frame(uint8_t *image,int width,int height,int frame_num)
{
	deviation1=deviation2=deviation3=0;
	int width_t=width>>1,height_t=height>>1;
	if(f1==NULL)
	{
		f1=(struct subands *)malloc(sizeof(struct subands));
		f2=(struct subands *)malloc(sizeof(struct subands));
		f1->lh=(int *)malloc(sizeof(int)*width_t*height_t);
		f1->hl=(int *)malloc(sizeof(int)*width_t*height_t);
		f1->hh=(int *)malloc(sizeof(int)*width_t*height_t);
		f2->lh=(int *)malloc(sizeof(int)*width_t*height_t);
		f2->hl=(int *)malloc(sizeof(int)*width_t*height_t);
		f2->hh=(int *)malloc(sizeof(int)*width_t*height_t);
		dwt2(image,width,height,1,f1);
		return true;
	}
	dwt2(image,width,height,1,f2);
	for(int y=0;y<height_t;y++)
	{
		for(int x=0;x<width_t;x++)
		{
			deviation1+=f2->hl[y*width_t+x]-f1->hl[y*width_t+x];
			deviation2+=f2->lh[y*width_t+x]-f1->lh[y*width_t+x];
			deviation3+=f2->hh[y*width_t+x]-f1->hh[y*width_t+x];
		}
	}
	float temp1=mean1,temp2=mean2,temp3=mean3;
	mean1+=(deviation1-mean1)/frame_num;
	mean2+=(deviation2-mean2)/frame_num;
	mean3+=(deviation3-mean3)/frame_num;
	var1+=(deviation1-temp1)*(deviation1-mean1);
	var2+=(deviation2-temp2)*(deviation2-mean2);
	var3+=(deviation3-temp3)*(deviation3-mean3);
	std1=sqrt(var1/frame_num);
	std2=sqrt(var2/frame_num);
	std3=sqrt(var3/frame_num);
	th1=mean1 + ALPHA*std1;
	th2=mean2 + ALPHA*std2;
	th3=mean3 + ALPHA*std3;
	f3=f1;
	f1=f2;
	f2=f3;
	if((deviation1>th1&&deviation2>th2) || (deviation2>th2&&deviation3>th3) || (deviation3>th3&&deviation1>th1))
	{
		return true;
	}
	return false;
}
