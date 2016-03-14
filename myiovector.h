#ifndef MYIOVECTOR_H
#define MYIOVECTOR_H
#include "myio.h"


/// <summary>
/// Class to display a vector
/// </summary>
/// <seealso cref="MyIo" />
class MyIoVector : public MyIo
{
	Q_OBJECT

public:
	~MyIoVector();
	MyIoVector(QWidget *target_ui, std::vector<QString> *target_data, std::vector<QString> *lables = NULL, QString *name_ = NULL, uint8_t flags = 0);
	MyIoVector(QWidget *target_ui, std::vector<QString> *target_data, QString lables , QString *name_ = NULL, uint8_t flags = 0);

public slots:

	void setValue(const QString str);



private:
	std::vector<QString> *data = NULL;
	std::vector<QString> *labels = NULL;
	

	void initVector();
	
};

#endif // MYIOVECTOR_H
