#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void setADC();
protected:
    ModelListener* modelListener;
    int ADC_Value;
};

#endif // MODEL_HPP
