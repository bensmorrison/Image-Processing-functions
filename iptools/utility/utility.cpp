#include "utility.h"
#include <chrono>


#define MAXRGB 255
#define MINRGB 0

using namespace std::chrono;

using namespace cv;

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
		}
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j,MINRGB);
			else
				tgt.setPixel(i,j,MAXRGB);
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::cv_gray(Mat &src, Mat &tgt)
{
	cvtColor(src, tgt, COLOR_BGR2GRAY);
}

/*-----------------------------------------------------------------------**/
void utility::cv_avgblur(Mat &src, Mat &tgt, int WindowSize)
{
	blur(src,tgt,Size(WindowSize,WindowSize));
}

void utility::histStretch(Mat &src, Mat &tgt, int x, int y, int sx, int sy, int a, int b)
{
    auto start = high_resolution_clock::now();
    
    Mat tempImg, temp;
    cv_gray(src, src);
    Size size(src.cols,src.rows);
    resize(src, tgt, size);

    // stretching
    for(int i = 0; i < src.rows; i++){
        for (int j = 0; j < src.cols; j++)
        {
            int current = src.at<uchar>(i,j);
            
            //ROI
            if(i >= y && j >= x && i <= (y + sy) && j <= (x + sx))
            {
                if(current < a){
                    tgt.at<int>(i,j) = MINRGB;
                }
                else if(current > b){
                    tgt.at<int>(i,j) = MAXRGB;
                }
                else{
                    tgt.at<uchar>(i,j) = checkValue((current-a)*(255/(b-a)));
                }
            }
            else{
                tgt.at<uchar>(i,j) = checkValue(src.at<uchar>(i,j));
            }
        }
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Histogram Stretching: " << duration.count() << " ms" << endl;
}

void utility::histEqual(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
    auto start = high_resolution_clock::now();
    
    Mat temp;
    cv_gray(src, src);
    Size size(src.cols,src.rows);
    resize(src, tgt, size);

    //equalization
    equalizeHist(src, temp);

    // ROI
    for(int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            if(i >= y && j >= x && i <= (y + sy) && j <= (x + sx))
                tgt.at<uchar>(i,j) = checkValue(temp.at<uchar>(i,j));
            else
                tgt.at<uchar>(i,j) = checkValue(src.at<uchar>(i,j));
        }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Histogram Equalization: " << duration.count() << " ms" << endl;
}

void utility::sobel(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
    auto start = high_resolution_clock::now();
    
    Mat temp;
    cv_gray(src, src);
    Size size(src.cols,src.rows);
    resize(src, tgt, size);
    
    // Sobel Edge Detection
    Mat grad_x, grad_y, abs_grad_x, abs_grad_y;

    Sobel(src, grad_x, CV_16S, 1, 0, 3);
    Sobel(src, grad_y, CV_16S, 0, 1, 3);

    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, temp);
    
    // ROI
    for(int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            if(i >= y && j >= x && i <= (y + sy) && j <= (x + sx))
                tgt.at<uchar>(i,j) = checkValue(temp.at<uchar>(i,j));
            else
                tgt.at<uchar>(i,j) = checkValue(src.at<uchar>(i,j));
        }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Sobel: " << duration.count() << " ms" << endl;
    
}

void utility::canny(Mat &src, Mat &tgt, int x, int y, int sx, int sy, int a, int b)
{
    auto start = high_resolution_clock::now();
    
    Mat temp;
    cv_gray(src, src);
    Size size(src.cols,src.rows);
    resize(src, tgt, size);
    
    //Canny Edge Detection
    Canny(src, temp, a, b);
    
    // ROI
    for(int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            if(i >= y && j >= x && i <= (y + sy) && j <= (x + sx))
                tgt.at<uchar>(i,j) = checkValue(temp.at<uchar>(i,j));
            else
                tgt.at<uchar>(i,j) = checkValue(src.at<uchar>(i,j));
        }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Canny: " << duration.count() << " ms" << endl;
}
 
void utility::combineCanny(Mat &src, Mat &tgt, int x, int y, int sx, int sy, int a, int b)
{
    auto start = high_resolution_clock::now();
    
    Mat tempImg, equalizedImg, equalizedCanny, equalMinusCanny, temp;
    //cv_gray(src, src);
    cv_gray(src, tempImg);
    cv_gray(src, temp);
    tgt = tempImg.clone();

    //equalization
    equalizeHist(tempImg, equalizedImg);
    temp = equalizedImg.clone();
    
    //canny
    canny(src, equalizedImg, x, y, sx, sy, a, b);
    equalizedCanny = equalizedImg.clone();
    
    // image subtraction for canny
    equalMinusCanny = temp - equalizedCanny;
    
    // ROI
    for(int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            if(i >= y && j >= x && i <= (y + sy) && j <= (x + sx))
                tgt.at<uchar>(i,j) = checkValue(equalMinusCanny.at<uchar>(i,j));
            else
                tgt.at<uchar>(i,j) = checkValue(src.at<uchar>(i,j));
        }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Combine Canny: " << duration.count() << " ms" << endl;
}

void utility::combineSobel(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
    auto start = high_resolution_clock::now();
    
    Mat tempImg, equalizedImg, equalizedSobel, equalMinusSobel, temp;
    cv_gray(src, tempImg);
    cv_gray(src, temp);
    tgt = tempImg.clone();

    //equalization
    equalizeHist(tempImg, equalizedImg);
    temp = equalizedImg.clone();
    
    //sobel
    sobel(src, equalizedImg, x, y, sx, sy);
    equalizedSobel = equalizedImg.clone();
    
    // image subtraction for canny
    equalMinusSobel = temp - equalizedSobel;
    
    // ROI
    for(int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            if(i >= y && j >= x && i <= (y + sy) && j <= (x + sx))
                tgt.at<uchar>(i,j) = checkValue(equalMinusSobel.at<uchar>(i,j));
            else
                tgt.at<uchar>(i,j) = checkValue(src.at<uchar>(i,j));
        }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Combine Sobel: " << duration.count() << " ms" << endl;
}

void utility::qr(Mat &src, Mat &tgt)
{
    auto start = high_resolution_clock::now();
    
    cvtColor(src, src, COLOR_BGR2GRAY);
    //equalizeHist(src, src);
    cout << QRCodeDetector().detectAndDecode(src) << endl;
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "QR: " << duration.count() << " ms" << endl;
}
