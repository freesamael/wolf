/**
 * \file manset.cpp
 * \date Jul 16, 2010
 * \author samael
 */

//#include <iostream>
//#include <opencv/cv.h>
//#include <opencv/cvaux.h>
//#include <opencv/highgui.h>
//
//using namespace std;
//
//uchar manset(int x, int y, double width, double height, int ch)
//{
//	double minreal = -2.0;
//	double maxreal = 1.0;
//	double minimag = -1.2;
//	double maximag = 1.2;
//	double creal = minreal + x * (maxreal - minreal) / (width - 1);
//	double cimag = maximag - y * (maximag - minimag) / (height - 1);
//	double zreal = creal, zimag = cimag;
//	unsigned maxiter = 1000, iter;
//	for (iter = 0; iter < maxiter; iter++) {
//		if (zreal * zreal + zimag * zimag > 4)
//			break;
//		double tmpzreal = zreal * zreal - zimag * zimag;
//		zimag = 2 * zreal * zimag + cimag;
//		zreal = tmpzreal + creal;
//	}
//	if (iter == maxiter) {
//		return 0;
//	} else if (ch == 0) {
//		if (iter <= 5)
//			return 50 + iter * 5;
//		if (iter <= 15)
//			return (200 - 75) * (iter - 5) / 10 + 75;
//		if (iter <= 20)
//			return (255 - 200) * (iter - 15) / 5 + 200;
//		return 255;
//	} else if (ch == 1) {
//		if (iter <= 13)
//			return 0;
//		if (iter <= 18)
//			return (iter - 13) * 5;
//		if (iter <= 23)
//			return (255 - 75) * (iter - 18) / 5 + 75;
//		return 255;
//	} else {
//		if (iter <= 18)
//			return 0;
//		if (iter <= 20)
//			return (iter - 18) * 40;
//		if (iter <= 23)
//			return (255 - 80) * (iter - 20) / 3;
//		return 255;
//	}
//}

int main()
{
//	IplImage *img = cvCreateImage(cvSize(2400, 1920), IPL_DEPTH_8U, 3);
//
//	for (int i = 0; i < img->height; i++) {
//		for (int j = 0; j < img->width; j++) {
//			((uchar*)img->imageData)[i * img->widthStep + j * 3] = manset(j, i, img->width, img->height, 0);
//			((uchar*)img->imageData)[i * img->widthStep + j * 3 + 1] = manset(j, i, img->width, img->height, 1);
//			((uchar*)img->imageData)[i * img->widthStep + j * 3 + 2] = manset(j, i, img->width, img->height, 2);
//		}
//	}
//
//	cvSaveImage("img.jpg", img);
//	cvReleaseImage(&img);
	return 0;
}
