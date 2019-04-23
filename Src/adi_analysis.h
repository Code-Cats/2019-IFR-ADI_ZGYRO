#ifndef __ADI_ANALYSIS_H
#define __ADI_ANALYSIS_H

#include "stm32f1xx_hal.h"

typedef struct
{
	struct 
	{
		int offset;
		int rawdata;
		double filterdata;
		uint8_t cali_state;
		uint32_t cali_count;
		int cali_offsetsum;
	}angvel;
	double Zangle;
}ADI_DataTypeDef;



#define ADI_DATA_DEFAULT \
{ \
	{ \
		INT16_MAX,0,0,0,0 \
	}, \
	0.0f \
}

void ADI_DataDeal_Task(uint16_t rawdata);

#endif
