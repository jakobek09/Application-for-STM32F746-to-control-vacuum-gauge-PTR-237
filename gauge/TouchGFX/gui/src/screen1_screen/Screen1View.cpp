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
	Unicode::snprintfFloat(powerVoltBuffer, POWERVOLT_SIZE, "%.3f", suppVolt);
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
	}
	double x,y;
	int part;
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
			y = (result * pow(10,x+1));

			gaugeVal = 10*(x+1)+((int)y);

			part = gaugeVal/10;
			corr = 100 + gaugeVal - (20*part);

			gauge1.setValue(corr);
			gauge1.setAlpha(255);
			gauge1.invalidate();


			if(secureOn)
				secure(result);

			showTrend(result);
			break;
		case 1:
			if(warnStat)
			{
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
			}
		case 2:
			if(warnStat)
			{
				boxWithBorder1.setAlpha(136);
				statusText.setAlpha(255);
				powerText.setAlpha(0);
				Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%c", '-');
				gauge1.setValue(0);
				gauge1.setAlpha(100);
				gauge1.invalidate();
				textBigPress.setVisible(false);
				textBigPress.invalidate();
			}
			break;
		case 3:
			if(warnStat)
			{
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
	int32_t selectedButton = radioButtonGroup1.getSelectedRadioButtonIndex();
	int sec = 0;

	if(selectedButton == 0)
	{
		sec = 1;						//HIGH
	}
	else if(selectedButton == 1)
	{
		sec = 10;                       //LOW
	}
	else if(selectedButton == 2)
	{
		sec = 5;                        //MEDIUM
	}

	if(pressure1 != 0)
	{
		if((pressure1 - pressure) > (0.0001 - pressure1) * sec)
		{
			secureOFF();
		}
		if(secureInc > 38)
		{
			if(pressureMag != 0)
			{
			magnitude = abs(ceil(log10(pressure)));
			magnitude1 = abs(ceil(log10(pressureMag)));
				if(abs(magnitude - magnitude1) > 0.5)
				{
					secureOFF();
				}
			}
			pressureMag = pressure;
		}
	}
	pressure1 = pressure;
}

void Screen1View::secureOFF()
{
	warnStat = false;
	warningText.setAlpha(255);
	boxWithBorder2.setAlpha(200);
	warningText.invalidate();
	boxWithBorder2.invalidate();
	toggleButton1.setTouchable(false);
	yesButton.setVisible(true);
	noButton.setVisible(true);
	yesButton.invalidate();
	noButton.invalidate();
	HAL_GPIO_WritePin(controlPin_GPIO_Port, controlPin_Pin, GPIO_PIN_RESET);
	textBigPress.setVisible(false);

}

void Screen1View::yesButtonClicked()
{
	warnStat = true;
	warningText.setAlpha(0);
	boxWithBorder2.setAlpha(0);
	warningText.invalidate();
	boxWithBorder2.invalidate();
	toggleButton1.setTouchable(true);
	yesButton.setVisible(false);
	noButton.setVisible(false);
	yesButton.invalidate();
	noButton.invalidate();
	HAL_GPIO_WritePin(controlPin_GPIO_Port, controlPin_Pin, GPIO_PIN_SET);
}

void Screen1View::noButtonClicked()
{
	warnStat = true;
	yesButton.setVisible(false);
	noButton.setVisible(false);
	yesButton.invalidate();
	noButton.invalidate();
	toggleButton1.setTouchable(true);
	toggleButton1.forceState(true);
	toggleButton1.invalidate();
	warningText.setAlpha(0);
	boxWithBorder2.setAlpha(0);
	warningText.invalidate();
	boxWithBorder2.invalidate();
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
		shape_downPainter.setColor(touchgfx::Color::getColorFromRGB(226, 243, 0));
		shape_down.setPainter(shape_downPainter);
		shape_upPainter.setColor(touchgfx::Color::getColorFromRGB(226, 243, 0));
		shape_up.setPainter(shape_upPainter);
		shape_up.invalidate();
		shape_down.invalidate();
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
		shape_downPainter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		shape_down.setPainter(shape_downPainter);
		shape_upPainter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		shape_up.setPainter(shape_upPainter);
		shape_up.invalidate();
		shape_down.invalidate();
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
		highRadio.setVisible(false);
		mediumRadio.setVisible(false);
		lowRadio.setVisible(false);
		textArea_H.setVisible(false);
		textArea_M.setVisible(false);
		textArea_L.setVisible(false);
		highRadio.invalidate();
		mediumRadio.invalidate();
		lowRadio.invalidate();
		textArea_H.invalidate();
		textArea_M.invalidate();
		textArea_L.invalidate();
	}
	else
	{
		viewButton_1.setLabelText(TypedText(1));
		viewButton_1.setLabelColor(touchgfx::Color::getColorFromRGB(0,255,0));
		secureOn = true;
		highRadio.setVisible(true);
		mediumRadio.setVisible(true);
		lowRadio.setVisible(true);
		textArea_H.setVisible(true);
		textArea_M.setVisible(true);
		textArea_L.setVisible(true);
		highRadio.invalidate();
		mediumRadio.invalidate();
		lowRadio.invalidate();
		textArea_H.invalidate();
		textArea_M.invalidate();
		textArea_L.invalidate();
	}

}




