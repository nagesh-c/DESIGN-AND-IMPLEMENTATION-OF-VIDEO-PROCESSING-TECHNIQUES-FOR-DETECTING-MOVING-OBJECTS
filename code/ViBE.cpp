#include"headers.h"

uint8_t *samples=NULL;

void init_background_model(uint8_t *image,int width,int height)
{
	samples=new uint8_t[height*width*N];

	for(int x=0;x<height;x++)
	{
		for(int y=0;y<width;y++)
		{
			for(int index=0;index<N;index++)
			{
				int neighbour=rand()%8;
				if(x==0)
				{
					if(y==0)
					{
						if(neighbour<4)
						{
							neighbour=rand()%4 + 4;
						}
						if(neighbour==5)
						{
							neighbour=rand()%2 + 6;
						}
					}
					else if(y==width-1)
					{
						if(neighbour<3)
						{
							neighbour=3;
						}
						else if(neighbour>6)
						{	
							neighbour=6;
						}
						else
						{
							neighbour=5;
						}
					}
					else if(neighbour<3)
					{
						neighbour=rand()%5 + 3;
					}
				}
				else if(x==height-1)
				{
					if(y==0)
					{
						neighbour=rand()%3 + 1;
						if(neighbour==3)
						{
							neighbour=4;
						}
					}
					else if(y==width-1)
					{
						neighbour=rand()%4;
						if(neighbour==2)
						{
							neighbour=3;
						}
					}
					else if(neighbour>4)
					{
						neighbour-=4;
					}
				}
				else if(y==0)
				{
					if(neighbour==0)
					{
						neighbour=rand()%2 + 1;
					}
					else if(neighbour==3)
					{
						neighbour=4;
					}
					else if(neighbour==5)
					{
						neighbour=rand()%2 + 6;
					}
				}
				else if(y==width-1)
				{
					if(neighbour==2)
					{
						neighbour=rand()%2;
					}
					else if(neighbour==4)
					{
						neighbour=3;
					}
					else if(neighbour==7)
					{
						neighbour=rand()%2 + 5;
					}
				}
				switch(neighbour)
				{
					case 0:samples[index*width*height+x*width+y]=image[(x-1)*width+(y-1)];
					       break;
					case 1:samples[index*width*height+x*width+y]=image[(x-1)*width+y];
					       break;
					case 2:samples[index*width*height+x*width+y]=image[(x-1)*width+(y+1)];
					       break;
					case 3:samples[index*width*height+x*width+y]=image[x*width+(y-1)];
					       	break;
					case 4:samples[index*width*height+x*width+y]=image[x*width+(y+1)];
					       break;
					case 5:samples[index*width*height+x*width+y]=image[(x+1)*width+(y-1)];
					       break;
					case 6:samples[index*width*height+x*width+y]=image[(x+1)*width+y];
					       break;
					case 7:samples[index*width*height+x*width+y]=image[(x+1)*width+(y+1)];
					       break;
				}
			}
		}
	}
	printf("model init..... Success\n");
}

void background_subtract(uint8_t *image,uint8_t *segMap,int width,int height)
{
	assert(samples!=NULL);
	for(int x=0;x<height;x++)
	{
		for(int y=0;y<width;y++)
		{
			int count=0,index=0,dist=0;
			while((count<MIN_CARD)&&(index<N))
			{
				dist=abs((image[x*width+y])-(samples[index*width*height+x*width+y]));
				if(dist<R)
				{
					count++;
				}
				index++;
			}

			if(count<MIN_CARD)
			{
				segMap[x*width+y]=foreground;
				continue;
			}

			segMap[x*width+y]=background;
			int r=rand()%RANDOM_SAMPLE;
			if(r==0)
			{
				r=rand()%N;
				samples[r*width*height+x*width+y]=image[x*width+y];
			}
	
			int neighbour=rand()%8;
			if(x==0)
			{
				if(y==0)
				{
					if(neighbour<4)
					{
						neighbour=rand()%4 + 4;
					}
					if(neighbour==5)
					{
						neighbour=rand()%2 + 6;
					}
				}
				else if(y==width-1)
				{
					if(neighbour<3)
					{
						neighbour=3;
					}
					else if(neighbour>6)
					{
						neighbour=6;
					}
					else
					{
						neighbour=5;
					}
				}
				else if(neighbour<3)
				{
					neighbour=rand()%5 + 3;
				}
			}
			else if(x==height-1)
			{
				if(y==0)
				{
					neighbour=rand()%3 + 1;
					if(neighbour==3)
					{
						neighbour=4;
					}
				}
				else if(y==width-1)
				{
					neighbour=rand()%4;
					if(neighbour==2)
					{
						neighbour=3;
					}
				}
				else if(neighbour>4)
				{
					neighbour-=4;
				}
			}
			else if(y==0)
			{
				if(neighbour==0)
				{
					neighbour=rand()%2 + 1;
				}
				else if(neighbour==3)
				{
					neighbour=4;
				}
				else if(neighbour==5)
				{
					neighbour=rand()%2;
				}
			}
			else if(y==width-1)
			{
				if(neighbour==2)
				{
					neighbour=rand()%2;
				}
				else if(neighbour==4)
				{
					neighbour=3;
				}
				else if(neighbour==7)
				{
					neighbour=rand()%2 + 5;
				}
			}
			switch(neighbour)
			{
				r=rand()%N;
				case 0:samples[r*width*height+(x-1)*width+(y-1)]=image[x*width+y];
				       break;
				case 1:samples[r*width*height+(x-1)*width+y]=image[x*width+y];
				       break;
				case 2:samples[r*width*height+(x-1)*width+(y+1)]=image[x*width+y];
				       break;
				case 3:samples[r*width*height+x*width+(y-1)]=image[x*width+y];
				       break;
				case 4:samples[r*width*height+x*width+(y+1)]=image[x*width+y];
				       break;
				case 5:samples[r*width*height+(x+1)*width+(y-1)]=image[x*width+y];
				       break;
				case 6:samples[r*width*height+(x+1)*width+y]=image[x*width+y];
				       break;
				case 7:samples[r*width*height+(x+1)*width+(y+1)]=image[x*width+y];
				       break;
			}
		}
	}
}
