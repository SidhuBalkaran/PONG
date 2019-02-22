#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <conio.h>
#include <istream>
#include "Client.h"
#include "Server.h"
#include "Serial.h"
#include "opencv.hpp"
#include "CBase4618.h"



class CPong:public CBase4618 {
public:
	CPong();
	~CPong();


	/** @brief Sets the desired COM port.
	*
	* @param COM port string.
	* @return nothing to return
	*/
	//CPong(cv::Size d, int);

	/** @brief Sets the desired COM port.
	*
	* @param COM port string.
	* @return nothing to return
	*/
	//~CPong();

	/** @brief Sets the desired COM port.
	*
	* @param COM port string.
	* @return nothing to return
	*/
	void update() override;

	/** @brief Sets the desired COM port.
	*
	* @param COM port string.
	* @return nothing to return
	*/
	void draw() override;

	void reset();
private :
	int y_pos;///< Y value JoYSTICK
	int y_new;
	int high;///< canvas height 
	const int frameDelay = 1000 / 25;
	int frameTime;
	uint32_t frameStart;
	double last;
	int score;
	int press, flag;
};

