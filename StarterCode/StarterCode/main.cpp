#include "startercode.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StarterCode w;
	w.show();
	return a.exec();
}
