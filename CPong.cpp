#include "stdafx.h"
#include "CPong.h"
#include<thread>
#include <cstdint>
#include "stdint.h"
#include "typeinfo.h"
using namespace cv;


Point2f pos_ball (500,400);
Point2f velocity (200,200);
Point2f a = (0,30);
CPong::CPong()
{ 
	
	score = 0;
	last = cv::getTickCount();
	control.init_com(4);
	_canvas = cv::Mat::zeros(800,1000, CV_8UC3);
	
}

/*CPong::CPong(cv::Size d, int com)
{
	//_canvas = cv::Mat::zeros(d, CV_8UC3);
	//high = d.height;

	y_new = high / 2;

}*/
void CPong::update()
{
	int y;
	
	press = control.get_button();
	if (press == 0)
	{
		reset();
	}

		control.get_data("G", "1", "9", y);
		y_pos = 8*(100-control.get_analog(y));
		if (y_pos > 750)
			y_pos = 750;
		if (y_pos < 50)
			y_pos = 50;
		//this_thread::sleep_until(end_time);



}
void CPong::draw()
{
	auto calc_start = std::chrono::steady_clock::now();
	
	_canvas = cv::Mat::zeros(800,1000, CV_8UC3);
	
/////Time Calc////
	double time_passed;
	double start = cv::getTickCount();
	
	time_passed = (start-last) / cv::getTickFrequency();
	last = start;
	//physics engine
	velocity += a * time_passed;

	pos_ball += (velocity*time_passed);
	
	//side walls
	if (pos_ball.y > _canvas.size().height-15)
	{
		pos_ball.y = _canvas.size().height-15;
		velocity.y *= -1;
	}
	if (pos_ball.y < 15)
	{
		pos_ball.y = 15;
		velocity.y *= -1;
	}
	if (pos_ball.x > 970)
	{
		pos_ball.x = 970;
		velocity.x *= -1;
	}

	if (pos_ball.x < 0)
	{
		score++;
		pos_ball.x = 500;
		pos_ball.y = 400;
		velocity.x = 200;
		velocity.y = 200;
		//reset();
		//pos_ball.x = 0;
		//velocity.x *= -1.2;
	}
	if (score > 5)
	{
		score = 0;
	}
	
	if (pos_ball.x < 35 &&(pos_ball.y<y_pos+50 && pos_ball.y>y_pos-50))
	{
		pos_ball.x =35 ;
		velocity.x *= -1;
	}
	circle(_canvas,pos_ball, 15, CV_RGB(255, 255, 255),-1);
	rectangle(_canvas, Point(25,y_pos-50 ), Point(10,y_pos+50), Scalar(255, 255, 255),CV_FILLED, y_pos);
	line(_canvas, Point(500, 0), Point(500, 1000), Scalar(255, 255, 0), 1, 8, 0);

	/////////////////////////
	///////Computer paddle//
	////////////////////////
	rectangle(_canvas, Point(995, pos_ball.y-50), Point(980, pos_ball.y+50), Scalar(255, 255, 255),CV_FILLED ,0 );

	putText(_canvas,"Player 1 : 0",Size(100,30),FONT_HERSHEY_PLAIN,2,Scalar(255,255,255),2,cv::LINE_AA);
	putText(_canvas, "GOD :"+to_string(score), Size(700, 30), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255),2, cv::LINE_AA);
	

	auto calc_end = std::chrono::steady_clock::now();
	auto calc_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(calc_end - calc_start);
	//std::cout << "\nElapsed Time: " << calc_elapsed.count();
	
	//frameTime = (cv::getTickCount()-frameStart) /cv::getTickFrequency();
	if (frameDelay > calc_elapsed.count())
	{
		Sleep(frameDelay- calc_elapsed.count());
		putText(_canvas, "FPS :" + to_string(1000/ (frameDelay - calc_elapsed.count())), Size(425, 30), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 1, cv::LINE_AA);
	}

	imshow("Image", _canvas);

}


void CPong::reset()
{

	score=0;
	pos_ball.x = 500;
	pos_ball.y = 400;
	velocity.x = 200;
	velocity.y = 200;
	imshow("Image", _canvas);
}
CPong::~CPong()
{
	
}
