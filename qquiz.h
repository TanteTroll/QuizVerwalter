#ifndef QQUIZ_H
#define QQUIZ_H

#include <QObject>
#include <vector>
#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QPushButton>
#include <QList>

class QQuiz : public QObject
{
	Q_OBJECT
	struct Kategorie
	{
		QString name;
		std::vector<QString> Frage;
	};

public: //TODO delete empty mambers

	QQuiz(QObject *parent = 0);
	~QQuiz();

	std::vector<Kategorie> Katalog;
	QString name ="new";

	void ui_view(QWidget *ui_);

public slots:
	void setName(const QString str);
	void setKat(const QString str);
	void setQues(const QString str);

signals:
	void nameChange(QString str);

private:
	QWidget * ui;
	QVBoxLayout *layout_content = NULL;
	
};

#endif // QQUIZ_H
