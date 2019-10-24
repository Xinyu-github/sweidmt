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

#ifndef __QFRAMEWORKAPPLICATION_H__
#define __QFRAMEWORKAPPLICATION_H__

#include <QApplication>
#include "QFrameworkDLL\QFramework.h"
#include "ApplicationData.h"
#include "TestWidget1.h"
#include "TestWidget3.h"



// ----------------------------------------------------------------------------------
// QFrameworkApplication
// ----------------------------------------------------------------------------------

/** \brief	application class
  *
  * It keeps all necessary components of a QFrameworkDLL application: the framework widget itself,
  * an application data class and all submenu widget classes. 
  *
  * \author	Melanie Strake
  * \date	17.04.2013
  */
class QFrameworkApplication: public QApplication
{
public:

	/** \brief	Instantiates...
	  */
	QFrameworkApplication(int& argc, char ** argv);
	
	/** \brief	Releases...
	  */
	virtual ~QFrameworkApplication();
	
	/** \brief
	  */
	virtual bool notify(QObject * receiver, QEvent * event);


	/** \brief	framework (main widget)
	  */
	QFramework* qFramework;

	/** \brief	one instance from type \ref ApplicationData will be created and each submenu widget
	  *			will reference this object.
      */
	ApplicationData* data;
	
	/** \brief	submenu widget \ref TestWidget1
	  */
	TestWidget1 *tWidget1;
	TestWidget3 *tWidget3;
};
#endif // __QFRAMEWORKAPPLICATION_H__


