#ifndef QQUIZ_H
#define QQUIZ_H

// C++
#include <vector>

// core qt
#include <QObject>
#include <QWidget>
#include <QString>
#include <QList>

// widgets
#include <QTabWidget>
#include <QScrollArea>
#include <QLayout>

//xml
#include <QtXml>


class QQuiz : public QObject
{
	Q_OBJECT

public:
	static std::vector<QString> badNames; //TODO safe in xml
	
	QQuiz(QObject *parent = 0);
	~QQuiz();

	std::vector<QString> kategorieNamen;
	std::vector<std::vector<QString>> fragen; 
	// auﬂen : Kategorie Nummer
	// innen: Fragen

	QString name ="new";

	void writeToXml(QXmlStreamWriter *xmlWriter);
	void ui_view(QWidget *ui_);
	void deleteEmpty();
	
public slots:
	void setName(const QString str);
	

signals:
	void nameChange(QString str);

private:
	QWidget * ui = NULL;
	QWidget *dynamic = NULL;
	QScrollArea *area = NULL;
	QVBoxLayout *layout_content = NULL;
	

	
};

class QQuizs : public QObject
{
	Q_OBJECT
public:
	QQuizs(QObject *parent = 0);

	QList<QQuiz*> quizList;


	void readFromXml();
	void deleteEmpty();
	void ui_view(QWidget *ui);
	


public slots:
	void tabClicked(const int i);
	void saveToXml();

private:
	QWidget * ui = NULL;
	QVBoxLayout *layout = NULL;
	QTabWidget *tabs = NULL;

	void newTab();
	QList < QWidget* > tabList;
};

#endif // QQUIZ_H
