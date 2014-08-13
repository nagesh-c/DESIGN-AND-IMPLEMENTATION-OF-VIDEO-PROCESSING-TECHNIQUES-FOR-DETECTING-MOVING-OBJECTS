This is a project on Background Subtraction without using OpenCV, but it requires ffmpeg for video decompression and outputs the uncompressed format images(*.ppm).

To run this:
		  
        $cd installation
		$chmod +x setup.sh
		$./setup.sh
This will install all the necessary packages. 

To finally execute the file:
		
        $cd code
         	$make makefile
		$./background.out name-of-file
		
And, would like to thank:
	
        Mr. Vignesh
        Mr. Sachin
        Mr. STP

for doing most of the development part.

This project uses "Discrete Wavelet Transform" for Key Frame Extraction and "Vibe" for Background Subtraction.  
