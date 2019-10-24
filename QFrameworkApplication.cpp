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

#include "QFrameworkApplication.h"
#include <QDebug>


// ----------------------------------------------------------------------------------
// QFrameworkApplication
// ----------------------------------------------------------------------------------

QFrameworkApplication::QFrameworkApplication(int& argc, char ** argv) :
	QApplication(argc, argv) 
{
	// create framework widget
	qFramework = new QFramework();
	// create data object, which collects all application data
	data = new ApplicationData();

	// create submenu widgets
	tWidget1 = new TestWidget1(data, qFramework);
//	tWidget2 = new TestWidget2(data, qFramework);
	tWidget3 = new TestWidget3(data, qFramework);
//	tWidget4 = new TestWidget4(data, qFramework);
}

QFrameworkApplication::~QFrameworkApplication()
{
	delete data;

	delete tWidget1;


	delete qFramework;
}

// reimplemented from QApplication so we can throw exceptions in slots
bool QFrameworkApplication::notify(QObject * receiver, QEvent * event) {
	try {
		return QApplication::notify(receiver, event);
	} 
	catch(std::exception& e) {
		qCritical() << "Exception thrown:" << e.what();
	}
	return false;
}

// ----------------------------------------------------------------------------------
// main
// ----------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	// create application
	QFrameworkApplication app(argc, argv);

	// pass path to stylesheet for submenu widgets
	app.qFramework->setSubmenuStylesheet("../../src/res/MeditecStyle_ChildWidget.qss");

	// create menus and their submenus
	app.qFramework->addMenu("Menu 1");
	app.qFramework->addSubMenu("Menu 1", "Submenu 1", app.tWidget1);
	//app.qFramework->addSubMenu("Menu 1", "Submenu 2", app.tWidget2);

	app.qFramework->addMenu("Menu 2");
	app.qFramework->addSubMenu("Menu 2", "Submenu 3", app.tWidget3);

	//app.qFramework->addMenu("Menu 3");
	//app.qFramework->addSubMenu("Menu 3", "Submenu 4", app.tWidget4);

	// run framework
	app.qFramework->enter();
	app.qFramework->showFullScreen();
	app.exec();
}