
// #include "stdafx.h"
#include "Com.h"
#include "windows.h"
#include "time.h"
#include "stdio.h"
#include "strain.h"
#include <iostream>
#include <tchar.h>
using namespace std;

unsigned char ucComNo[2] ={0,0};

int _tmain(int argc, _TCHAR* argv[])
{
	char chrBuffer[2000];
	unsigned short usLength=0,usCnt=0;
	unsigned long ulBaund=115200,ulComNo=7;
	signed char cResult= 1;	
	
	// printf("\r\nCom = ");
	// scanf("%ld",&ulComNo);
	// printf("\r\nBaud = ");
	// scanf("%ld",&ulBaund);

	while(cResult!=0)
	{
		cResult = OpenCOMDevice(ulComNo,ulBaund);
	}

	while(1)
	{

		usLength = CollectUARTData(ulComNo,chrBuffer);
        // cout << usLength << endl;
		if (usLength>0)
		{
			strain.CopeSerialData(chrBuffer,usLength);
		}
		Sleep(100);
		int torque[4];
        for(int i = 0; i <4; i++)
        {
            switch(strain.stcStrain.s[i])
            {
                case 0x30: torque[i] = 0; break;
                case 0x31: torque[i] = 1; break;
                case 0x32: torque[i] = 2; break;
                case 0x33: torque[i] = 3; break;
                case 0x34: torque[i] = 4; break;
                case 0x35: torque[i] = 5; break;
                case 0x36: torque[i] = 6; break;
                case 0x37: torque[i] = 7; break;
                case 0x38: torque[i] = 8; break;
                case 0x39: torque[i] = 9; break;
            }
        }
        printf("force: %.2f\n", float(torque[0]*1000 + torque[1]*100 + torque[2]*10 + torque[3]));
	}
		return 0;
}

