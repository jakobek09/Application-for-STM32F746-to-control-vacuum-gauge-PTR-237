#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#define valuesSize 10

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

class Screen1View : public Screen1ViewBase
{
private:
	double pressure1 = 0.0;

public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void setADC(uint32_t pressureVolt, uint32_t statusVolt, uint32_t supplyVolt);
    virtual void onOffClicked();
    virtual void changeView();
    double getStat();
    double getSupp();
    void secure(double pressure);
    void secureOnOff();
    void showTrend(double x);
    void secureOFF();
    void yesButtonClicked();
    void noButtonClicked();


    double stat;
    double supp;
    double volt2;
    double result;
    double pVolt;
    double stVolt;
    double suppVolt;
    double magnitude;
    double magnitude1;
    double pressureMag = 0;

    int gaugeVal = 0;
    int preTimStop = 4;
    bool view = true;
    bool secureOn = false;
    bool startEr = true;
    bool warnStat = true;

    char str[20];
    Unicode::UnicodeChar buff[20];
    double trend[valuesSize] = {0};

    int currentIndex = 0;
    int corr = 0;

protected:


};

#endif // SCREEN1VIEW_HPP
