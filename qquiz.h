#ifndef QQUIZ_H
#define QQUIZ_H

#include <QObject>
#include <vector>
#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QPushButton>
#include <QList>
#include <QScrollArea>

class QQuiz : public QObject
{
	Q_OBJECT

public:
	static std::vector<QString> badNames; //TODO safe in xml
	struct Kategorie
	{
		QString name;
		std::vector<QString> Frage;
	};



	QQuiz(QObject *parent = 0);
	~QQuiz();

	std::vector<Kategorie> Katalog;
	QString name ="new";

	void ui_view(QWidget *ui_);
	void deleteEmpty();

public slots:
	void setName(const QString str);
	void setKat(const QString str);
	void setQues(const QString str);
	

signals:
	void nameChange(QString str);

private:
	QWidget * ui;//QWidget oder QScrollArea
	QWidget *dynamic;
	QScrollArea *area;
	QVBoxLayout *layout_content = NULL;
	
	QList < QWidget* > FragenWidgets;
	
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
	void editQuiz();
	void saveToXml();

private:
	QWidget * ui_buttons;
	QWidget * ui_content;
	QHBoxLayout *layout_team;

	QPushButton *thisButton;
	QPushButton *lastButton = NULL;

};

#endif // QQUIZ_H
