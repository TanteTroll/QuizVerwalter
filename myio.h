#ifndef MYIO_H
#define MYIO_H

#include <QObject>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>

#include <QScrollArea>

#include <bitset>

/// <summary>
/// Base class for my Widget container
/// </summary>
/// <seealso cref="QWidget" />
class MyIo : public QWidget
{
	Q_OBJECT

public:
	const uint8_t todo = 0x01; //TODO 

	uint8_t flags = 0;

	MyIo(QWidget *parent, QString *target_name = NULL, uint8_t flags_ = 0);
	MyIo(QWidget *parent, QString  target_name);
	
	void setName(QString str);

protected:
	int numberCols = 2;

	QVBoxLayout *ui_layout = NULL;
	QGridLayout *entry_layout = NULL;
	QVector<QLayout*> localLayout;

	void clear();
	void initLayouts();
	void initName();
	

private:
	QLineEdit *name_edit = NULL;
	QHBoxLayout *name_layout = NULL;
	QString *name = NULL;
	QScrollArea *area = NULL;
};

#endif // MYIO_H
