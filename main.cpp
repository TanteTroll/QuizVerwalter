#include "quizverwalter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QuizVerwalter w;
	w.show();
	return a.exec();
}
