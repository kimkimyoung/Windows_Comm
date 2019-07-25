#include "Com.h"
#include "windows.h"
#include "time.h"
#include "stdio.h"
#include <tchar.h>
#include <iostream>
#include "encoder.h"

using namespace std;
extern float encoder_data;

int _tmain(int argc, _TCHAR* argv[])
{
    char chrBuffer[2000];
    unsigned short usLength=0, usCnt=0;
    unsigned long ulBaund=115200,ulComNo=9;
	signed char cReset= 1;
    signed char cModeSelect = 1;
    signed char cResult = 1;
    signed char cConfig = 1;

	printf("\r\nCom = ");
	scanf("%ld",&ulComNo);
	printf("\r\nBaud = ");
	scanf("%ld",&ulBaund);

    //  打开串口
	while(cResult != 0)
	{
		cResult = OpenCOMDevice(ulComNo,ulBaund);
	}

    const unsigned char ResetBuffer[] = {0x23, 0x00, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
    DWORD ResetBufferLen = sizeof(ResetBuffer) / sizeof(ResetBuffer[0]);
    
    //  发送重置指令
    while(cReset != 0)
    {
        cReset = SendUARTMessageLength(ulComNo, ResetBuffer, ResetBufferLen);
    }
    
    Sleep(500);

    //  发送模式选择指令
    const unsigned char ModeSelectBuffer[] = {0x23, 0x01, 0x04, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
    DWORD ModeSelectBufferLen = sizeof(ModeSelectBuffer) / sizeof(ModeSelectBuffer[0]);
    
    while(cModeSelect != 0)
    {
        cModeSelect = SendUARTMessageLength(ulComNo, ModeSelectBuffer, ModeSelectBufferLen);
    }

    //  发送配置指令
    const unsigned char ConfigBuffer[] = {0x23, 0x0A, 0x0A, 0x00, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
    DWORD ConfigBufferLen = sizeof(ConfigBuffer) / sizeof(ConfigBuffer[0]);
    
    while(cConfig != 0)
    {
        cConfig = SendUARTMessageLength(ulComNo, ConfigBuffer, ConfigBufferLen);
    }

    while(1)
	{
		usLength = CollectUARTData(ulComNo,chrBuffer);
        if (usLength>0)
		{
			encoder.CopeSerialData(chrBuffer,usLength);
		}
		Sleep(100);
        // encoder_data = (float)( (encoder.stcEncoder.p[0] << 24) | (encoder.stcEncoder.p[1] << 16) | (encoder.stcEncoder.p[2] << 8) | (encoder.stcEncoder.p[3]) );
        printf("Position: %f\r\n",(float)( (encoder.stcEncoder.p[0] << 24) | (encoder.stcEncoder.p[1] << 16) | (encoder.stcEncoder.p[2] << 8) | (encoder.stcEncoder.p[3]) ));
    }
    return 0;
}