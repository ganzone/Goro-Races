#ifndef _GRCOMPUTERCAR_H
#define _GRCOMPUTERCAR_H


#include "grcar.h"


class grComputerCar : public grCar
{
// Attributes
private:
	// The other player car pointer
	grCar *OtherCar;

// Functions
public:
	void setOtherCar(grCar &OtherCar) { this->OtherCar = &OtherCar; }

// Overrides
public:
    void onAnimate(DWORD deltaTime);
	void onDraw();

	// Save object info to given file
	virtual void XMLWrite(CStdioFile &fp);
	// Load object info from given file
	virtual void XMLRead(Xml &Tag);

// Constructors and destructors
public:
	grComputerCar(void);
	~grComputerCar(void) { }
};


#endif // _GRCOMPUTERCAR_H