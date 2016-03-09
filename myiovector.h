#ifndef MYIOVECTOR_H
#define MYIOVECTOR_H

#include <QObject>
#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLineEdit>
#include <QLabel>

#include <vector>

#include <QString>
#include <QList>

class MyIoVector : public QObject
{
	Q_OBJECT

public:
	~MyIoVector();
	MyIoVector(QWidget *target_ui,
		std::vector<QString> *target_data,
		QString *name_ = NULL,
		std::vector<QString> *lables = NULL,
		bool clearWidgetOnInit = true);

public slots:

	void setName( QString str);
	void setValue(const QString str);



private:
	QWidget *ui = NULL;
	QString *name = NULL;
	std::vector<QString> *data = NULL;
	std::vector<QString> *labels = NULL;
	int numberCols = 2;

	QVBoxLayout *ui_layout = NULL;
	QHBoxLayout *name_layout = NULL;
	QGridLayout *entry_layout = NULL;

	QLineEdit *name_edit = NULL;

	QList<QLabel*> labelList;

	void clear();
	void initLayouts();
	void initName();
	void initVector();
	
};

#endif // MYIOVECTOR_H
