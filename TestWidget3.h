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

#ifndef __TESTWIDGET3_H__
#define __TESTWIDGET3_H__


#include <QFrameworkDLL\QFramework.h>
#include <qwidget.h>
#include "ApplicationData.h"
#include "ui_TestWidget3.h"
#include <QMessageBox> 


// ----------------------------------------------------------------------------------
// TestWidget1
// ----------------------------------------------------------------------------------

/** \brief	Widget class of "Submenu 1"
  *
  * User finishes the processing of this submenu with a click on the push button "Click 1".
  *
  * \author	Melanie Strake
  * \date	18.04.2013
  */
class TestWidget3: public QWidget
{
	Q_OBJECT

public:

	/** \brief	Instantiates...
	  *
	  * \param	data	application data
	  * \param	widget	framework (parent widget)
	  *
	  * \note	\ref widget has to reference a widget from type \c QFramework, 
	  *			if text message of the framework status box should be modified. 
	  *			Otherwise the constructor can look like this: TestWidget1(CData *data, QWidget* widget = 0)
	  *
	  * \note	framework status box = QFrameworkDLL::QFramework::statusBox
	  */
	TestWidget3(ApplicationData *data, QFramework* widget = 0);
	

	/** \brief	Releases...
	  */
	~TestWidget3();

protected:

	/** \brief Event handling
	  *
	  *	Reimplements handling of \c QEvent::Show and \c QEvent::Hide. 
	  * \c QEvent::Show is posted in case of an entrance or re-entrance into submenu widget \ref TestWidget1. 
	  * \c QEvent::Hide is posted in case of leaving submenu widget \ref TestWidget1 to enter and process another submenu widget. 
	  */

	bool event(QEvent* e);

signals:
	void valueChanged(int);


private:
	
	/** \brief	References framework (parent widget)
	  *
	  * \note	QFrameworkDLL::QFramework
	  */
	QFramework* framework;

	/** \brief References Ui::TestWidget1
	  */
	Ui::TestWidget3 ui;
	
	/** \brief	References application data
	  */
	ApplicationData* data;

	/** \brief	Example how to call function from Dll
	  */
	void useDLL();

private slots:

	/** \brief	Called, when push button "Click 1" is clicked. Induces end of process, so that next submenu 
	  *			can be entered and processed. In this case next submenu is "Submenu 2" (class \ref TestWidget2).
	  *
	  * In detail:
	  *	Boolean value of \ref ApplicationData::widget1Finished is set to true. 
	  * Important:  \c QFrameworkDLL::QWidgetEvent::FinishWorkingStep event is posted to framework widget. 
	  * The status box content of the framework widget is updated with a confirmation message.
	  *
	  * \note	The status box content of the framework can also be used for general information and does not 
	  *			have to be updated in every submenu widget. This is just an example. 
	  *			Instead submenu widget \ref TestWidget1 can hold an own status box.
	  *
	  * \note	QFrameworkDLL::QWidgetEvent::FinishWorkingStep
	  * \note	QFrameworkDLL::QStatusBox 
	  */
	void mousePressEvent(QMouseEvent*event);
	void on_load8bit_clicked();
	void on_load12bit_clicked();
	//int fenster(int, int, int);
	void on_startSlider_valueChanged();
	void on_widthSlider_valueChanged();
	void on_Schicht_valueChanged();
	void on_HUWert_valueChanged();
	void Update2DView();
	void Tiefenkarte(int);

};
#endif // __TESTWIDGET1_H__