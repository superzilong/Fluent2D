#include <iostream>

#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "Core/Log/Log.h"

int main(int argc, char *argv[])
{
	Log::Init();

    QApplication a(argc, argv);

	MainWindow MainWinExample;	// Creating an using a QMainWindow with central SDL widget
	LOG_TRACE("Initialize main window");
	
	MainWinExample.show();
	LOG_TRACE("Show window");

	int RetVal = a.exec();	// Most examples have this on the return, we
							// need to have it return to a variable cause:

	LOG_TRACE("Quit!");
	
	return RetVal;
}
