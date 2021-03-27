#pragma once
#include "grcar.h"

class grHumanCar : public grCar
{
// Overrides
public:
	// Draw function
	void onDraw();

	// Save object info to given file
	virtual void XMLWrite(CStdioFile &fp);
	// Load object info from given file
	virtual void XMLRead(Xml &Tag);

// Constructors and destructors
public:
	grHumanCar(void);
	~grHumanCar(void) { }
};
