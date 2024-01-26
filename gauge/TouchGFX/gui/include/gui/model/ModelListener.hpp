#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "main.h"

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    virtual void setADC(uint32_t pressureVolt, uint32_t statusVolt, uint32_t supplyVolt) {}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
