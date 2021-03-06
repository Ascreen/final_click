// ascreen_calculating.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include<stdio.h>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include  <vector>
#include <windows.h>
#include <math.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"

#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv/cxcore.h"

#include "opencv2/core/core.hpp"

#include <stdlib.h>
#include "opencv2/imgproc/imgproc_c.h"

#include "opencv2/opencv.hpp"

#include <fstream>

#define Pi 3.14159265
#define Length 1920
#define Height 1080

#define monitor_l 1440
#define monitor_h 900


using namespace cv;
using namespace std;

Point dr_c(0, 0);
Point dr_l(0, 0);
Point dr_h(0, 0);
Point dr_touched(0, 0);
float dr_l_dgree;
float dr_h_dgree;

Point ur_c(0, 0);
Point ur_l(0, 0);
Point ur_h(0, 0);
Point ur_touched(0, 0);
float ur_l_dgree;
float ur_h_dgree;

Point ul_c(0, 0);
Point ul_l(0, 0);
Point ul_h(0, 0);
Point ul_touched(0, 0);
float ul_l_dgree;
float ul_h_dgree;

Point dl_c(0, 0);
Point dl_l(0, 0);
Point dl_h(0, 0);
Point dl_touched(0, 0);
float dl_l_dgree;
float dl_h_dgree;

void setting_parsing() {
	string settingFilePath = "setting.txt";

	ifstream openFile(settingFilePath.data());
	if (openFile.is_open()) {
		string line;
		int num = 0;
		while (getline(openFile, line)) {

			std::vector<char> writable(line.begin(), line.end());
			writable.push_back('\0');
			char* ptr = &writable[0];
			//std::cout << ptr;

			char* token = strtok(ptr, "/");

			int count = 0;
			while (token) {
				if (count == 0) {
					dr_c.x = atoi(token);
					count++;
				}
				else if (count == 1) {
					dr_c.y = atoi(token);
					count++;
				}
				else if (count == 2) {
					dr_l.x = atoi(token);
					count++;
				}
				else if (count == 3) {
					dr_l.y = atoi(token);
					count++;
				}
				else if (count == 4) {
					dr_h.x = atoi(token);
					count++;
				}
				else if (count == 5) {
					dr_h.y = atoi(token);
					count++;
				}
				else if (count == 6) {
					ur_c.x = atoi(token);
					count++;
				}
				else if (count == 7) {
					ur_c.y = atoi(token);
					count++;
				}
				else if (count == 8) {
					ur_l.x = atoi(token);
					count++;
				}
				else if (count == 9) {
					ur_l.y = atoi(token);
					count++;
				}
				else if (count == 10) {
					ur_h.x = atoi(token);
					count++;
				}
				else if (count == 11) {
					ur_h.y = atoi(token);
					count++;
				}
				else if (count == 12) {
					ul_c.x = atoi(token);
					count++;
				}
				else if (count == 13) {
					ul_c.y = atoi(token);
					count++;
				}
				else if (count == 14) {
					ul_l.x = atoi(token);
					count++;
				}
				else if (count == 15) {
					ul_l.y = atoi(token);
					count++;
				}
				else if (count == 16) {
					ul_h.x = atoi(token);
					count++;
				}
				else if (count == 17) {
					ul_h.y = atoi(token);
					count++;
				}
				else if (count == 18) {
					dl_c.x = atoi(token);
					count++;
				}
				else if (count == 19) {
					dl_c.y = atoi(token);
					count++;
				}
				else if (count == 20) {
					dl_l.x = atoi(token);
					count++;
				}
				else if (count == 21) {
					dl_l.y = atoi(token);
					count++;
				}
				else if (count == 22) {
					dl_h.x = atoi(token);
					count++;
				}
				else if (count == 23) {
					dl_h.y = atoi(token);
					count++;
				}
				token = strtok(NULL, "/");
			}
			/*
			cout << dr_c<< endl;
			cout << dr_l << endl;
			cout << dr_h << endl;
			cout << ur_c<< endl;
			cout << ur_l << endl;
			cout << ur_h << endl;
			cout << ul_c<< endl;
			cout << ul_l << endl;
			cout << ul_h << endl;
			cout << dl_c<< endl;
			cout << dl_l << endl;
			cout << dl_h << endl;
			*/

		}
		openFile.close();
	}
}

float getAngle(Point p1, Point p2) {
	float result;
	result = atan2(p2.y - p1.y, p2.x - p1.x);
	while (result<0) {
		result = 2 * Pi + result;
	}
	return result;
}

void calculate_dr(Point dr_touched) {
	Point tmp_dr_c(0, 0);
	Point tmp_dr_l(0, 0);
	Point tmp_dr_h(0, 0);
	Point tmp_dr_touched(0, 0);

	float dgree;

	//1st change for y
	tmp_dr_c.x = dr_c.x;
	tmp_dr_c.y = Height - dr_c.y;
	tmp_dr_l.x = dr_l.x;
	tmp_dr_l.y = Height - dr_l.y;
	tmp_dr_h.x = dr_h.x;
	tmp_dr_h.y = Height - dr_h.y;
	tmp_dr_touched.x = dr_touched.x;
	tmp_dr_touched.y = Height - dr_touched.y;
	/*
	cout << tmp_dr_c << endl;
	cout << tmp_dr_l<< endl;
	cout << tmp_dr_h<< endl;
	cout << tmp_dr_touched<< endl;
	*/
	//2nd change for x,y (move parell)

	tmp_dr_l.x = tmp_dr_l.x - tmp_dr_c.x;
	tmp_dr_l.y = tmp_dr_l.y - tmp_dr_c.y;
	tmp_dr_h.x = tmp_dr_h.x - tmp_dr_c.x;
	tmp_dr_h.y = tmp_dr_h.y - tmp_dr_c.x;
	tmp_dr_touched.x = tmp_dr_touched.x - tmp_dr_c.x;
	tmp_dr_touched.y = tmp_dr_touched.y - tmp_dr_c.y;
	tmp_dr_c.x = tmp_dr_c.x - tmp_dr_c.x;
	tmp_dr_c.y = tmp_dr_c.y - tmp_dr_c.y;

	/*
	cout << tmp_dr_c << endl;
	cout << tmp_dr_l<< endl;
	cout << tmp_dr_h<< endl;
	cout << tmp_dr_touched<< endl;
	*/


	dgree = getAngle(Point(1, 0), tmp_dr_h) - getAngle(Point(1, 0), tmp_dr_l);
	dr_h_dgree = (getAngle(tmp_dr_touched, Point(1, 0)) - getAngle(tmp_dr_h, Point(1, 0))) * 90 / dgree;
	dr_l_dgree = (getAngle(tmp_dr_l, Point(1, 0)) - getAngle(tmp_dr_touched, Point(1, 0))) * 90 / dgree;


	cout << "---dgree-dr---" << endl;
	cout << dr_l_dgree << endl;
	cout << dr_h_dgree << endl;
	/*
	cout << tmp_dr_c << endl;
	cout << tmp_dr_l<< endl;
	cout << tmp_dr_h<< endl;
	cout << tmp_dr_touched<< endl;
	*/

}

void calculate_ur(Point ur_touched) {
	Point tmp_ur_c(0, 0);
	Point tmp_ur_l(0, 0);
	Point tmp_ur_h(0, 0);
	Point tmp_ur_touched(0, 0);
	float dgree;


	//1st change for y
	tmp_ur_c.x = ur_c.x;
	tmp_ur_c.y = 1080 - ur_c.y;
	tmp_ur_l.x = ur_l.x;
	tmp_ur_l.y = 1080 - ur_l.y;
	tmp_ur_h.x = ur_h.x;
	tmp_ur_h.y = 1080 - ur_h.y;
	tmp_ur_touched.x = ur_touched.x;
	tmp_ur_touched.y = 1080 - ur_touched.y;



	//2nd change for x,y (move parell)
	tmp_ur_l.x = tmp_ur_l.x - tmp_ur_c.x;
	tmp_ur_l.y = tmp_ur_l.y - tmp_ur_c.y;
	tmp_ur_h.x = tmp_ur_h.x - tmp_ur_c.x;
	tmp_ur_h.y = tmp_ur_h.y - tmp_ur_c.x;
	tmp_ur_touched.x = tmp_ur_touched.x - tmp_ur_c.x;
	tmp_ur_touched.y = tmp_ur_touched.y - tmp_ur_c.y;
	tmp_ur_c.x = tmp_ur_c.x - tmp_ur_c.x;
	tmp_ur_c.y = tmp_ur_c.y - tmp_ur_c.y;

	dgree = getAngle(tmp_ur_h, Point(1, 0)) - getAngle(tmp_ur_l, Point(1, 0));
	ur_l_dgree = (getAngle(tmp_ur_l, Point(1, 0)) - getAngle(tmp_ur_touched, Point(1, 0))) * 90 / dgree;
	ur_h_dgree = (getAngle(Point(1, 0), tmp_ur_touched) - getAngle(Point(1, 0), tmp_ur_h)) * 90 / dgree;


	//cout << tmp_ur_c << endl;
	//cout << tmp_ur_l<< endl;
	//cout << tmp_ur_h<< endl;
	//cout << tmp_ur_touched<< endl;

	cout << "---dgree-ur---" << endl;
	cout << ur_l_dgree << endl;
	cout << ur_h_dgree << endl;


}

void calculate_ul(Point ul_touched) {
	Point tmp_ul_c(0, 0);
	Point tmp_ul_l(0, 0);
	Point tmp_ul_h(0, 0);
	Point tmp_ul_touched(0, 0);
	float dgree;


	//1st change for y
	tmp_ul_c.x = ul_c.x;
	tmp_ul_c.y = 1080 - ul_c.y;
	tmp_ul_l.x = ul_l.x;
	tmp_ul_l.y = 1080 - ul_l.y;
	tmp_ul_h.x = ul_h.x;
	tmp_ul_h.y = 1080 - ul_h.y;
	tmp_ul_touched.x = ul_touched.x;
	tmp_ul_touched.y = 1080 - ul_touched.y;

	//2nd change for x,y (move parell)
	tmp_ul_l.x = tmp_ul_l.x - tmp_ul_c.x;
	tmp_ul_l.y = tmp_ul_l.y - tmp_ul_c.y;
	tmp_ul_h.x = tmp_ul_h.x - tmp_ul_c.x;
	tmp_ul_h.y = tmp_ul_h.y - tmp_ul_c.x;
	tmp_ul_touched.x = tmp_ul_touched.x - tmp_ul_c.x;
	tmp_ul_touched.y = tmp_ul_touched.y - tmp_ul_c.y;
	tmp_ul_c.x = tmp_ul_c.x - tmp_ul_c.x;
	tmp_ul_c.y = tmp_ul_c.y - tmp_ul_c.y;

	dgree = getAngle(tmp_ul_h, Point(1, 0)) - getAngle(tmp_ul_l, Point(1, 0));
	ul_l_dgree = (getAngle(tmp_ul_touched, Point(1, 0)) - getAngle(tmp_ul_l, Point(1, 0))) * 90 / dgree;
	ul_h_dgree = (getAngle(tmp_ul_h, Point(1, 0)) - getAngle(tmp_ul_touched, Point(1, 0))) * 90 / dgree;

	cout << "---dgree-ul---" << endl;
	cout << ul_l_dgree << endl;
	cout << ul_h_dgree << endl;

}

void calculate_dl(Point dl_touched) {
	Point tmp_dl_c(0, 0);
	Point tmp_dl_l(0, 0);
	Point tmp_dl_h(0, 0);
	Point tmp_dl_touched(0, 0);
	float dgree;


	//1st change for y
	tmp_dl_c.x = dl_c.x;
	tmp_dl_c.y = 1080 - dl_c.y;
	tmp_dl_l.x = dl_l.x;
	tmp_dl_l.y = 1080 - dl_l.y;
	tmp_dl_h.x = dl_h.x;
	tmp_dl_h.y = 1080 - dl_h.y;
	tmp_dl_touched.x = dl_touched.x;
	tmp_dl_touched.y = 1080 - dl_touched.y;

	//2nd change for x,y (move parell)
	tmp_dl_l.x = tmp_dl_l.x - tmp_dl_c.x;
	tmp_dl_l.y = tmp_dl_l.y - tmp_dl_c.y;
	tmp_dl_h.x = tmp_dl_h.x - tmp_dl_c.x;
	tmp_dl_h.y = tmp_dl_h.y - tmp_dl_c.x;
	tmp_dl_touched.x = tmp_dl_touched.x - tmp_dl_c.x;
	tmp_dl_touched.y = tmp_dl_touched.y - tmp_dl_c.y;
	tmp_dl_c.x = tmp_dl_c.x - tmp_dl_c.x;
	tmp_dl_c.y = tmp_dl_c.y - tmp_dl_c.y;

	dgree = getAngle(Point(1, 0), tmp_dl_l) - getAngle(Point(1, 0), tmp_dl_h);
	dl_l_dgree = (getAngle(tmp_dl_l, Point(1, 0)) - getAngle(tmp_dl_touched, Point(1, 0))) * 90 / dgree;
	dl_h_dgree = (getAngle(Point(1, 0), tmp_dl_touched) - getAngle(Point(1, 0), tmp_dl_h)) * 90 / dgree;


	cout << "---dgree-dl---" << endl;
	cout << dl_l_dgree << endl;
	cout << dl_h_dgree << endl;


}

int calculate_y() {
	int result;
	int result1;
	int result2;
	double alpha;
	double beta;

	if (ur_h_dgree != 0 && ul_h_dgree != 0) {
		alpha = ur_h_dgree * Pi / 180;
		beta = ul_h_dgree * Pi / 180;
		result1 = sin(alpha)*sin(beta)*monitor_l / sin(Pi - alpha - beta);
		if (result1<0) {
			result1 = result1 * (-1);
		}
	}
	if (dr_h_dgree != 0 && dl_h_dgree != 0) {

		alpha = dr_h_dgree * Pi / 180;
		beta = dl_h_dgree * Pi / 180;
		result2 = sin(alpha)*sin(beta)*monitor_l / sin(Pi - alpha - beta);
		if (result2<0) {
			result2 = result2 * (-1);
		}
	}
	if (result1 != 0 && result2 != 0) {
		result = ((monitor_h - result2) + result1) / 2;
	}
	else if (result1 == 0) {
		result = monitor_h - result2;
	}
	else if (result2 == 0) {
		result = result1;
	}
	return result;
}

int calculate_x() {

	int result;
	int result1;
	int result2;
	double alpha;
	double beta;

	if (ur_h_dgree != 0 && dr_h_dgree != 0) {
		alpha = ur_h_dgree * Pi / 180;
		beta = dr_h_dgree * Pi / 180;
		result1 = sin(alpha)*sin(beta)*monitor_h / sin(Pi - alpha - beta);
		if (result1<0) {
			result1 = result1 * (-1);

		}


	}
	if (ul_h_dgree != 0 && dl_h_dgree != 0) {

		alpha = ul_h_dgree * Pi / 180;
		beta = dl_h_dgree * Pi / 180;
		result2 = sin(alpha)*sin(beta)*monitor_h / sin(Pi - alpha - beta);
		if (result2<0) {
			result2 = result2 * (-1);
		}
	}
	if (result1 != 0 && result2 != 0) {
		result = ((monitor_l - result2) + result1) / 2;
	}
	else if (result1 == 0) {
		result = monitor_l - result2;
	}
	else if (result2 == 0) {
		result = result1;
	}
	return result;
}

void clickhaja(Point cursor) {
	SetCursorPos(cursor.x, cursor.y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	//Sleep(10);
}

int main() {
	setting_parsing();
	dr_touched.x = 962;
	dr_touched.y = 370;
	ur_touched.x = 873;
	ur_touched.y = 352;
	ul_touched.x = 853;
	ul_touched.y = 511;
	dl_touched.x = 1324;
	dl_touched.y = 444;

	calculate_dr(dr_touched);
	calculate_ur(ur_touched);
	calculate_ul(ul_touched);
	calculate_dl(dl_touched);

	Point click(0, 0);

	click.x = calculate_x();
	click.y = calculate_y();

	cout << "---clicked---" << endl;
	cout << click << endl;
	for (int i = 0; i < 5; i++) {
	if (click.x != 0 && click.y != 0) {
		//click.x += 40;
		clickhaja(click);
	}
}

	return 0;
}
