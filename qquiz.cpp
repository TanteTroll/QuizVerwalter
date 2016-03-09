#include "qquiz.h"
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
#include <QSizePolicy>
#include <QScrollArea>
#include <QLayout>

//Layout
#include <QVBoxLayout>
#include <QHBoxLayout>

//xml
#include <QtXml>
#include <QFile>
std::vector <QString> QQuiz::badNames{ "niggers" };

void ClearWidget(QWidget * ui)
{
	while (QWidget* w = ui->findChild<QWidget*>())
	{
		delete w->layout();
		delete w;
	}
	delete ui->layout();
}

QQuiz::QQuiz(QObject *parent)
	: QObject(parent)
{

}

QQuizs::QQuizs(QObject *parent)
	: QObject(parent)
{
	readFromXml();
}

QQuiz::~QQuiz()
{

}

void QQuiz::setName(const QString str)
{
	if (std::find(badNames.begin(), badNames.end(), str) != badNames.end()) {
		qDebug() << "bad Name" << str;
	}
	else {
		this->name = str;
		emit nameChange(str);
	}
}

void QQuiz::ui_view(QWidget * ui_)
{
	ClearWidget(ui_);
	FragenWidgets.empty();
	
	ui = ui_;
	

	QVBoxLayout *layout = new QVBoxLayout(ui);
	layout->setAlignment(Qt::AlignTop);

	//Name des Teams
	QHBoxLayout *layout_Name = new QHBoxLayout;
	QLabel *name_label = new QLabel(ui);
	QLineEdit  *name_line = new QLineEdit(ui);

	layout_Name->setAlignment(Qt::AlignLeft);
	layout_Name->addWidget(name_label);
	layout_Name->addWidget(name_line);
	layout->addLayout(layout_Name);

	name_label->setText("Name des Quiz");
	name_line->setText(this->name);

	connect(name_line, &QLineEdit::textEdited, this, &QQuiz::setName);


	// Kategorien
	
	dynamic = new QWidget(ui);
	
	QScrollArea *area = new QScrollArea;

	area->setWidget(dynamic);
	layout->addWidget(area);

	layout_content = new QVBoxLayout(dynamic);
	layout_content->setSizeConstraint(QLayout::SetMinAndMaxSize);
	layout_content->setAlignment(Qt::AlignTop);
	QVBoxLayout *tmp = new QVBoxLayout(area);
	tmp->addWidget(dynamic);


	

	for (int i = 0; i <= this->Katalog.size(); i++)	
	{
		QHBoxLayout *layout_entry = new QHBoxLayout;
		layout_entry->setSizeConstraint(QLayout::SetMinAndMaxSize);
		layout_content->addLayout(layout_entry);

		QLineEdit *line_kat = new QLineEdit(dynamic);
		QWidget *question_widget = new QWidget(dynamic);
		
		layout_entry->addWidget(line_kat, 2);
		layout_entry->addWidget(question_widget, 8);
		FragenWidgets.push_back(question_widget);

		QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
		line_kat->setSizePolicy(sizePolicy);
		line_kat->setObjectName("kat" + QString::number(i) );
		line_kat->setMinimumHeight(70);
		
		if (i < this->Katalog.size())
		{
			line_kat->setText(this->Katalog.at(i).name);

			QGridLayout *layout_questions = new QGridLayout(question_widget);
			layout_content->addLayout(layout_questions);
			// Question Widget
			for (int j = 0; j <= this->Katalog.at(i).Frage.size(); j++)
			{
				QLineEdit *line_qu = new QLineEdit(question_widget);
				line_qu->setMinimumHeight(30);
				layout_questions->addWidget(line_qu, j/2 , j%2);
				line_qu->setObjectName(QString::number(i) + "," + QString::number(j));
				


				if (j < this->Katalog.at(i).Frage.size())
				{
					line_qu->setText(this->Katalog.at(i).Frage.at(j));
				}
				else
					line_qu->setText("neue Frage");

				connect(line_qu, &QLineEdit::textChanged, this, &QQuiz::setQues);
			}
		}
		else
			line_kat->setText("neue Kategorie");

		connect(line_kat, &QLineEdit::textChanged, this, &QQuiz::setKat);

		
	}
	
}

int QQuiz::numberOfQuestions()
{
	return 0;
}

void QQuiz::setKat(const QString str)
{
	QObject *obj = QObject::sender();
	QLineEdit *thisLine = qobject_cast<QLineEdit *>(obj);

	QString senderobjName = thisLine->objectName();
	QStringList list = senderobjName.split("kat");
	int index = list[1].toInt();

	if (index < Katalog.size())
	{
		Katalog.at(index).name = str;
	}
	else if (str != "")
	{
		// save data
		Kategorie newEntry; 
		newEntry.name = str;
		Katalog.push_back(newEntry);


		//create new Kategory Box
		QHBoxLayout *layout_entry = new QHBoxLayout;
		layout_content->addLayout(layout_entry);

		QLineEdit *line_kat = new QLineEdit(ui);
		line_kat->setMinimumHeight(70);
		QWidget *question_widget = new QWidget(ui);
		FragenWidgets.push_back(question_widget);

		QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
		line_kat->setSizePolicy(sizePolicy);
		line_kat->setObjectName("kat" + QString::number(index + 1));
		line_kat->setText("new Kategorie");

		layout_entry->addWidget(line_kat, 2);
		layout_entry->addWidget(question_widget, 8);
		
		connect(line_kat, &QLineEdit::textChanged, this, &QQuiz::setKat);


		// create Question Box
		QGridLayout *layout_questions = new QGridLayout(FragenWidgets.at(index));
		QLineEdit *line_qu = new QLineEdit(FragenWidgets.at(index));
		layout_questions->addWidget(line_qu);
		line_qu->setObjectName(QString::number(index) + "," + QString::number(0));
		line_qu->setText("neue Frage");
		line_qu->setMinimumHeight(30);
		connect(line_qu, &QLineEdit::textChanged, this, &QQuiz::setQues);

	}
}

void QQuiz::setQues(const QString str)
{
	QObject *obj = QObject::sender();
	QLineEdit *thisLine = qobject_cast<QLineEdit *>(obj);
	QString senderobjName = thisLine->objectName();
	QStringList list = senderobjName.split(",");
	if (list.size() != 2) return;
	
	int katNr = list.at(0).toInt();
	int queNr = list.at(1).toInt();

	if (queNr < Katalog.at(katNr).Frage.size())
	{
		Katalog.at(katNr).Frage.at(queNr) = str;
	}
	else
	{
		// save data
		Katalog.at(katNr).Frage.push_back(str);

		//create new Box
		QLineEdit *line_qu = new QLineEdit(FragenWidgets.at(katNr));
		line_qu->setMinimumHeight(30);
		QGridLayout *layout_questions = qobject_cast<QGridLayout *> ( FragenWidgets.at(katNr)->layout());
		layout_questions->addWidget(line_qu, (queNr+1)/2, (queNr+1)%2);
		line_qu->setObjectName(QString::number(katNr) + "," + QString::number(queNr + 1));
		line_qu->setText("neue Frage");
		connect(line_qu, &QLineEdit::textChanged, this, &QQuiz::setQues);
		FragenWidgets.at(katNr)->layout()->activate();
	}

}

void QQuiz::deleteEmpty()
{
	//delete Question
	for (int i = 0; i < Katalog.size(); i++)
	{
		for (int j = 0; j < Katalog.at(i).Frage.size(); j++)
		{
			if (Katalog.at(i).Frage.at(j) == "")
			{
				Katalog.at(i).Frage.erase(Katalog.at(i).Frage.begin() + j);
			}
		}
	}

	//delete Category
	for (int i = 0; i < Katalog.size(); i++)
	{
		if (Katalog.at(i).name == "" || Katalog.at(i).Frage.size() == 0)
		{
			Katalog.erase(Katalog.begin() + i);
		}
	}
}

void QQuizs::deleteEmpty()
{
	for (int i = 0; i < quizList.size(); i++)
	{
		quizList.at(i)->deleteEmpty();
		if (quizList.at(i)->name == "")
		{
			quizList.erase(quizList.begin() + i);
		}
	}
}

void QQuizs::ui_view(QWidget * ui_)
{

	this->deleteEmpty();
	lastButton = NULL;
	ClearWidget(ui_);

	QVBoxLayout *mainlayout = new QVBoxLayout(ui_);

	ui_buttons = new QWidget(ui_);
	ui_content = new QWidget(ui_);

	mainlayout->addWidget(ui_buttons, 1);
	mainlayout->addWidget(ui_content, 9);

	QVBoxLayout *layout = new QVBoxLayout(ui_buttons);
	layout->setAlignment(Qt::AlignTop);

	layout_team = new QHBoxLayout;
	for (int i = 0; i <= this->quizList.size(); i++)
	{
		QPushButton *button_team = new QPushButton;
		layout_team->addWidget(button_team);
		button_team->setObjectName("button" + QString::number(i));

		if (i < this->quizList.size())
		{
			button_team->setText(quizList.at(i)->name);
			connect(quizList.at(i), &QQuiz::nameChange, button_team, &QPushButton::setText);
		}
		else
			button_team->setText("new Quiz");

		connect(button_team, &QPushButton::clicked, this, &QQuizs::editQuiz);
	}
	layout->addLayout(layout_team);
}

void QQuizs::editQuiz()
{
	QObject *obj = QObject::sender();
	thisButton = qobject_cast<QPushButton *>(obj);
	if (lastButton) lastButton->setStyleSheet("");
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

	if (index < quizList.size())
	{
		quizList.at(index)->deleteEmpty();
		quizList.at(index)->ui_view(ui_content);
	}
	else if (index == quizList.size())
	{

		QQuiz *newQuiz = new QQuiz();
		newQuiz->name = "new Quiz";
		
		quizList.push_back(newQuiz);
		newQuiz->ui_view(ui_content);

		QPushButton *button_quiz = new QPushButton;
		layout_team->addWidget(button_quiz);
		button_quiz->setObjectName("button" + QString::number(index + 1));
		button_quiz->setText("new Quiz");

		connect(newQuiz, &QQuiz::nameChange, thisButton, &QPushButton::setText);
		connect(button_quiz, &QPushButton::clicked, this, &QQuizs::editQuiz);
	}
	lastButton = thisButton;
}

void QQuizs::saveToXml()
{
	deleteEmpty();

	QFile file("Resources/Quiz.xml");
	file.open(QIODevice::WriteOnly);

	if (!file.isOpen()) { qDebug("Cannot open File! (quiz)"); return; }
	qDebug("File opened! (quiz)");

	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement("Quizs");
	xmlWriter.writeAttribute("NumberOfQuiz", QString::number(this->quizList.size()));

	for (int i = 0; i < this->quizList.size(); i++)
	{
		xmlWriter.writeStartElement("Quiz");
		xmlWriter.writeAttribute("Quizname", this->quizList.at(i)->name);
		xmlWriter.writeAttribute("NumberOfKat", QString::number(this->quizList.at(i)->Katalog.size()));
		for (int j = 0; j < this->quizList.at(i)->Katalog.size(); j++)
		{
			xmlWriter.writeStartElement("Kategorie");
			xmlWriter.writeAttribute("Kategoriename", this->quizList.at(i)->Katalog.at(j).name);
			xmlWriter.writeAttribute("AnzahlKategorien", QString::number(this->quizList.at(i)->Katalog.at(j).Frage.size() ) );
			for (int k = 0; k < this->quizList.at(i)->Katalog.size(); k++)
			{
				xmlWriter.writeTextElement("Frage", this->quizList.at(i)->Katalog.at(j).Frage.at(k));
			}
			xmlWriter.writeEndElement();
		}
		xmlWriter.writeEndElement();
	}
	xmlWriter.writeEndElement();
}

void QQuizs::readFromXml()
{
	QXmlStreamReader Rxml;

	QFile file("Resources/Quiz.xml");
	file.open(QFile::ReadOnly | QFile::Text);
	if (!file.isOpen()) { qDebug("Cannot open File!"); return; }

	Rxml.setDevice(&file);
	Rxml.readNext();

	QQuiz *newQuiz;

	while (!Rxml.atEnd())	//Quize einelesen
	{
		//Suche nach start Elementen
		if (Rxml.isStartElement())
		{
			//TeamS Element enthält name des Teams
			if (Rxml.name() == "Quizs")
			{
				int NumberOfQuiz = Rxml.attributes().value("NumberOfQuiz").toInt();
			}

			//Team enthält Namen der TeamMember
			if (Rxml.name() == "Quiz")
			{
				//lese header
				QString quizname = Rxml.attributes().value("Quizname").toString();
				int numberOfKat = Rxml.attributes().value("NumberOfKat").toInt();

				newQuiz = new QQuiz();
				newQuiz->name = quizname;

				//lese TextAttribute
				while (!Rxml.atEnd())	// Kategorien einlesen
				{
					Rxml.readNext();
					//keine weitern Elemente vorhanden
					if (Rxml.isEndElement()) break;

					//Kategorie Element gefunden
					if (Rxml.isStartElement())
					{
						// Spieler einlesen
						QString kategoriename = Rxml.attributes().value("Kategoriename").toString();
						int anzahlKategorien = Rxml.attributes().value("AnzahlKategorien").toInt();
						QQuiz::Kategorie newKat;
						newKat.name = kategoriename;

						while (!Rxml.atEnd())	//Fragen einlesen
						{
							Rxml.readNext();

							//keine weitern Elemente vorhanden
							if (Rxml.isEndElement()) break;

							//Kategorie Element gefunden
							if (Rxml.isStartElement())
							{
								QString frage = Rxml.readElementText();
								newKat.Frage.push_back(frage);
							}
						}
						newQuiz->Katalog.push_back(newKat);
					}
				}
				this->quizList.push_back(newQuiz);
			}
		}
		Rxml.readNext();
	}
	file.close();
}