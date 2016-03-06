#ifndef QUIZVERWALTER_H
#define QUIZVERWALTER_H

#include <QtWidgets/QMainWindow>
#include "ui_quizverwalter.h"
#include "qteam.h"
#include "qquiz.h"

class QuizVerwalter : public QMainWindow
{
	Q_OBJECT
public:
	QuizVerwalter(QWidget *parent = 0);
	~QuizVerwalter();

public slots:
	void on_pushButtonTeams_clicked();
	void on_pushButtonQuiz_clicked();

private:
	Ui::QuizVerwalterClass ui;

	QTeams *teams = NULL;
	QQuiz *quiz = NULL;
};

#endif // QUIZVERWALTER_H
