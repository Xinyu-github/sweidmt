/*
 *  Copyright (C) 2012 - 2013 Melanie Strake
 *
 *  Chair of Medical Engineering (mediTEC)
 *  RWTH Aachen University
 *  Pauwelsstr. 20
 *  52074 Aachen
 *  Germany
 *
 */

#include "ApplicationData.h"
#include <QApplication>


// ----------------------------------------------------------------------------------
// ApplicationData
// ----------------------------------------------------------------------------------

ApplicationData::ApplicationData()
{
	widget1Finished = false;
	m_pImage = new short[512 * 512];
	m_3DImage = new short[66560 * 512];
	m_tiefenkarte = new short[512*512];
	
}


ApplicationData::~ApplicationData()
{
	// Speicehr wieder freigeben
	delete[] m_pImage;
	delete[] m_3DImage;
}
