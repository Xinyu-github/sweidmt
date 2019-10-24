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

#include "TestWidget3.h"
#include "QFrameworkDLL\QWidgetEvent.h"
#include "dll.hpp"

// ----------------------------------------------------------------------------------
// TestWidget3
// ----------------------------------------------------------------------------------

TestWidget3::TestWidget3(ApplicationData *data, QFramework* widget)
	: QWidget(widget)
{
	framework = widget;
	this->data = data;
	ui.setupUi(this);
	


	// Beispielaufruf einer Funktion aus einer DLL
	useDLL();
}



bool TestWidget3::event(QEvent* e)
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

void TestWidget3::on_load8bit_clicked()
{
	// test data for \ref TestWidget3
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

void TestWidget3::on_load12bit_clicked()
{
	// test data for \ref TestWidget3
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

void TestWidget3::on_startSlider_valueChanged()
{
	// Verbindet Bildeinlesen mit Slider
	TestWidget3::Update2DView();
}

void TestWidget3::on_widthSlider_valueChanged()
{
	// Verbindet Bildeinlesen mit Slider
	TestWidget3::Update2DView();
}

void TestWidget3::on_Schicht_valueChanged()
{
	// Verbindet Bildeinlesen mit Slider
	TestWidget3::Update2DView();
	TestWidget3::Tiefenkarte(ui.Schicht->value());
}
void TestWidget3::on_HUWert_valueChanged()
{
	// Verbindet Bildeinlesen mit Slider
	TestWidget3::Update2DView();
}
void TestWidget3::Update2DView()
{
	// test data for \ref TestWidget3
	data->widget1Finished = true;
	//data->m_pImage = new short[512 * 512];

	// processing finished
	QApplication::postEvent(framework, new QWidgetEvent(QWidgetEvent::FinishWorkingStep));

	// update status box of framework widget with a confirmation message
	framework->statusBox->writeConfirmMessage("sub menu 2 processed");
	// Erzeuge ein Objekt vom Typ Image
	QImage image(512, 512, QImage::Format_RGB32);


	QFile DataFile(qApp->applicationDirPath().append("/../../../../res/kopf_CT_130.raw"));
	bool bFileOpen = DataFile.open(QIODevice::ReadOnly);
	if (!bFileOpen)
	{
		QMessageBox::critical(this, "ACHTUNG", "Datei konnte nicht geöffnet werden");
		return;
	}
	DataFile.read((char*)data->m_3DImage, 66560 * 512 * sizeof(short));
	unsigned long i = ui.Schicht->value()*262144;
	int sx = 500; int sy = 500;
	int Tx = 0; int Ty = 0; int Iref; float denominator; 
	// Schreibe Inhalt in das Bild
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			if (x < sx)
			{
				Tx = data->m_tiefenkarte[x, y] - data->m_tiefenkarte[x + sx, y];
			}
			else if(x > (512-sx))
			{
				Tx = data->m_tiefenkarte[x - sx, y] - data->m_tiefenkarte[x, y];
			}
			else
			{
				Tx = data->m_tiefenkarte[x - sx, y] - data->m_tiefenkarte[x + sx, y];
			}
			if (y < sy)
			{
				Ty = data->m_tiefenkarte[x, y] - data->m_tiefenkarte[x, y+sy];
			}
			else if (y > (512 - sy))
			{
				Ty = data->m_tiefenkarte[x, y - sy] - data->m_tiefenkarte[x, y];
			}
			else
			{
				Ty = data->m_tiefenkarte[x, y-sy] - data->m_tiefenkarte[x, y+sy];
			}//??????????????????????????
			denominator = (sy*Tx)^2 + (sx*Ty)^2 + (sx*sy)^2;
			int k = fenster(50, 1500, data->m_3DImage[i]);
			if (k < ui.HUWert->value())
			{
				Iref = 255 * sx*sy / (sqrt(denominator));
				image.setPixel(x, y, qRgb(Iref, Iref, Iref));
			}
			else
			{
				image.setPixel(x, y, qRgb(255, 0, 0));
			}

			

			i++;
		}
	}
	ui.lbImage->setPixmap(QPixmap::fromImage(image));

}

int TestWidget3::fenster(int startValue, int windowWidth, int fileValue)
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
void TestWidget3::useDLL()
{
	int result = answer("What is the answer to life, the universe and everything?");
}
void TestWidget3::Tiefenkarte(int schicht)
{
	
	for (int i = schicht; i < 129; i++)
	{
		int m = i * 262144;
		for (int y = 0; y < 512; y++)
		{
			for (int x = 0; x < 512; x++)
			{
				int k = fenster(50, 1500, data->m_3DImage[m]);
				if (k != 0)
				{
					if (data->m_tiefenkarte[x, y] == 0)
					{
						data->m_tiefenkarte[x, y] = i;
					}
				}
			}
		}
	}
		
}
void TestWidget3::Update2DView()
{
	// test data for \ref TestWidget3
	data->widget1Finished = true;
	//data->m_pImage = new short[512 * 512];

	// processing finished
	QApplication::postEvent(framework, new QWidgetEvent(QWidgetEvent::FinishWorkingStep));

	// update status box of framework widget with a confirmation message
	framework->statusBox->writeConfirmMessage("sub menu 2 processed");
	// Erzeuge ein Objekt vom Typ Image
	QImage image(512, 512, QImage::Format_RGB32);


	QFile DataFile(qApp->applicationDirPath().append("/../../../../res/kopf_CT_130.raw"));
	bool bFileOpen = DataFile.open(QIODevice::ReadOnly);
	if (!bFileOpen)
	{
		QMessageBox::critical(this, "ACHTUNG", "Datei konnte nicht geöffnet werden");
		return;
	}
	DataFile.read((char*)data->m_3DImage, 66560 * 512 * sizeof(short));
	unsigned long i = ui.Schicht->value() * 262144;
	int sx = 200; int sy = 200;
	int Tx = 0; int Ty = 0; int Iref; float denominator;
	// Schreibe Inhalt in das Bild
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			if (x <sx)
			{
				Tx = data->m_tiefenkarte[x, y] - data->m_tiefenkarte[x + sx, y];
			}
			else if (x >(512 - sx))
			{
				Tx = data->m_tiefenkarte[x - sx, y] - data->m_tiefenkarte[x, y];
			}
			else
			{
				Tx = data->m_tiefenkarte[x - sx, y] - data->m_tiefenkarte[x + sx, y];
			}
			if (y < sy)
			{
				Ty = data->m_tiefenkarte[x, y] - data->m_tiefenkarte[x, y + sy];
			}
			else if (y >(512 - sy))
			{
				Ty = data->m_tiefenkarte[x, y - sy] - data->m_tiefenkarte[x, y];
			}
			else
			{
				Ty = data->m_tiefenkarte[x, y - sy] - data->m_tiefenkarte[x, y + sy];
			}// Schreibe Tiefenkarten unterschiede
			denominator = (sy*Tx)*(sy*Tx) + (sx*Ty)*(sy*Ty) + (sx*sy)* (sx*sy);
			
			Iref = 255 * sx*sy / (sqrt(denominator));
			image.setPixel(x, y, qRgb(Iref,Iref,Iref));
						


			i++;
		}
	}
	ui.lbImage->setPixmap(QPixmap::fromImage(image));

}


void TestWidget3::mousePressEvent(QMouseEvent*event)
{
	QPoint globalPos= (event->x,event->y);
	QPoint localPos= ui.lbImage->mapFromParent(globalPos);

	if (ui.lbImage->rect().contains(localPos))
	{ 
		voxel seed;
		seed.x = localPos.x;
		seed.y = localPos.y;
		seed.z = data->m_tiefenkarte[localPos.x, localPos.y];
	}
}

