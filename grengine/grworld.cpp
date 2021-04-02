/*

File name: grWorld.cpp

Description:
see grWorld.h file for a description about this class

*/


#include "stdafx.h"
#include "grWorld.h"
#include <gl/gl.h>


BOOL const grWorld::load(CString const &file)
{
	// Check if a world file is already loaded
	if (isLoaded())
		unload();

	// Attach cars and pills objects to track object
	Track.attach(&HumanCar);
	Track.attach(&ComputerCar);
	for (int i=0; i<PILL_ONTRACK_NUM*4; i++)
		Track.attach(&Pill[i]);

	// Load given XML file
	BOOL retval = TRUE;
	if (file != "")
	{
		XmlDoc XMLDoc;

		if (XMLDoc.read((LPCTSTR) file) && (XMLDoc.root().id == "GoroRacesTrack"))
			XMLRead(XMLDoc.root());
		else
			retval = FALSE;
	}

	// Set isLoaded flag
	isLoadedFlag = TRUE;

	return retval;
}


BOOL const grWorld::unload(void)
{
	// Check if there is a world to unload
	if (!isLoaded())
		return FALSE;

	// Detach cars and pills objects to prevent destruction
	HumanCar.detach();
	ComputerCar.detach();
	for (int i=0; i<PILL_ONTRACK_NUM*4; i++)
		Pill[i].detach();

	// Unload all track objects
	while (Track.hasChild())
		delete Track.childNode;

	// Set isLoaded flag
	isLoadedFlag = FALSE;

	return TRUE;
}


void grWorld::XMLWrite(CStdioFile &fp)
{
	fp.WriteString("<GoroRacesTrack>\n");

	HumanCar.XMLWrite(fp);
	ComputerCar.XMLWrite(fp);

	fp.WriteString("</GoroRacesTrack>\n");
}


void grWorld::XMLRead(Xml &Tag)
{
	ASSERT(Tag.id == "GoroRacesTrack");

	for (Xml::iterator TagIter = Tag.begin(); TagIter != Tag.end(); TagIter++)
	{
		Xml cTag = *TagIter;
		
			if (cTag.id == "HumanCar") HumanCar.XMLRead(cTag);
		else
			if (cTag.id == "ComputerCar") ComputerCar.XMLRead(cTag);
	}
}


grWorld::grWorld(void)
{
	// Set some world attributes
	setId("World");
	isLoadedFlag = FALSE;

	// Set default world objects attributes
	Track.setId("Track");
	HumanCar.setId("HumanCar");
	ComputerCar.setId("ComputerCar");

	CString pillID;
	// Loop for each quarter of track
	for (int q=0; q<4; q++)
		// Loop for each pill in each quarter
		for (int p=0; p<PILL_ONTRACK_NUM; p++)
		{
			// Find current pill index
			int cpi = p + q * PILL_ONTRACK_NUM;

			// Set pill ID
			pillID.Format("Pill#%d", cpi);
			Pill[cpi].setId(pillID);

			// Set pill position on track
			Pill[cpi].setOnTrackPos(grPill::PillOnTrackAngle[p] + M_PI_2*q,
									grPill::PillOnTrackTraj[p]);
		}

	// Attach track object
	attach(&Track);
}


grWorld::~grWorld(void)
{
	// Unload any loaded world file
	unload();

	// Detach track object
	Track.detach();
}