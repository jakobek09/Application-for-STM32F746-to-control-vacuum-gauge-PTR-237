#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <cmsis_os2.h>
#include "main.h"

extern "C"
{
	extern osSemaphoreId_t binarySemADCHandle;
	extern uint32_t convertedVal[300];
}


Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if(binarySemADCHandle != NULL)
	{
		if(osSemaphoreAcquire(binarySemADCHandle, 0) == osOK)
		{
			setADC();
		}
	}
}
void Model::setADC()
{
	uint32_t val1 = 0, val2 = 0, val3 = 0;


	for(int j = 0; j<100;j++)
	{
		val1 += convertedVal[j*3];
		val2 += convertedVal[j*3+1];
		val3 += convertedVal[j*3+2];
	}
	modelListener->setADC(val1/100, val2/100, val3/100);
}
