#include "Grafika.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Grafika w; //Grafika sa napaja do mainu a QtClass sa napaja na Grafiku
	w.show();
	return a.exec();
}
