#ifndef QUIZVERWALTER_H
#define QUIZVERWALTER_H

#include <QtWidgets/QMainWindow>
#include "ui_quizverwalter.h"
#include "qteam.h"
#include "qquiz.h"
#include "points.h"
//TODO QQUIZ
//TODO QDATA
//TODO QVISUAL
class QuizVerwalter : public QMainWindow
{
	Q_OBJECT
public:
	QuizVerwalter(QWidget *parent = 0);
	~QuizVerwalter();

public slots:
	void on_pushButtonTeams_clicked();
	void on_pushButtonQuiz_clicked();
	void on_pushButtonErgebnis_clicked();

private:
	Ui::QuizVerwalterClass ui;

	QTeams *teams = NULL;
	QQuizs *quizs = NULL;
	Points *point = NULL;

	std::vector<QString> test;
	QString str;
};

#endif // QUIZVERWALTER_H
