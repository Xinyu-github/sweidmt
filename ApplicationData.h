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

#ifndef __APPLICATIONDATA_H__
#define __APPLICATIONDATA_H__

#include <QString>
#include <QFile>
#include <QApplication>


// ----------------------------------------------------------------------------------
// ApplicationData
// ----------------------------------------------------------------------------------

/** \brief	data class, which holds all necessary application data.
  *
  * The ApplicationData class is kept very simple. A boolean variable exists for every submenu.
  *	Once its value is set to true, the processsing of the corresponding submenu is finished. 
  *
  * \author	Melanie Strake
  * \date	17.04.2013
  */
class ApplicationData
{
public:

	/** \brief Instantiates all member variables
	  */
	ApplicationData();
	

	/** \brief	Releases...
	  */
	~ApplicationData();


	/** \brief	Indicates, if proccessing of submenu widget \ref TestWidget1 has been finished or not.
	  *
	  * \note	just test data for \ref TestWidget1
	  */
	bool widget1Finished;
	
	short* m_pImage;
	short* m_3DImage;
	short* m_tiefenkarte;


};
#endif // __APPLICATIONDATA_H__

