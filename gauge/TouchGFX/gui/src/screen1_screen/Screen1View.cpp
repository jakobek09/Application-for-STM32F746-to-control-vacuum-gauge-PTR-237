#include <gui/screen1_screen/Screen1View.hpp>
#include "string.h"
#include "cmsis_os2.h"
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <touchgfx/Color.hpp>
#include <cwchar>
#include <thread>

extern "C"
{
	extern bool is_On;
	extern TIM_HandleTypeDef htim3;
	extern double statMain;
	extern double suppMain;
	extern int timStop;
	extern int secureInc;
	extern bool check;

}

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

double Screen1View::getStat() {return stat;}

double Screen1View::getSupp() {return supp;}

void Screen1View::setADC(uint32_t pressureVolt, uint32_t statusVolt, uint32_t supplyVolt)
{

	pVolt = 3.300 * pressureVolt / 4096.000;
	stVolt = 3.300 * statusVolt / 4096.000;
	suppVolt = 3.300 * supplyVolt/ 4096.000;


	memset(&pinVoltBuffer,0,PINVOLT_SIZE);
	memset(&statVoltBuffer,0,STATVOLT_SIZE);
	memset(&powerVoltBuffer,0,POWERVOLT_SIZE);
	memset(&textArea1Buffer,0,TEXTAREA1_SIZE);
	memset(&realVoltBuffer,0,REALVOLT_SIZE);
	memset(&textBigPressBuffer,0,TEXTBIGPRESS_SIZE);
	Unicode::snprintfFloat(pinVoltBuffer, PINVOLT_SIZE, "%.3f", pVolt);
	pinVolt.invalidate();
	Unicode::snprintfFloat(statVoltBuffer, STATVOLT_SIZE, "%.3f", stVolt);
	statVolt.invalidate();
	//Unicode::snprintfFloat(powerVoltBuffer, POWERVOLT_SIZE, "%.3f", suppVolt);
	Unicode::snprintfFloat(powerVoltBuffer, POWERVOLT_SIZE, "%.3f", gaugeVal);
	powerVolt.invalidate();
	Unicode::snprintfFloat(realVoltBuffer, REALVOLT_SIZE, "%.3f", pVolt/0.3346);
	realVolt.invalidate();

	statMain = stVolt;
	suppMain = suppVolt;

	if((stVolt) > 1.8)
	{
		circleStatusPainter.setColor(touchgfx::Color::getColorFromRGB(79, 203, 3));
		circleStatus.setPainter(circleStatusPainter);
		staticText2.setAlpha(255);
		staticText2.invalidate();
		circleStatus.invalidate();
	}
	else
	{
		circleStatusPainter.setColor(touchgfx::Color::getColorFromRGB(173, 49, 49));
		circleStatus.setPainter(circleStatusPainter);
		staticText2.setAlpha(100);
		staticText2.invalidate();
		circleStatus.invalidate();
	}

	if((suppVolt) > 1.8)
	{
		circlePowerPainter.setColor(touchgfx::Color::getColorFromRGB(79, 203, 3));
		circlePower.setPainter(circlePowerPainter);
		circlePower.invalidate();
		staticText3.setAlpha(255);
		staticText3.invalidate();
	}
	else
	{
		circlePowerPainter.setColor(touchgfx::Color::getColorFromRGB(173, 49, 49));
		circlePower.setPainter(circlePowerPainter);
		circlePower.invalidate();
		staticText3.setAlpha(100);
		staticText3.invalidate();
	}
	double x,y;
	switch(timStop)
	{
		case 0:
			volt2 = std::round(pVolt*1000)/1000;
			result = pow(10,(((volt2/0.3346)-12.66)/1.33));
			snprintf(str, 50, "%.2e",result);
			Unicode::strncpy(buff, str, 20);
			boxWithBorder1.setAlpha(0);
			statusText.setAlpha(0);
			powerText.setAlpha(0);
			staticText1.setAlpha(255);
			textArea1.setAlpha(255);
			if(view)
				Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", buff);
			else
			{
				textBigPress.setVisible(true);
				Unicode::snprintf(textBigPressBuffer, TEXTBIGPRESS_SIZE, "%s", buff);
				textBigPress.invalidate();
			}

			x = abs(ceil(log10(result)));
			y = result * pow(10,x+1);
			gaugeVal = 10*(x+1)+(10-(int)y);

			gauge1.setValue(100-gaugeVal);
			gauge1.setAlpha(255);
			gauge1.invalidate();


			/*if(secureInc >= 28)
			{
				Screen1View::secure(result);
			}*/
			if(secureOn)
				secure(result);

			showTrend(result);
			break;
		case 1:
			boxWithBorder1.setAlpha(136);
			statusText.setAlpha(0);
			powerText.setAlpha(255);
			Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%c", '-');
			gauge1.setValue(0);
			gauge1.setAlpha(100);
			gauge1.invalidate();
			textBigPress.setVisible(false);
			textBigPress.invalidate();
			break;
		case 2:
			boxWithBorder1.setAlpha(136);
			statusText.setAlpha(255);
			powerText.setAlpha(0);
			Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%c", '-');
			gauge1.setValue(0);
			gauge1.setAlpha(100);
			gauge1.invalidate();
			textBigPress.setVisible(false);
			textBigPress.invalidate();
			break;
		case 3:
			boxWithBorder1.setAlpha(136);
			statusText.setAlpha(255);
			powerText.setAlpha(255);
			Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%c", '-');
			gauge1.setValue(0);
			gauge1.setAlpha(100);
			gauge1.invalidate();
			textBigPress.setVisible(false);
			textBigPress.invalidate();
			break;
	}
	boxWithBorder1.invalidate();
	statusText.invalidate();
	powerText.invalidate();
	textArea1.invalidate();
	staticText1.invalidate();

}

/*void Screen1View::secure(double pressure)
{
	if(pressure1 != 0)
	{
		magnitude = abs(ceil(log10(pressure)));
		magnitude1 = abs(ceil(log10(pressure1)));
		if(abs(magnitude - magnitude1) > 2.5)
		{
			warningText.setAlpha(255);
			boxWithBorder2.setAlpha(136);
			warningText.invalidate();
			boxWithBorder2.invalidate();
			toggleButton1.setTouchable(false);
			is_On = false;

		}
	}
	pressure1 = pressure;
}*/

void Screen1View::secure(double pressure)
{
	if(pressure1 != 0)
	{
		if((pressure1 - pressure) > (0.01 - pressure1)/10)
		{
			warningText.setAlpha(255);
			boxWithBorder2.setAlpha(136);
			warningText.invalidate();
			boxWithBorder2.invalidate();
			toggleButton1.setTouchable(false);
			is_On = false;

		}
		magnitude = abs(ceil(log10(pressure)));
		magnitude1 = abs(ceil(log10(pressure1)));
		if(abs(magnitude - magnitude1) > 2.5)
		{
			warningText.setAlpha(255);
			boxWithBorder2.setAlpha(136);
			warningText.invalidate();
			boxWithBorder2.invalidate();
			toggleButton1.setTouchable(false);
			is_On = false;

		}
	}
	pressure1 = pressure;
}

void Screen1View::changeView()
{
	if(view)
	{
		gauge1.setVisible(false);
		textArea1.setVisible(false);
		textBigPress.setVisible(true);
		gauge1.invalidate();
		textArea1.invalidate();
		textBigPress.invalidate();
		view = false;
	}
	else
	{
		gauge1.setVisible(true);
		textArea1.setVisible(true);
		textBigPress.setVisible(false);
		gauge1.invalidate();
		textArea1.invalidate();
		textBigPress.invalidate();
		view = true;
	}
}


// Funkcja do obsługi przycisku OnOff
void Screen1View::onOffClicked() {
	if(!toggleButton1.getState())
		{
			is_On = true;
			HAL_TIM_Base_Start_IT(&htim3);
			gauge1.setAlpha(255);
			gauge1.invalidate();

		}
		else
		{
			HAL_TIM_Base_Stop_IT(&htim3);
			is_On = false;
			gauge1.setAlpha(100);
			gauge1.setValue(0);
			gauge1.invalidate();
			staticText1.setAlpha(100);
			staticText1.invalidate();
			staticText3.setAlpha(100);
			staticText3.invalidate();
			staticText2.setAlpha(100);
			staticText2.invalidate();
			textArea1.setAlpha(100);
			textArea1.invalidate();
			circlePowerPainter.setColor(touchgfx::Color::getColorFromRGB(143, 130, 130));
			circlePower.setPainter(circlePowerPainter);
			circleStatusPainter.setColor(touchgfx::Color::getColorFromRGB(143, 130, 130));
			circleStatus.setPainter(circleStatusPainter);
			circlePower.invalidate();
			circleStatus.invalidate();
			boxWithBorder1.setAlpha(0);
			statusText.setAlpha(0);
			powerText.setAlpha(0);
			boxWithBorder1.invalidate();
			statusText.invalidate();
			powerText.invalidate();
		}

}

void Screen1View::showTrend(double x)
{
	trend[currentIndex] = x;
	currentIndex = (currentIndex + 1) % valuesSize;

	if(trend[5] != 0)
	{
		double diff1 = trend[3] - trend[1];
		double diff2 = trend[4] - trend[2];
		double diff3 = trend[5] - trend[3];

		if(diff1 < 0 && diff2 < 0 && diff3 < 0)
		{
			shape_up.setVisible(false);
			shape_down.setVisible(true);
		}
		else if(diff1 > 0 && diff2 > 0 && diff3 > 0)
		{
			shape_up.setVisible(true);
			shape_down.setVisible(false);
		}
		else
		{
			shape_up.setVisible(false);
			shape_down.setVisible(false);
		}
		shape_up.invalidate();
		shape_down.invalidate();
	}
}

void Screen1View::secureOnOff()
{

	if(secureOn)
	{
		viewButton_1.setLabelText(TypedText(0));
		viewButton_1.setLabelColor(touchgfx::Color::getColorFromRGB(255,0,0));
		secureOn = false;
	}
	else
	{
		viewButton_1.setLabelText(TypedText(1));
		viewButton_1.setLabelColor(touchgfx::Color::getColorFromRGB(0,255,0));
		secureOn = true;
	}

}




