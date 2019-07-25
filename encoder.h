#ifndef encoder_h
#define encoder_h

struct SEncoder
{
	unsigned char c[2];
	unsigned char v[2];
	unsigned char p[4];
};

class Encoder 
{
	public: 
	
		struct SEncoder stcEncoder;	
    	Encoder (); 
    	void CopeSerialData(char ucData[],unsigned short usLength);
};
extern Encoder encoder;
// extern float encoder_data;
#endif