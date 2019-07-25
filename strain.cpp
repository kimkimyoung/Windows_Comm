// #include "stdafx.h"
#include "strain.h"
#include "string.h"
#include <iostream>

using namespace std;

Strain::Strain()
{
}
void Strain::CopeSerialData(char ucData[],unsigned short usLength)
{
	static unsigned char chrTemp[2000];
    static unsigned char chrZero[1] = {0x30};
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;

    memcpy(chrTemp,ucData,usLength);
	usRxLength += usLength;

    if (usLength == 5)
    {
        memcpy(&stcStrain,&chrZero,1);
        memcpy(&stcStrain.s[1],&chrTemp,3);
    }
    else if(usLength == 6)
    {
        memcpy(&stcStrain,&chrTemp,4);
    }
}
Strain strain = Strain();