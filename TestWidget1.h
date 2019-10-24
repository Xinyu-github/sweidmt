

#ifndef __TESTWIDGET1_H__
#define __TESTWIDGET1_H__


#include <QFrameworkDLL\QFramework.h>
#include <qwidget.h>
#include "ApplicationData.h"
#include "ui_TestWidget1.h"
#include <QMessageBox> 


// ----------------------------------------------------------------------------------
// TestWidget1
// ----------------------------------------------------------------------------------


class TestWidget1: public QWidget
{
	Q_OBJECT

public:

	
	TestWidget1(ApplicationData *data, QFramework* widget = 0);
	

	/** \brief	Releases...
	  */
	~TestWidget1();

protected:



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
	Ui::TestWidget1 ui;
	
	/** \brief	References application data
	  */
	ApplicationData* data;

	/** \brief	Example how to call function from Dll
	  */
	void useDLL();

private slots:

	
	void on_load8bit_clicked();
	void on_load12bit_clicked();
	int fenster(int, int, int);
	void on_startSlider_valueChanged();
	void on_widthSlider_valueChanged();
	void Update2DView();

};
#endif // __TESTWIDGET1_H__
