#include "myiovector2d.h"
#include "myiovector.h"

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QDebug>

MyIoVector2D::MyIoVector2D(QWidget *target_ui, std::vector<QString> *target_data_master, std::vector<std::vector<QString>> *target_data_slave,
	QString *name_, uint8_t flags)
	: MyIo(target_ui, name_, flags),  data_master(target_data_master), data_slave(target_data_slave)
{
	numberCols = 1;
	initVector();
}



void MyIoVector2D::initVector()
{
	Q_ASSERT(data_master); 
	Q_ASSERT(data_slave);

	for (size_t i = 0; i <= data_master->size(); i++)
	{
		QHBoxLayout *local_layout = new QHBoxLayout;
		local_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		entry_layout->addLayout(local_layout, i / numberCols, i % numberCols);

		QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred); //Widget expands over full size
		QLineEdit *line = new QLineEdit(this);
		line->setSizePolicy(sizePolicy);
		line->setProperty("id", i);
		line->setMinimumHeight(60);
		
		local_layout->addWidget(line, 2);

		if (i < data_master->size()) {
			MyIoVector *vect = new MyIoVector(this, &data_slave->at(i));
			local_layout->addWidget(vect, 8);
			line->setText(data_master->at(i));
		}
		localLayout.push_back(local_layout);
		
		connect(line, &QLineEdit::textChanged, this, &MyIoVector2D::setValue);
	}
	
}



void MyIoVector2D::setValue(const QString str)
{
	QLineEdit *thisButton = qobject_cast<QLineEdit *>(QObject::sender());

	Q_ASSERT(thisButton);
	Q_CHECK_PTR(thisButton);

	int i = thisButton->property("id").toInt();
	if (i < data_master->size()) // change data
	{
		data_master->at(i) = str;
	}

	else if (i == data_master->size()) // add new data
	{
		data_master->push_back(str);


		// layout
		QHBoxLayout *local_layout = new QHBoxLayout;
		local_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		entry_layout->addLayout(local_layout, (i + 1) / numberCols, (i + 1) % numberCols);

		//add LineEdit
		QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
		QLineEdit *line = new QLineEdit(this);
		line->setSizePolicy(sizePolicy);
		line->setProperty("id", i + 1);
		line->setMinimumHeight(60);
		local_layout->addWidget(line, 2);

		// add Vector
		std::vector<QString> neu = { "" };
		data_slave->push_back(neu);
		MyIoVector *vect = new MyIoVector(this, &data_slave->at(i));
		qobject_cast<QHBoxLayout *>(localLayout.at(i))->addWidget(vect, 8);


		localLayout.push_back(local_layout);
		connect(line, &QLineEdit::textChanged, this, &MyIoVector2D::setValue);
	}
}