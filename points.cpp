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
	for (int i = 0; i < quizs->quizList.size(); i++)
	{
		quizauswahl->addItem(quizs->quizList.at(i)->name);
	}
	connect(quizauswahl, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &Points::paintTable);

	QHBoxLayout *layout_participants = new QHBoxLayout;
	layout->addLayout(layout_participants);

	checkbox.clear();
	for (int i = 0; i < teams->teamNames.size(); i++)
	{
		QCheckBox *cb = new QCheckBox(ui);
		checkbox.push_back(cb);
		cb->setText(teams->teamNames.at(i)->TeamName);
		layout_participants->addWidget(cb);
	}

	table = new QTableWidget(ui);
	layout->addWidget(table);
}

void Points::paintTable(const int i)
{
	searchSelectedTeams();
	if (i == 0 || selectedCheckbox.size() == 0)
		return;

	int rowNumber = quizs->quizList.at(i - 1)->Katalog.size() + 1;
	for (int j = 1; j < quizs->quizList.at(i - 1)->Katalog.size(); j++)
	{
		rowNumber += quizs->quizList.at(i - 1)->Katalog.at(j).Frage.size()+1;
	}

	table->setRowCount(rowNumber);
	table->setColumnCount(selectedCheckbox.size() );

	QStringList hLabels;
	for (int k = 0; k < selectedCheckbox.size(); k++ )
	{
		hLabels.push_back(selectedCheckbox.at(k)->text());
	}
	
	QStringList vLabels;
	for (int k = 0; k < quizs->quizList.at(i - 1)->Katalog.size(); k++ )
	{
		vLabels.push_back(quizs->quizList.at(i - 1)->Katalog.at(i).name);
		for (int j = 0; j < quizs->quizList.at(i - 1)->Katalog.at(k).Frage.size(); j++)
		{
			QString tmp = "      " + quizs->quizList.at(i - 1)->Katalog.at(k).Frage.at(j);
			vLabels.push_back(tmp);
		}
	}

	table->setVerticalHeaderLabels(vLabels);
	table->setHorizontalHeaderLabels(hLabels);
}

void Points::searchSelectedTeams()
{
	selectedCheckbox.clear();
	for (int i = 0; i < checkbox.size(); i++)
	{
		if (checkbox.at(i)->isChecked() == true)
			selectedCheckbox.push_back(checkbox.at(i));
	}
}