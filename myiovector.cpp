#include "myiovector.h"

#include <QObject>
#include <QWidget>
#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QLineEdit>
#include <QLabel>

#include <vector>

#include <QString>
#include <QList>
#include <QDebug>


//TODO put QWidget(ui) in Scroll area?

MyIoVector::~MyIoVector()
{

}

/// <summary>
/// Initializes a new instance of the <see cref="MyIoVector"/> class.
/// </summary>
/// <param name="target_ui">Widget where the we are going to place the ui.</param>
/// <param name="target_data">Data to which we will link the input</param>
/// <param name="name_">(if needed) an aditional name for the data set</param>
/// <param name="lables_">(if needed) labels for the input values. Needs to be the same size as the data vector.</param>
/// <param name="clearWidgetOnInit">if set to <c>true</c> [clear widget on initialize].</param>
MyIoVector::MyIoVector(QWidget *target_ui, std::vector<QString> *target_data, QString *name_, std::vector<QString> *lables_, bool clearWidgetOnInit )
	:	QObject(target_ui),	ui(target_ui),	name(name_), labels(lables_), data(target_data)
{
	if (clearWidgetOnInit)clear();
	initLayouts();
	if (name) initName();
	initVector();
}

void MyIoVector::clear()
{
	for (auto it = ui->children().begin(); it != ui->children().end(); ++it)
	{
		if (*it != this)delete *it;
	}
}

void MyIoVector::initLayouts()
{
	if (!ui_layout) ui_layout = new QVBoxLayout(ui);
	if (!name_layout) name_layout = new QHBoxLayout;
	if (!entry_layout) entry_layout = new QGridLayout;

	ui_layout->addLayout(name_layout);
	ui_layout->addLayout(entry_layout);

	ui_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	name_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	entry_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

void MyIoVector::initName()
{
	name_edit = new QLineEdit(ui);
	QLabel * label = new QLabel(ui);
	label->setText("Name:");
	labelList.push_back(label);

	connect(name_edit, &QLineEdit::textEdited, this, &MyIoVector::setName);

	name_layout->addWidget(label);
	name_layout->addWidget(name_edit);
}

/// <summary>
/// Sets the name.
/// name: (if needed) an aditional name for the data set
/// </summary>
/// <param name="str">The string.</param>
void MyIoVector::setName(QString str)
{
	if (!name_edit) {
		name_edit->setReadOnly(true);
		name_edit = new QLineEdit(ui);
		name_layout->addWidget(name_edit);
	}
	name_edit->setText(str);

	if (name) *name = str;
}

void MyIoVector::initVector()
{
	Q_ASSERT(data);

	for (size_t i = 0; i <= data->size(); i++)
	{
		QHBoxLayout *local_layout = new QHBoxLayout;
		local_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		entry_layout->addLayout(local_layout, i/ numberCols, i%numberCols);

		// Generate Labels
		if (labels) // labels should be set
		{
			QLabel *entry_label = new QLabel(ui);
			local_layout->addWidget(entry_label);
			if ((i < data->size()) && //label name still existing
				(labels->size() == data->size())) { //valid input I (enough names given)
				entry_label->setText(labels->at(i));
			}
			else if (labels->size() == 1) { //valid input II (always the same name)
				entry_label->setText(labels->at(0));
			}
		}


		// Generate lineEdits
		QLineEdit *entry_lineedit = new QLineEdit(ui);
		
		if (i < data->size()) {
			entry_lineedit->setText(data->at(i));
		}
		local_layout->addWidget(entry_lineedit);
		entry_lineedit->setProperty("id" , i);

		connect(entry_lineedit, &QLineEdit::textChanged, this, &MyIoVector::setValue);
	}
}

/// <summary>
/// Sets the a value of the data vector.
/// </summary>
/// <param name="str">The string.</param>
void MyIoVector::setValue(const QString str)
{
	QLineEdit *thisButton = qobject_cast<QLineEdit *>(QObject::sender());

	Q_ASSERT(thisButton);
	Q_CHECK_PTR(thisButton);
	int i = thisButton->property("id").toInt();
	
	if (i < data->size() ) // change data
	{
		data->at(i)=str;
	}

	else if (i == data->size()) // add new data
	{
		data->push_back(str);


		// layout
		QHBoxLayout *local_layout = new QHBoxLayout;
		local_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		entry_layout->addLayout(local_layout, (i + 1) / numberCols, (i + 1) % numberCols);


		//add label
		if (labels) // labels should be set
		{
			QLabel *entry_label = new QLabel(ui);
			local_layout->addWidget(entry_label);
			if (labels->size() == 1) { //valid input II (always the same name)
				entry_label->setText(labels->at(0));
			}
		}


		//add LineEdit
		QLineEdit *entry_lineedit = new QLineEdit(ui);
		local_layout->addWidget(entry_lineedit);
		entry_lineedit->setProperty("id", i + 1);
		connect(entry_lineedit, &QLineEdit::textChanged, this, &MyIoVector::setValue);
	}
}
