// #include "stdafx.h"
#include "encoder.h"
#include "string.h"
#include <iostream>

using namespace std;

Encoder ::Encoder ()
{
}

void Encoder ::CopeSerialData(char ucData[],unsigned short usLength)
{
	static unsigned char chrTemp[2000];
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;


    memcpy(chrTemp,ucData,usLength);
	usRxLength += usLength;
    while (usRxLength >= 10)
    {
        if (chrTemp[0] != 0x23)
        {
			usRxLength--;
			memcpy(&chrTemp[0],&chrTemp[1],usRxLength);                        
            continue;
        }
		switch(chrTemp[1])
		{
			case 0x0B: memcpy(&stcEncoder,&chrTemp[2],8);break;
		}
		usRxLength -= 10;
		memcpy(&chrTemp[0],&chrTemp[10],usRxLength);                     
    }
}
Encoder encoder = Encoder();