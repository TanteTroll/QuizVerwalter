#include "qquiz.h"
#include "myiovector2d.h"

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

void QQuiz::writeToXml(QXmlStreamWriter * xmlWriter)
{
	xmlWriter->writeStartElement("Quiz");
	xmlWriter->writeAttribute("Quizname", name);

	xmlWriter->writeAttribute("NumberOfKat", QString::number(kategorieNamen.size() ) );
	for (int i = 0; i < kategorieNamen.size(); i++)
	{
		xmlWriter->writeStartElement("Kategorie");
		xmlWriter->writeAttribute("Kategoriename", kategorieNamen.at(i) );
		xmlWriter->writeAttribute("AnzahlKategorien", QString::number(fragen.at(i).size() ));
		for (int j = 0; j < fragen.at(i).size(); j++)
		{
			xmlWriter->writeTextElement("Frage", fragen.at(i).at(j) );
		}
		xmlWriter->writeEndElement();
	}
	xmlWriter->writeEndElement();
}

void QQuiz::ui_view(QWidget * ui_)
{
	ClearWidget(ui_);
	
	ui = ui_;

	// prepare ui
	QVBoxLayout *layout = new QVBoxLayout(ui);
	layout->setAlignment(Qt::AlignTop);

	MyIoVector2D* widget = new MyIoVector2D(ui, &kategorieNamen, &fragen);
	layout->addWidget(widget);
}


void QQuiz::deleteEmpty()
{

}

void QQuizs::deleteEmpty()
{
	for (int i = 0; i < this->quizList.size(); i++)
	{
		quizList.at(i)->deleteEmpty();
	}
}

void QQuizs::ui_view(QWidget * ui_)
{
	deleteEmpty();
	ClearWidget(ui_);

	ui = ui_;

	layout = new QVBoxLayout(ui);
	tabs = new QTabWidget(ui);
	layout->addWidget(tabs);
	tabs->setTabShape(QTabWidget::Rounded);
	tabs->setTabPosition(QTabWidget::North);
	connect(tabs, &QTabWidget::tabBarClicked, this, &QQuizs::tabClicked);

	for (auto i = 0; i <= quizList.size(); i++)
	{
		QWidget * page;
		QString label;
		if (i < quizList.size()) {
			label = quizList.at(i)->name;
			page = new QWidget(ui); 
			quizList.at(i)->ui_view(page);
		}
		else {
			page = new QWidget(ui);
			label = "+";
		}
		tabs->insertTab(i, page, label);
		tabList.push_back(page);
	}
}

void QQuizs::tabClicked(const int i)
{
	qDebug() << "clicked "<<i<< quizList.size();
	if (i == quizList.size())newTab();
}

void QQuizs::newTab()
{
	qDebug() << "added";
	//save new data
	QQuiz *newQuiz = new QQuiz(ui);
	quizList.push_back(newQuiz);

	//create new Tab
	QWidget * page = new QWidget(ui);
	tabs->insertTab(quizList.size(), page, "+");
	tabList.push_back(page);

	//change old Tab
	tabs->setTabText(quizList.size() - 1, quizList.at(quizList.size() - 1)->name);//set Tab Name
	quizList.at(quizList.size() - 1)->ui_view(tabList.at(quizList.size() - 1)); //activate Tab widget

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
		quizList.at(i)->writeToXml(&xmlWriter);
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
			//QuizS Element enthält name des Teams
			if (Rxml.name() == "Quizs")
			{
				int NumberOfQuiz = Rxml.attributes().value("NumberOfQuiz").toInt();
			}

			//Quiz enthält Namen der TeamMember
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
						
						newQuiz->kategorieNamen.push_back(kategoriename);

						std::vector<QString> kategFrage;
						while (!Rxml.atEnd())	//Fragen einlesen
						{
							Rxml.readNext();

							//keine weitern Elemente vorhanden
							if (Rxml.isEndElement()) break;

							//Kategorie Element gefunden
							
							if (Rxml.isStartElement())
							{
								QString frage = Rxml.readElementText();
								kategFrage.push_back(frage);
							}
						}
						newQuiz->fragen.push_back(kategFrage);
					}
				}
				this->quizList.push_back(newQuiz);
			}
		}
		Rxml.readNext();
	}
	file.close();
}