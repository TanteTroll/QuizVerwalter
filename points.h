#ifndef POINTS_H
#define POINTS_H

#include <QObject>
#include <vector>
#include <QWidget>
#include <QTableWidget>
#include <QCheckBox>
#include <QString>

#include "qquiz.h"
#include "qteam.h"

class Points : public QObject
{
	Q_OBJECT

public:
	Points(QTeams *teams_, QQuizs *quizs_, QObject *parent = 0);
	~Points();

	void ui_view(QWidget * ui);

public slots:
	void paintTable(const int i);

private:
	QTeams *teams;
	QQuizs *quizs;
	std::vector<QCheckBox*> checkbox;
	std::vector<QCheckBox*> selectedCheckbox;
	void searchSelectedTeams();


	QTableWidget *table;
	
};

#endif // POINTS_H
