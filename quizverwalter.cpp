#include "quizverwalter.h"
#include "qteam.h"
#include "qquiz.h"
#include "points.h"

QuizVerwalter::QuizVerwalter(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	teams = new QTeams();
	quizs = new QQuizs();
	point = new Points(teams, quizs);

	point->ui_view(ui.contentWidget);

	connect(ui.pushButtonSave, &QPushButton::clicked, teams, &QTeams::saveToXml);
	connect(ui.pushButtonSave, &QPushButton::clicked, quizs, &QQuizs::saveToXml);
}

QuizVerwalter::~QuizVerwalter()
{
	
}

void QuizVerwalter::on_pushButtonTeams_clicked()
{
	teams->ui_view(ui.contentWidget);
}
void QuizVerwalter::on_pushButtonQuiz_clicked()
{
	quizs->ui_view(ui.contentWidget);
}
