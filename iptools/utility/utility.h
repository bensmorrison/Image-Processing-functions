#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <opencv2/opencv.hpp>
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int value);
		static void binarize(image &src, image &tgt, int threshold);
		static void scale(image &src, image &tgt, float ratio);
		static void cv_gray(cv::Mat &src, cv::Mat &tgt);
		static void cv_avgblur(cv::Mat &src, cv::Mat &tgt, int WindowSize);
        static void histStretch(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy, int a, int b);
        static void histEqual(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
        static void sobel(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
        static void canny(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy, int a, int b);
        static void combineCanny(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy, int a, int b);
        static void combineSobel(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
        static void qr(cv::Mat &src, cv::Mat &tgt);
};

#endif

