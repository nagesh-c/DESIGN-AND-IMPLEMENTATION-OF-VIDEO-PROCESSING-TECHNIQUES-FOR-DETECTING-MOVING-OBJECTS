//compile as g++ -o display display.cpp `pkg-config opencv --libs --cflags`
#include<stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

main(int argc, char **argv)
{
	int i;
	char str1[100],str2[100];
	namedWindow("Video Feed",CV_WINDOW_KEEPRATIO);
   	while(i<=atoi(argv[1]))
	{
		sprintf(str1,"framekey%d.ppm",i);
		sprintf(str2,"bkframekey%d.ppm",i);
		
    		Mat im1 = imread(str1);
		if(im1.data)
		{
			Mat im2 = imread(str2);
			Size sz1 = im1.size();
    			Size sz2 = im2.size();
    			Mat im3(sz1.height, sz1.width+sz2.width, CV_8UC3);
    			Mat left(im3, Rect(0, 0, sz1.width, sz1.height));
    			im1.copyTo(left);
    			Mat right(im3, Rect(sz1.width,0, sz2.width, sz2.height));
    			im2.copyTo(right);
    			imshow("Video Feed", im3);
		}
		if(waitKey(0)%256==81)
		{
			i--;
		}
		else
			i++;
	}
	return 0;
}
