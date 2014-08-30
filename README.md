
Abstract:

Green computing is the environmentally responsible use of computers and related
resources. Such practices include the implementation of energy-efficient computing
solutions. Multi-core and General Purpose Graphics Processing Units (GPGPUs)
computing has become trend of high performance processors and energy efficient
computing. Video processing technique like moving object detection which is a
computationally intensive task can be made to exploit the multi-core architecture to
extract information more efficiently. Moving object detection finds wide range of
application especially in automated traffic surveillance and management. In defense,
these techniques are used in automating threat detection and elimination, target
acquisition and also in underwater object tracking. Existing systems are primitive in terms
of optimal utilization of multi-cores, hence cannot scale along with input video size.
Implementing moving object detection on GPU using CUDA or other platforms provides
greater speedup and scalability in terms of input size.

Moving object detection is carried out in three stages. First, key frames of video
shot are identified using wavelet based technique. Background subtraction is applied on
such key frames using a dynamic, self updating and fast learning algorithm. The key
frames are also subjected to edge detection algorithm to highlight the edges. This data is
then merged with the output of background subtraction module to segment foreground
objects. Post processing techniques are employed to reduce interference of background
noises. All these modules are collectively implemented on CUDA to make use of NVidia
GPUs for computation. Multiple threads are created to simultaneously manipulate each
pixel of a video frame in parallel to obtain speedup.

A video of 920X720 resolution and length 120 seconds was used as test video to
determine speedup due to GPU. The execution time was 111 second in CPU and 60
second in GPU. A HD video takes 23 minutes in serial implementation which is reduced
to 7 minutes using GPU acceleration. In sequential implementation, execution time
increases exponentially with respect to video resolution whereas there will be a linear
increase on a GPU. The precision achieved is 0.92 which is above par with respect to
IEEE standard benchmark of 0.8993. By using optimal 256 threads per block on each
device core, maximum GPU utilization was achieved and runtime reduced to 7 minutes.


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
