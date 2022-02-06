#include<lpc21xx.h>
#include "LPC2148_delay.h"

char Data[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};			//comman cathode type;
//char Data[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};			//comman anode type;

int Count;

void Segment_Runner()
{	
	int Disp1_Data,Disp2_Data,Disp3_Data,Disp4_Data;
	int Temp_DATA;
			
	Temp_DATA  = Count;						//6789;
	Disp1_Data = Temp_DATA % 10;	//Disp1=9;
	Temp_DATA  = Temp_DATA / 10;	//678;
	Disp2_Data = Temp_DATA % 10;	//Disp2=8;

//	Temp_DATA  = Temp_DATA / 10;	//67;
//	Disp3_Data = Temp_DATA % 10;	//7;
//	Disp4_Data = Temp_DATA / 10;

	IOSET0 = 0x00000200; 
	IOSET0 = Data[Disp2_Data];
	delay(50);
	IOCLR0 = Data[Disp2_Data];
	IOCLR0 = 0x00000200;
			
	IOSET0 = 0x00000100; 
	IOSET0 = Data[Disp1_Data]; 
	delay(50);
	IOCLR0 = Data[Disp1_Data]; 
	IOCLR0 = 0x00000100;	
}

int main()
{
	PINSEL0 = 0x00000000;
	IODIR0 = 0x000003ff;

	while(1)
	{
		while(IOPIN0 == 0x80000000)
		{
			Count++;
			
			if(Count >= 100)
			{
				Count = 0;
			}
			while(IOPIN0 == 0x80000000);
		}
		Segment_Runner();
	}
}