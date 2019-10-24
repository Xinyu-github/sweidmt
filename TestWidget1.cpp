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

#include "TestWidget1.h"
#include "QFrameworkDLL\QWidgetEvent.h"
#include "dll.hpp"

// ----------------------------------------------------------------------------------
// TestWidget1
// ----------------------------------------------------------------------------------

TestWidget1::TestWidget1(ApplicationData *data, QFramework* widget)
	: QWidget(widget)
{
	framework = widget;
	this->data = data;
	ui.setupUi(this);
	


	// Beispielaufruf einer Funktion aus einer DLL
	useDLL();
}


TestWidget1::~TestWidget1(void)
{
}

bool TestWidget1::event(QEvent* e)
{
	QWidget::event(e);

	if(e->type() == QEvent::Show)  // \ref TestWidget1 is current submenu
	{
		// update framework status box
		if(data->widget1Finished)  // widget has been processed before (re-entrance into widget)
		{
			framework->statusBox->writeConfirmMessage("sub menu 1 processed");
		}
		else  
		{
			framework->statusBox->writeStatusMessage("sub menu 1 in process...");			
		}
	}
	else if(e->type() == QEvent::Hide)  // another submenu will be entered and processed and \ref TestWidget1 submenu will be left
	{
	}

	return true;
}

void TestWidget1::on_load8bit_clicked()
{
	// test data for \ref TestWidget1
	data->widget1Finished = true; 

	// processing finished
	QApplication::postEvent(framework, new QWidgetEvent(QWidgetEvent::FinishWorkingStep));

	// update status box of framework widget with a confirmation message
	framework->statusBox->writeConfirmMessage("sub menu 1 processed");
	QImage image(512, 512, QImage::Format_RGB32);
	
	// Bild in Variable einlesen
	QFile DataFile(qApp->applicationDirPath().append("/../../../../res/8bit.raw"));
	bool bFileOpen = DataFile.open(QIODevice::ReadOnly);
	if (!bFileOpen)
	{
		QMessageBox::critical(this, "ACHTUNG", "Datei konnte nicht geöffnet werden");
		return;
	};
	DataFile.read((char*)data->m_pImage, 512 * 512);
	int i = 0;
	// Schreibe Inhalt in das Bild
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			image.setPixel(x, y, qRgb(data->m_pImage[i], data->m_pImage[i], data->m_pImage[i]));
			i++;
		}
	}
	
	ui.lbImage->setPixmap(QPixmap::fromImage(image));

	//data->m_pImage
	
}

void TestWidget1::on_load12bit_clicked()
{
	// test data for \ref TestWidget1
	data->widget1Finished = true;
	//data->m_pImage = new short[512 * 512];

	// processing finished
	QApplication::postEvent(framework, new QWidgetEvent(QWidgetEvent::FinishWorkingStep));

	// update status box of framework widget with a confirmation message
	framework->statusBox->writeConfirmMessage("sub menu 1 processed");
	// Erzeuge ein Objekt vom Typ Image
	QImage image(512, 512, QImage::Format_RGB32);
	
	// Bild in Variable einlesen
	QFile DataFile(qApp->applicationDirPath().append("/../../../../res/12bit_short.raw"));
	bool bFileOpen = DataFile.open(QIODevice::ReadOnly);
	if (!bFileOpen)
	{
		QMessageBox::critical(this, "ACHTUNG", "Datei konnte nicht geöffnet werden");
		return;
	}
	DataFile.read((char*)data->m_pImage, 512 * 512 * sizeof(short));
	int i = 0;
	// Schreibe Inhalt in das Bild
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			int k = fenster(800, 400, data->m_pImage[i]);
			image.setPixel(x, y, qRgb(k, k, k));
			i++;
		}
	}
	ui.lbImage->setPixmap(QPixmap::fromImage(image));
	
}

void TestWidget1::on_startSlider_valueChanged()
{
	// Verbindet Bildeinlesen mit Slider
	TestWidget1::Update2DView();
}

void TestWidget1::on_widthSlider_valueChanged()
{
	// Verbindet Bildeinlesen mit Slider
	TestWidget1::Update2DView();
}

void TestWidget1::Update2DView()
{
	// test data for \ref TestWidget1
	data->widget1Finished = true;
	//data->m_pImage = new short[512 * 512];

	// processing finished
	QApplication::postEvent(framework, new QWidgetEvent(QWidgetEvent::FinishWorkingStep));

	// update status box of framework widget with a confirmation message
	framework->statusBox->writeConfirmMessage("sub menu 1 processed");
	// Erzeuge ein Objekt vom Typ Image
	QImage image(512, 512, QImage::Format_RGB32);


	QFile DataFile(qApp->applicationDirPath().append("/../../../../res/12bit_short.raw"));
	bool bFileOpen = DataFile.open(QIODevice::ReadOnly);
	if (!bFileOpen)
	{
		QMessageBox::critical(this, "ACHTUNG", "Datei konnte nicht geöffnet werden");
		return;
	}
	DataFile.read((char*)data->m_pImage, 512 * 512 * sizeof(short));
	int i = 0;
	// Schreibe Inhalt in das Bild
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			int k = fenster(ui.startSlider->value(), ui.widthSlider->value(), data->m_pImage[i]);
			image.setPixel(x, y, qRgb(k, k, k));
			i++;
		}
	}
	ui.lbImage->setPixmap(QPixmap::fromImage(image));

}

int TestWidget1::fenster(int startValue, int windowWidth, int fileValue)
{
	int y;
	if (fileValue <= startValue)
	{
		y = 0;
	}
	else if (fileValue >= (startValue + windowWidth))
	{
		y = 255;
	}
	else
	{
		y = (fileValue - startValue)* 255.0 / (windowWidth);
	}
	return y;
}

// Beispielfunktion, wie man auf eine Funktion aus einer DLL zugreift
void TestWidget1::useDLL()
{
	int result = answer("What is the answer to life, the universe and everything?");
}