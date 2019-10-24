

#ifndef __TESTWIDGET3_H__
#define __TESTWIDGET3_H__


#include <QFrameworkDLL\QFramework.h>
#include <qwidget.h>
#include "ApplicationData.h"
#include "ui_TestWidget3.h"
#include <QMessageBox> 




class TestWidget3: public QWidget
{
	Q_OBJECT

public:

	TestWidget3(ApplicationData *data, QFramework* widget = 0);
	

	/** \brief	Releases...
	  */
	~TestWidget3();

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
	Ui::TestWidget3 ui;
	
	/** \brief	References application data
	  */
	ApplicationData* data;

	/** \brief	Example how to call function from Dll
	  */
	void useDLL();

private slots:

	
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
