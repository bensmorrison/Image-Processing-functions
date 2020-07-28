This software is architectured as follows.

iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image. (without OpenCV)
	utility - This folder hosts the implemented algorithms.
	roi - This folder hosts the roi structure
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory.

*** INSTALATION ***

On Linux

Enter the project directory in terminal and run make
The executable file will be created in bin/

*** Run the program:
cd bin/
./iptool parameters.txt

*** FUNCTIONS (without OpenCV) ***

1. Add intensity: add
Increase the intensity for a gray-level image.
parameter: intensity

2. Binarization: binarize
Binarize the pixels with the threshold.
parameter: threshold

3. Scaling: Scale
Reduce or expand the heigh and width with two scale factors.
Scaling factor = 2: double height and width of the input image.
Scaling factor = 0.5: half height and width of the input image.
parameter: scaling_factor

*** FUNCTIONS (with OpenCV) ***

1. Gray Scale: gray
Change whole image to gray-level.
parameter: no

2. Average Blur: blur_avg
Uniform smoothing.
parameter: window_size

3. Histogram Stretch: histStretch
Perform histogram stretching
Parameters: ROI, a & b thresholds

4. Histogram Equalization: histEqual
Perform histogram equalization
Parameters: ROI

5. Sobel edge detection
Perform Sobel edge detection based on a kernel (kernel size hardcoded)
Parameters: ROI

6. Canny edge detection
Perform Canny edge detection
Parameters ROI, a & b thresholds

7. Combined Canny operations
Preform image equalization and then Canny edge detection. Subtract edge detection to reveal equalized image
Parameters ROI, a & b thresholds

8. Combined Sobel operations
Preform image equalization and then Sobel edge detection. Subtract edge detection to reveal equalized image
Parameters: ROI

9. QR code reader
Reads the QR code and outputs the link/text
Parameters: no
Note: define the input and output images (although no output image will save as the output is in the console)

*** PARAMETERS FILE ***
(Please check parameters.txt)
There are four parameters:
1. the input file name
2. the output file name
3. opencv / FUNCTIONS (without OpenCV): skip to 5 for parameters
4. the name of the function with OpenCV. Check FUNCTIONS (with OpenCV).
5. The number of ROIs you would like in the image
6. The ROI dimensions (4 numbers) x, y, sx, and sy values
7. parameters (Check FUNCTIONS (with OpenCV) for parameters)

Note: if you have more than one ROI, you must define the next dimensions after the first. 
For example:
003.pgm combineSobel.pgm opencv combineSobel 2 0 0 200 200 300 300 400 400

Also, please ensure ROI dimensions are within the image size





