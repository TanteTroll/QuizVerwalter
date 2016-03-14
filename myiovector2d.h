#ifndef MYIOVECTOR2D_H
#define MYIOVECTOR2D_H

#include "myio.h"

class MyIoVector2D : public MyIo
{
	Q_OBJECT
	
public:
	MyIoVector2D(QWidget *target_ui, std::vector<QString> *target_data_master, std::vector<std::vector<QString>*> *target_data_slave,
		QString *name_ = NULL, uint8_t flags = 0);
	
public slots:
	void setValue(const QString str);

private:
	std::vector<QString> *data_master = NULL;
	std::vector<std::vector<QString>*> *data_slave = NULL;

	void initVector();
	
	
};

#endif // MYIOVECTOR2D_H
