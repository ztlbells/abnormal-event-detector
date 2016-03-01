#include "Thread.h"
#include <QImage>  
#include <QPixmap> 
#include"cv.h"
#include"highgui.h"
#include<QtMultimedia>
#include <QVideoWidget>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <math.h>
#include <QString>
#include <sstream>
#define M_PI 3.14159
#define M_PI_2 1.57
using namespace cv;
using namespace std;



Thread::~Thread()
{
}

void Thread::run() {
	VideoCapture cap;
	cap.open("E:/28-prp/vids/pos_003.avi");
	Mat frame, gray, gray1, prevgray, flow, prevflow;
	Mat block[18][32];
	double opticalflow[18][32];
	double opticalflow_log[18][32];
	double sumflow[3][4];
	double ii = 0;
	double sum, sumlog;
	Mat picture(240, 240, CV_8UC3, Scalar(255, 255, 255)); //承载图像
	Mat picture2(240, 240, CV_8UC3, Scalar(255, 255, 255));
	Mat picture3(240, 240, CV_8UC3, Scalar(255, 255, 255));
	Point a, b;
	int posonpic2 = 0;
	int count_of_picture = -1;//用来记录当前记录的帧是第几帧
	int abnormal[] = { 502, 512, 530, 532, 534, 536, 538, 540, 542, 548, 550, 552, 554, 556, 558, 560, 562, 564, 566, 568, 570, 572, 580, 582, 584, 606, 618, 638, 704, 706 };
	int normal[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 17, 19, 21, 23, 76, 78, 82, 84, 86, 92, 94, 98, 108, 114, 116, 118, 120, 122, 246, 250, 280, 282, 292, 294, 356, 372, 374, 402, 406, 408 };
	int ab_cnt = 0;
	int nor_cnt = 0;//用来记录样例匹配到第几个
	double angle = 0;
	int statistic[256];
	memset(statistic, 0, sizeof(int) * 256);
	double getangle(double, double);
	int valid = 0;
	ofstream outfile;
	VideoWriter writer("VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(160, 90), false);
	for (;;)
	{
		double t = (double)cvGetTickCount();
		cap >> frame;
		count_of_picture++;
		cout << count_of_picture << endl;

		cvtColor(frame, gray, CV_BGR2GRAY);
		pyrDown(gray, gray1, Size(gray.cols / 2, gray.rows / 2));
		pyrDown(gray1, gray, Size(gray1.cols / 2, gray1.rows / 2));
		pyrDown(gray, gray1, Size(gray.cols / 2, gray.rows / 2));
		gray = gray1;
		if (prevgray.data)
		{
			calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
			for (int i = 0; i < 18; i++)
				for (int j = 0; j < 32; j++)
					opticalflow[i][j] = 0;
			sum = 0;
			if (prevflow.data)
			{
				for (int i = 0; i < 18; i++)
					for (int j = 0; j < 32; j++)
					{
						for (int c = 5 * j; c < 5 * j + 5; c++)
							for (int r = 5 * i; r < 5 * i + 5; r++)
							{
								static Vec2f ipt1;
								ipt1 = flow.at<Vec2f>(r, c);
								ii = ipt1[0] * ipt1[0] + ipt1[1] * ipt1[1];
								if (ii > 0.01) {
									opticalflow[i][j] = opticalflow[i][j] + ii*ii;
									sum += ii*ii;
								}
							}
						opticalflow_log[i][j] = log(opticalflow[i][j] + 1);
						if (opticalflow[i][j] > 100)
						{

							for (int m = 0; m < 40; m++)
								for (int n = 0; n < 40; n++)
								{
									frame.at<Vec3b>(40 * i + m, 40 * j + n)[2] = 255;

								}
							cout << opticalflow[i][j] << " ";

						}

					}
				cout << endl;

			}

			rectangle(picture3, Point(0, 0), Point(240, 240), Scalar(0, 0, 0), -1);
			static char outfilepath[60];
			valid = 0;
			for (int i = 0; i<flow.rows; i++)
			{
				for (int j = 0; j<flow.cols; j++)
				{
					Vec2f ipt = flow.at<Vec2f>(i, j);
					angle = getangle(ipt[0], ipt[1]);
					statistic[(int)(angle * 255 / (2 * M_PI))] += 1;
					circle(picture3, Point(120 + ipt[0] * 50, 120 + ipt[1] * 50), 2, Scalar(255, 255, 255), -1);
				}
			}
			statistic[0] = 0;
			memset(statistic, 0, sizeof(int) * 256);


		}
		std::swap(prevgray, gray);
		std::swap(prevflow, flow);
		if (gray.data)
		{
			writer << gray;
		}

		static char ss[40];
		sprintf(ss, "D://pictures/pic_of%d_lightflow.jpg", count_of_picture);
		imwrite(ss, picture3);
		sprintf(ss, "D://pictures/pic_of%d_original.jpg", count_of_picture);
		imwrite(ss, frame);

		/*string address("D://pictures/pic_of");
		string result = "";
		std::ostringstream oss;
		oss << address << count_of_picture << "_lightflow.jpg";
		result += oss.str();

		string add("D://pictures/pic_of");
		string re = "";
		std::ostringstream osss;
		osss << add << count_of_picture << "_original.jpg";
		re += osss.str();*/

		QString sss;
		sss.setNum(count_of_picture);
		emit done(sss);
		
	}

	cap.release();
	
}