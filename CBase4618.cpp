#include "stdafx.h"
#include "CBase4618.h"

CBase4618::CBase4618()
{

}
void CBase4618::draw()
{

}
void CBase4618::run()
{
do
{
update();
draw();
} while (cv::waitKey(1) !='q');
}
void CBase4618::update()
{

}
CBase4618::~CBase4618()
{
	control.set_data("0", "39", "0");
	control.set_data("0", "37", "0");
	control.set_data("0", "38", "0");
}
