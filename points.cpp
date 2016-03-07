#include "points.h"
#include "qquiz.h"
#include "qteam.h"
#include <vector>
#include <algorithm>

// Qt 
#include <QDebug>
#include <QString>
#include <QList>

//ui Elemente
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckbox>
#include <QTableWidget>

//Layout
#include <QVBoxLayout>
#include <QHBoxLayout>

//xml
#include <QtXml>
#include <QFile>
Points::Points(QTeams *teams_, QQuizs *quizs_, QObject *parent)
	:QObject(parent)
{
	teams = teams_;
	quizs = quizs_;
}

Points::~Points()
{

}

void Points::ui_view(QWidget * ui)
{
	while (QWidget* w = ui->findChild<QWidget*>())
	{
		delete w->layout();
		delete w;
	}
	delete ui->layout();

	QVBoxLayout *layout = new QVBoxLayout(ui);
	layout->setAlignment(Qt::AlignTop);

	//main UI
	QComboBox *quizauswahl = new QComboBox(ui);
	quizauswahl->addItem("Select a Quiz");
	layout->addWidget(quizauswahl);
	qDebug() << quizs->quizList.size();
	for (int i = 0; i < quizs->quizList.size(); i++)
	{
		quizauswahl->addItem(quizs->quizList.at(i)->name);
	}
	connect(quizauswahl, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Points::paintTable);

	QHBoxLayout *layout_participants = new QHBoxLayout;
	layout->addLayout(layout_participants);

	selectedTeams.clear();
	for (int i = 0; i < teams->teamNames.size(); i++)
	{
		QCheckBox *cb = new QCheckBox(ui);
		selectedTeams.push_back(cb);
		cb->setText(teams->teamNames.at(i)->TeamName);
		layout_participants->addWidget(cb);
	}

	table = new QTableWidget(ui);
	layout->addWidget(table);
}

void Points::paintTable(const int i)
{
	if (i == 0 || selectedTeams_number() == 0)
		return;

	int rowNumber = 1 ;
	for (int j = 0; j < quizs->quizList.at(i - 1)->Katalog.size(); j++)
	{
		rowNumber += quizs->quizList.at(i - 1)->Katalog.at(j).Frage.size();
		rowNumber ++;
	}

	qDebug() << rowNumber; qDebug() << 2 + selectedTeams_number();
	table->setRowCount(rowNumber);
	table->setColumnCount(2 + selectedTeams_number());

	for (int hLabels = 0; hLabels < selectedTeams_number(); hLabels++ )
	{
		QTableWidgetItem();//TODO
	}
}
int Points::selectedTeams_number()
{
	int number = 0;
	for (int i = 0; i < selectedTeams.size(); i++)
	{
		if (selectedTeams.at(i)->isChecked() == true)
			number = number +1;
	}
	
	return number;
}