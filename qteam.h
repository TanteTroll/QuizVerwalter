#ifndef QTEAM_H
#define QTEAM_H

#include <QObject>
#include <vector>
#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QPushButton>
#include <QList>

class QTeam : public QObject
{
	Q_OBJECT

public:
	std::vector <QString> TeamMembers;
	QString TeamName;

	QTeam(QObject *parent = 0);
	~QTeam();
	void ui_view(QWidget *ui);
	void deleteEmptyMembers();
	

public slots:
	void setTeamName(const QString str);
	void setTeamMembers(const QString str);

signals:
	void nameChange(QString str);

private:
	QWidget * ui;
	QVBoxLayout *layout_teamPlayers;


};

class QTeams : public QObject
{
	Q_OBJECT
public:
	QTeams(QObject *parent = 0);

	QList<QTeam*> teamNames;

	
	void readFromXml();
	void deleteEmptyTeams();
	void ui_view(QWidget *ui);
	

public slots:
	void editTeam();
	void saveToXml();

private:
	QWidget * ui_buttons;
	QWidget * ui_content;
	QHBoxLayout *layout_team;

	QPushButton *thisButton;
	QPushButton *lastButton = NULL;

};
#endif // QTEAM_H
