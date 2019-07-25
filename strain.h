#ifndef strain_h
#define strain_h

struct Sstrain
{
    unsigned char s[4];
};

class Strain 
{
	public: 
	
		struct Sstrain stcStrain;	
    	Strain (); 
    	void CopeSerialData(char ucData[],unsigned short usLength);
};
extern Strain strain;

#endif