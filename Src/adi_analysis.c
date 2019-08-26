#include "adi_analysis.h"

#define ADI_DATA_CALICOUNT 180000
#define ADI_ANGVEL_K 300.0*0.00001/32767.0*3.725//4736

const double ADI_Angvel_k=ADI_ANGVEL_K;

ADI_DataTypeDef ADI_Data=ADI_DATA_DEFAULT;

void ADI_DataCalibration(void)
{
	
}

int dealdata=0;
void ADI_DataDeal_Task(uint16_t rawdata)
{
	ADI_Data.angvel.rawdata=rawdata;
	ADI_Data.angvel.rawdata-=ADI_Data.angvel.offset;
	
	if(ADI_Data.angvel.cali_state==0)
	{
		ADI_Data.angvel.cali_offsetsum+=ADI_Data.angvel.rawdata;
		ADI_Data.angvel.cali_count++;
		if(ADI_Data.angvel.cali_count>=ADI_DATA_CALICOUNT)
		{
			ADI_Data.angvel.offset+=ADI_Data.angvel.cali_offsetsum/ADI_DATA_CALICOUNT;
			ADI_Data.angvel.cali_state=1;
			ADI_Data.angvel.cali_count=0;
			ADI_Data.angvel.cali_offsetsum=0;
		}
	}
	else
	{
		ADI_Data.angvel.cali_count=0;
		ADI_Data.angvel.cali_offsetsum=0;
	}
	
	if(ADI_Data.angvel.cali_state==1)
	{
		dealdata=ADI_Data.angvel.rawdata;
		ADI_Data.angvel.filterdata=ADI_Data.angvel.rawdata*ADI_Angvel_k;
		ADI_Data.Zangle+=ADI_Data.angvel.filterdata;
	}
	
}
