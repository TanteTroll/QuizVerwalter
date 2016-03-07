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

//Layout
#include <QVBoxLayout>
#include <QHBoxLayout>

//xml
#include <QtXml>
#include <QFile>


std::vector <QString> QTeam::badNames{ "niggers" };

QTeam::QTeam(QObject *parent)
	:QObject(parent)
{

}
QTeams::QTeams(QObject *parent)
	: QObject(parent)
{
	readFromXml();
}
QTeam::~QTeam(){}
void qClearWidget(QWidget * ui)
{
	while (QWidget* w = ui->findChild<QWidget*>())
	{
		delete w->layout();
		delete w;
	}
	delete ui->layout();
}
void QTeam::setTeamName(const QString str)
{
	if (std::find(badNames.begin(), badNames.end(), str) != badNames.end()) {
		qDebug() << "bad Name" << str;
	}
	else {
		this->TeamName = str;
		emit nameChange(str);
	}
	
}

/// <summary>
/// SLOT
/// changes Name of Team Members depending on calling Object 
///		(linEdit object name in form of "lineedit[I]" where
///		[I] := position of Name in vector
/// add new Name if calling with
///		[I] exceeds size of vector
/// </summary>
/// <param name="str">New Name of Team Member</param>
void QTeam::setTeamMembers(const QString str)
{
	QObject *obj = QObject::sender();
	QString senderobjName = obj->objectName();
	QStringList list = senderobjName.split("lineedit");
	int index = list[1].toInt();
	if (index < TeamMembers.size() ) TeamMembers.at(index) = str;
	else if (str != "")
	{
		TeamMembers.push_back(str);
		QHBoxLayout *layout_teamPlayer = new QHBoxLayout;
		QLabel *player_label = new QLabel;
		QLineEdit  *player_line = new QLineEdit;
		player_label->setText("Spieler " + QString::number(index + 2));
		player_line->setObjectName("lineedit" + QString::number(index + 1));

		connect(player_line, &QLineEdit::textChanged, this, &QTeam::setTeamMembers);

		layout_teamPlayer->addWidget(player_label);
		layout_teamPlayer->addWidget(player_line);
		layout_teamPlayers->addLayout(layout_teamPlayer);
	}
}

/// <summary>
/// Create Ui to Edit the Team
/// </summary>
/// <param name="ui_">Widget where to create the ui</param>
void QTeam::ui_view(QWidget * ui_)
{
	ui = ui_;
	qClearWidget(ui);
	QVBoxLayout *layout = new QVBoxLayout(ui);
	layout->setAlignment(Qt::AlignTop);

	//Name des Teams
	QHBoxLayout *layout_teamName = new QHBoxLayout;
	QLabel *teamname_label = new QLabel(ui);
	QLineEdit  *teamname_line = new QLineEdit(ui);

	layout_teamName->setAlignment(Qt::AlignLeft);
	layout_teamName->addWidget(teamname_label);
	layout_teamName->addWidget(teamname_line);
	layout->addLayout(layout_teamName);

	teamname_label->setText("Name des Teams");
	teamname_line->setText(this->TeamName);

	connect(teamname_line, &QLineEdit::textEdited, this, &QTeam::setTeamName);


	layout_teamPlayers = new QVBoxLayout;
	for (int i = 0; i <= this->TeamMembers.size(); i++)
	{
		QHBoxLayout *layout_teamPlayer = new QHBoxLayout;
		QLabel *player_label = new QLabel(ui);
		QLineEdit  *player_line = new QLineEdit(ui);

		layout_teamPlayer->addWidget(player_label);
		layout_teamPlayer->addWidget(player_line);
		layout_teamPlayers->addLayout(layout_teamPlayer);

		player_label->setText("Spieler " + QString::number(i + 1));
		if (i < this->TeamMembers.size())
			player_line->setText(TeamMembers.at(i));
		player_line->setObjectName("lineedit" + QString::number(i));

		connect(player_line, &QLineEdit::textChanged, this, &QTeam::setTeamMembers );
	}
	layout->addLayout(layout_teamPlayers);
}

void QTeam::deleteEmptyMembers()
{
	for (int i = 0; i < TeamMembers.size(); i++)
	{
		if (TeamMembers.at(i) == "")
		{
			TeamMembers.erase(TeamMembers.begin() + i);
		}
	}
}
void QTeams::deleteEmptyTeams()
{
	for (int i = 0; i < teamNames.size(); i++)
	{
		teamNames.at(i)->deleteEmptyMembers();
		if (teamNames.at(i)->TeamName == "" || teamNames.at(i)->TeamMembers.size() == 0)
		{
			teamNames.erase(teamNames.begin() + i);
		}
	}
}

void QTeams::ui_view(QWidget * ui_)
{
	
	this->deleteEmptyTeams();
	lastButton = NULL;
	qClearWidget(ui_);
	
	QVBoxLayout *mainlayout = new QVBoxLayout(ui_);

	ui_buttons = new QWidget(ui_);
	ui_content = new QWidget(ui_);
	
	mainlayout->addWidget(ui_buttons, 1);
	mainlayout->addWidget(ui_content, 9);
	
	QVBoxLayout *layout = new QVBoxLayout(ui_buttons);
	layout->setAlignment(Qt::AlignTop);

	layout_team = new QHBoxLayout;
	for (int i = 0; i <= this->teamNames.size(); i++)
	{
		QPushButton *button_team = new QPushButton;
		layout_team->addWidget(button_team);
		button_team->setObjectName("button" + QString::number(i));

		if (i < this->teamNames.size())
		{
			button_team->setText(teamNames.at(i)->TeamName);
			connect(teamNames.at(i), &QTeam::nameChange, button_team, &QPushButton::setText);
		}
		else
			button_team->setText("new Team");

		connect(button_team, &QPushButton::clicked, this, &QTeams::editTeam);
	}
	layout->addLayout(layout_team);	
}
void QTeams::editTeam()
{
	QObject *obj = QObject::sender();
	thisButton = qobject_cast<QPushButton *>(obj);
	if (lastButton) lastButton->setStyleSheet( "" );
	thisButton->setStyleSheet(
		"background-color: black;"
		"border-style: outset;"
		"border-width: 2px;"
		"font: bold 14px;"
		"color: white;"
		);
	QString senderobjName = thisButton->objectName();
	QStringList list = senderobjName.split("button");
	int index = list[1].toInt();
	
	if (index < teamNames.size())
	{
		teamNames.at(index)->deleteEmptyMembers();
		teamNames.at(index)->ui_view(ui_content);
	}
	else if (index == teamNames.size())
	{
		
		QTeam *newTeam = new QTeam();
		newTeam->TeamName = "new Team";
		newTeam->TeamMembers.push_back("new Player");
		teamNames.push_back(newTeam);
		newTeam->ui_view(ui_content);

		QPushButton *button_team = new QPushButton;
		layout_team->addWidget(button_team);
		button_team->setObjectName("button" + QString::number(index + 1));
		button_team->setText("new Team");

		connect(newTeam, &QTeam::nameChange, thisButton, &QPushButton::setText);
		connect(button_team, &QPushButton::clicked, this, &QTeams::editTeam);
	}
	lastButton = thisButton;
}


void QTeams::saveToXml()
{
	deleteEmptyTeams();

	QFile file("Resources/Teams.xml");
	file.open(QIODevice::WriteOnly);

	if (!file.isOpen()) { qDebug("Cannot open File! (teams)"); return; }
	qDebug("File opened! (teams)");

	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement("Teams");
	xmlWriter.writeAttribute("NumberOfTeams", QString::number(this->teamNames.size()) );
	for (int i = 0; i < this->teamNames.size(); i++)
	{
		xmlWriter.writeStartElement("Team");
		xmlWriter.writeAttribute("Teamname", this->teamNames.at(i)->TeamName);
		xmlWriter.writeAttribute("NumberOfTeamMembers", QString::number(this->teamNames.at(i)->TeamMembers.size()));
		for (int j = 0; j < this->teamNames.at(i)->TeamMembers.size(); j++)
		{
			xmlWriter.writeTextElement("Spieler", this->teamNames.at(i)->TeamMembers.at(j) );
		}
		xmlWriter.writeEndElement();
	}
	xmlWriter.writeEndElement();

	file.close();
}
void QTeams::readFromXml()
{
	QXmlStreamReader Rxml;

	QFile file("Resources/Teams.xml");
	file.open(QFile::ReadOnly | QFile::Text);
	if (!file.isOpen()) { qDebug("Cannot open File!"); return; }

	Rxml.setDevice(&file);
	Rxml.readNext();

	
	QTeam *newTeam;

	while (!Rxml.atEnd())
	{
		//Suche nach start Elementen
		if (Rxml.isStartElement())	
		{

			//TeamS Element enthält name des Teams
			if (Rxml.name() == "Teams")	
			{
				int numberOfTeams = Rxml.attributes().value("NumberOfTeams").toInt();
			}

			//Team enthält Namen der TeamMember
			if (Rxml.name() == "Team")
			{
				//lese header
				QString teamname = Rxml.attributes().value("Teamname").toString();
				int numberOfTeamMembers = Rxml.attributes().value("NumberOfTeamMembers").toInt();

				newTeam = new QTeam();
				newTeam->TeamName = teamname;

				//lese TextAttribute
				while (!Rxml.atEnd())
				{
					Rxml.readNext();
					//keine weitern Elemente vorhanden
					if (Rxml.isEndElement()) break;

					//Text Element gefunden
					if (Rxml.isStartElement())
					{
						// Spieler einlesen
						QString Spieler = Rxml.readElementText();
						newTeam->TeamMembers.push_back(Spieler);

						//warte auf ende des Text Elementes
						while (!Rxml.isEndElement()|| Rxml.atEnd() ) Rxml.readNext();
					}
				}

				this->teamNames.push_back(newTeam);
			}
		}
		Rxml.readNext();
	}
	file.close();
}