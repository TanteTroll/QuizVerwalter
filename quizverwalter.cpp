#include "quizverwalter.h"
#include "qteam.h"
#include "qquiz.h"

QuizVerwalter::QuizVerwalter(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	teams = new QTeams();
	quiz = new QQuiz();
	quiz->ui_view(ui.contentWidget);
	connect(ui.pushButtonSave, &QPushButton::clicked, teams, &QTeams::saveToXml);
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
	quiz->ui_view(ui.contentWidget);
}
