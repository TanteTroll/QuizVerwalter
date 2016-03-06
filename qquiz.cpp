#include "qquiz.h"
#include <vector>

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

//Layout
#include <QVBoxLayout>
#include <QHBoxLayout>

//xml
#include <QtXml>
#include <QFile>
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

QQuiz::~QQuiz()
{

}

void QQuiz::setName(const QString str)
{
	this->name = str;
	emit nameChange(str);
}

void QQuiz::ui_view(QWidget * ui_)
{
	this->ui = ui_;
	ClearWidget(ui);
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
	layout_content = new QVBoxLayout;
	layout->addLayout(layout_content);

	for (int i = 0; i <= this->Katalog.size(); i++)
	{
		QHBoxLayout *layout_entry = new QHBoxLayout;
		layout_content->addLayout(layout_entry);

		QLineEdit *line_kat = new QLineEdit(ui);
		QWidget *question_widget = new QWidget(ui);	//TODO Scrollarea daraus machen
		//TODO add to a List
		question_widget->setMinimumSize(50, 50);
		QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
		line_kat->setSizePolicy(sizePolicy);
		layout_entry->addWidget(line_kat,2);
		layout_entry->addWidget(question_widget,8);
		
		line_kat->setObjectName("kat" + QString::number(i) );
		
		if (i < this->Katalog.size())
		{
			line_kat->setText(this->Katalog.at(i).name);

			for (int j = 0; j <= this->Katalog.at(i).Frage.size(); j++)
			{
				QGridLayout *layout_questions = new QGridLayout;
				layout_content->addLayout(layout_questions);

				QLineEdit *line_qu = new QLineEdit(question_widget);
				layout_questions->addWidget(line_qu);
				line_kat->setObjectName(QString::number(i) + "," + QString::number(j));
				if (i < this->Katalog.at(i).Frage.size())
				{
					line_kat->setText(this->Katalog.at(i).Frage.at(j));
				}
				else
					line_kat->setText("neue Frage");

				connect(line_kat, &QLineEdit::textChanged, this, &QQuiz::setQues);
			}
		}
		else
			line_kat->setText("neue Kategorie");

		connect(line_kat, &QLineEdit::textChanged, this, &QQuiz::setKat);


		// Question Widget
		
		
	}
	
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
		Kategorie newEntry; 
		newEntry.name = str;

		Katalog.push_back(newEntry);

		QHBoxLayout *layout_entry = new QHBoxLayout;
		layout_content->addLayout(layout_entry);

		QLineEdit *line_kat = new QLineEdit(ui);
		QWidget *question_widget = new QWidget(ui);
		question_widget->setMinimumSize(50, 50);
		QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
		line_kat->setSizePolicy(sizePolicy);
		layout_entry->addWidget(line_kat, 2);
		layout_entry->addWidget(question_widget, 8);

		line_kat->setObjectName("kat" + QString::number(index + 1));
		line_kat->setText("new Kategorie");


		connect(line_kat, &QLineEdit::textChanged, this, &QQuiz::setKat);
	}
}//TODO get Widget from list and put boxes inside
//TODO Question Boxes

void QQuiz::setQues(const QString str)
{
	qDebug() << str;
	//TODO obviously
}
