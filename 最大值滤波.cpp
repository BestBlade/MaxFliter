#include <iostream>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

Mat maxfliter(Mat img,Size temp) {				
	if (temp.height % 2 == 0 || temp.width % 2 == 0) {
		cerr << "error template size" << endl;
	}
	int row_center = temp.height / 2;
	int col_center = temp.width / 2;

	Mat res(img.rows, img.cols, img.type());

	for (int x = row_center; x < img.rows - row_center; x++) {
		for (int y = col_center; y < img.cols - col_center; y++) {
			if (res.channels() == 1) {
				uchar max_val = 0;
				for (int i = 0; i < temp.height; i++) {
					for (int j = 0; j < temp.width; j++) {
						if (i == row_center && j == col_center) {
							continue;
						}
						max_val = max(max_val, img.at<uchar>(x + i - row_center, y + j - col_center));
					}
				}
				res.at<uchar>(x, y) = max_val;
			}
			else {
				//空间换时间
				uchar max_val_r = 0;
				uchar max_val_g = 0;
				uchar max_val_b = 0;
				for (int i = 0; i < temp.height; i++) {
					for (int j = 0; j < temp.width; j++) {
						if (i == row_center && j == col_center) {
							continue;
						}
						max_val_r = max(max_val_r, img.at<Vec3b>(x + i - row_center, y + j - col_center)[2]);
						max_val_g = max(max_val_g, img.at<Vec3b>(x + i - row_center, y + j - col_center)[1]);
						max_val_b = max(max_val_b, img.at<Vec3b>(x + i - row_center, y + j - col_center)[0]);
					}
				}

				res.at<Vec3b>(x, y)[0] = max_val_b;
				res.at<Vec3b>(x, y)[1] = max_val_g;
				res.at<Vec3b>(x, y)[2] = max_val_r;
			}
		}
	}
	return res;

}
int main()
{
	Mat img = imread("C://Users//Chrysanthemum//Desktop//1.png");

	Size temp(3, 3);

	Mat res = maxfliter(img, temp);

	imshow("原图", img);
	imshow("3x3滤波结果图", res);

	waitKey(0);

	return 0;
}