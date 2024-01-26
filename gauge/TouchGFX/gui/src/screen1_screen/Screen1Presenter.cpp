#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::setADC(uint32_t pressureVolt, uint32_t statusVolt, uint32_t supplyVolt)
{
	view.setADC(pressureVolt, statusVolt, supplyVolt);
}
