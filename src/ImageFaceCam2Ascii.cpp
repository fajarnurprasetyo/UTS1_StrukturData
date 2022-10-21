#include "opencv2/opencv.hpp"
#include "curses.h"

int main()
{
	cv::VideoCapture camera(0);

	if (!camera.isOpened())
		return 1;

	const float
		size = 5,
		alpha = 1.5,
		beta = -20;

	initscr();
	cbreak();
	noecho();

	cv::Mat frame;
	while (true) {
		camera >> frame;

		resize_term(frame.rows / (size * 2), frame.cols / size);
		for (int y = 0, py = 0; py < frame.rows; y++, py = y * size * 2)
		{
			for (int x = 0, px = 0; px < frame.cols; x++, px = x * size) {
				if (px < frame.cols && py < frame.rows) {
					int b = frame.at<cv::Vec3b>(py, px)[0];
					int g = frame.at<cv::Vec3b>(py, px)[1];
					int r = frame.at<cv::Vec3b>(py, px)[2];

					int avg = (b + g + r) / 3;

					if (avg > 246.2) mvaddstr(y, x, "Ñ");
					else if (avg > 237.4) mvaddstr(y, x, "@");
					else if (avg > 228.6) mvaddstr(y, x, "#");
					else if (avg > 219.8) mvaddstr(y, x, "W");
					else if (avg > 211.0) mvaddstr(y, x, "$");
					else if (avg > 202.2) mvaddstr(y, x, "9");
					else if (avg > 293.4) mvaddstr(y, x, "8");
					else if (avg > 184.6) mvaddstr(y, x, "7");
					else if (avg > 175.8) mvaddstr(y, x, "6");
					else if (avg > 167.0) mvaddstr(y, x, "5");
					else if (avg > 158.3) mvaddstr(y, x, "4");
					else if (avg > 149.5) mvaddstr(y, x, "3");
					else if (avg > 140.7) mvaddstr(y, x, "2");
					else if (avg > 131.9) mvaddstr(y, x, "1");
					else if (avg > 123.1) mvaddstr(y, x, "0");
					else if (avg > 114.3) mvaddstr(y, x, "?");
					else if (avg > 105.5) mvaddstr(y, x, "!");
					else if (avg > 96.7) mvaddstr(y, x, "a");
					else if (avg > 87.9) mvaddstr(y, x, "b");
					else if (avg > 79.1) mvaddstr(y, x, "c");
					else if (avg > 70.3) mvaddstr(y, x, ";");
					else if (avg > 61.5) mvaddstr(y, x, ":");
					else if (avg > 52.7) mvaddstr(y, x, "+");
					else if (avg > 43.9) mvaddstr(y, x, "=");
					else if (avg > 35.2) mvaddstr(y, x, "-");
					else if (avg > 26.8) mvaddstr(y, x, ",");
					else if (avg > 17.5) mvaddstr(y, x, ".");
					else if (avg > 8.8) mvaddstr(y, x, "_");
					else mvaddstr(y, x, " ");
				}
			}
			refresh();
		}
	}

	nocbreak();
	echo();
	endwin();
	return 0;
}
