#pragma once

class misPlugInBase
{
public:
	virtual  void Initilize()=0;
	virtual   void Updtae(double* pos,double*  direction)=0;

	misPlugInBase(void);
	~misPlugInBase(void);
};

