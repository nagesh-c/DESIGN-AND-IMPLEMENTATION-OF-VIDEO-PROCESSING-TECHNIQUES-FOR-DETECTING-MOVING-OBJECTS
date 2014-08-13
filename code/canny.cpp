#include"headers.h"

bool canny(uint8_t *image, int width, int height)
{
	if(image==NULL)
		return false;
	int i = 0;
	int frameFinished=0,numBytes;
	uint8_t *buffer = NULL;
	char filename[100],outfile[100],*data=new char[1],*integer=new char[4];
	string line;
	int rowTotal,colTotal,neighbourOffset;
	int x,y;
	int rowOffset, colOffset;

	uint8_t foreground=255,background=0;
	
	//Gradient	
	int Gy,Gx;
	int * gradient;
	
	//Gradient direction
	float dir;
	int finDir;
	int  * edgeDir;

	//Gaussian Filter
	int gaussianMask[] = { 2,4,5,4,2,4,9,12,9,4,5,12,15,12,2,4,9,12,9,4,2,4,5,4,2};
	
	//Sobel Mask
	int GxMask[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	int GyMask[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
	

	//Thresholds
	int T1 ;
	int T2 ;


		gradient = new int [height * width];
		edgeDir = new int [height * width];

		/* Applying the Gaussian Mask */
		gaussian(image,height,width,gaussianMask);			
		/* Applying the sobel mask to determine the gradient along the X and Y directions*/
		
		for ( x = 1; x < height-1; x++)
	       	{
			for ( y = 1; y < width-1; y++) 
			{
				Gx = 0;
				Gy = 0;
				/* Calculate the sum of the Sobel mask times the nine surrounding pixels in the x and y direction */
				for ( rowOffset=-1; rowOffset<=1; rowOffset++) 
				{
					for ( colOffset=-1; colOffset<=1; colOffset++) 
					{
						rowTotal = x + rowOffset;
						colTotal = y + colOffset;
						neighbourOffset = rowTotal*width + colTotal;
						Gx = Gx + image[neighbourOffset] * GxMask[rowOffset + 1][colOffset + 1];
						Gy = Gy + image[neighbourOffset] * GyMask[rowOffset + 1][colOffset + 1];
					}
				}

				gradient[x*width+y] = sqrt(pow(Gx,2.0) + pow(Gy,2.0));	// Calculate gradient strength			
				dir = (atan2((double)Gx,(double)Gy)/3.14159) * 180.0;		// Calculate actual direction of edge
			
				/* Convert actual edge direction to approximate value */
				if ( ( (dir < 22.5) && (dir > -22.5) ) || (dir > 157.5) || (dir < -157.5) )
					finDir = 0;
				if ( ( (dir > 22.5) && (dir < 67.5) ) || ( (dir < -112.5) && (dir > -157.5) ) )
					finDir = 45;
				if ( ( (dir > 67.5) && (dir < 112.5) ) || ( (dir < -67.5) && (dir > -112.5) ) )
					finDir = 90;
				if ( ( (dir > 112.5) && (dir < 157.5) ) || ( (dir < -22.5) && (dir > -67.5) ) )
					finDir = 135;
				
				edgeDir[x * width+ y] = finDir;		// Store the approximate edge direction of each pixel in one array
			}
		}
		
		
		/* Non-Maximum Suppression*/
		int n1,n2;
		for (x = 1; x< height - 1; x++)
		{
			for(y = 1;y < width - 1; y++)
			{
				switch(edgeDir[x * width + y])
				{
					case 0:  if ((y - 1) == 0)
							 n1 = 0;
						 if((y+1) == width - 1)
							 n2 = 0;
						 n1 = (x * width) + (y - 1);
						 n2 = (x * width) + (y + 1);
					       	 break;

					case 45: if ((y - 1) == 0 || (x - 1) == 0)
							 n1 = 0;
						 if((y+1) == width - 1 || (x + 1) == height - 1)
							 n2 = 0;
						 n1 = ((x -1) * width) + (y - 1);
						 n2 = ((x + 1) * width) + (y + 1);
					       	 break;

					case 90: if ((x - 1) == 0)
							 n1 = 0;
						 if((x + 1) == height - 1)
							 n2 = 0;
						 n1 = ((x -1) * width) + y ;
						 n2 = ((x + 1) * width) + y ;
					       	 break;

					case 135: if ((y + 1) == width - 1 || (x - 1) == 0)
							 n1 = 0;
						   if((y - 1) == 0 || (x + 1) == height - 1)
							 n2 = 0;
						   n1 = ((x-1) * width) + (y + 1);
						   n2 = ((x + 1) * width) + (y - 1);
					       	   break;
									
				}
				
				if((n1 && n2 && gradient[ x* width + y] > gradient[n1] && gradient[ x* width + y] > gradient[n2]) || (n1 && gradient[x * width +y] > gradient[n1]) ||(n2 && gradient[x * width + y]>gradient[n2] ))
				{
					image[x * width + y] = foreground;
				}
				else 
				{
					image[x * width + y] = background;				}
			}
		}

		/* Hysteresis Thresholding*/
		T1 = ostu(image,height,width);
		T2 = T1/2;

		for(x = 1; x < height-1 ; x++)
		{
			for(y = 1; y < width; y++)
			{	int flag = 0;
				if(gradient[x * width + y] >= T1)
				{	//Strong edge pixel
					image[x * width + y] = foreground;
				}
				else if (gradient[x * width + y] <= T2)
				{
					//not edge pixel
					image[x * width + y]  = background;

				}
				else
				{
					//weak edge pixel
					for ( rowOffset=-1; rowOffset<=1; rowOffset++) 
					{	
						for ( colOffset=-1; colOffset<=1; colOffset++) 
						{
							image[x * width + y] = background;
							rowTotal = x + rowOffset;
							colTotal = y + colOffset;
							neighbourOffset = rowTotal*width + colTotal;

							if (!rowTotal || !colTotal || rowTotal == height - 1 || colTotal == width - 1)
							{
								image[neighbourOffset] = background;
							}
							else
							{
								if(gradient[neighbourOffset] >= T1)
								{	
									flag = 1;
									image[x * width + y] = foreground;
									break;
								}		
							}
						}
						if(flag)
						{
							break;	
						}	
					}
				}
			}
		}

		for(x=0;x<height;x++)
		{
			for(y=0;y<width;y++)
			{
				if(!(image[x * width + y] == foreground || image[x * width + y] == background))
				{
					image[x * width +y] = background;

				}
			}
		}
		delete []edgeDir;
		delete []gradient;
		return true;
}