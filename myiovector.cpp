#include "myiovector.h"

//TODO put QWidget(ui) in Scroll area?

MyIoVector::~MyIoVector()
{

}

/// <summary>
/// Initializes a new instance of the <see cref="MyIoVector"/> class.
/// </summary>
/// <param name="target_ui">Widget where the we are going to place the ui.</param>
/// <param name="target_data">Stored Data</param>
/// <param name="name_">(if needed) an aditional name for the data set</param>
/// <param name="lables_">(if needed) labels for the input values. Needs to be the same size as the data vector.</param>
/// <param name="clearWidgetOnInit">if set to <c>true</c> [clear widget on initialize].</param>
MyIoVector::MyIoVector(QWidget *parent, std::vector<QString> *target_data, std::vector<QString> *lables_,QString *name_, uint8_t flags )
	: MyIo(parent, name_, flags), data(target_data), labels(lables_)
{
	initVector();
}
MyIoVector::MyIoVector(QWidget *target_ui, std::vector<QString> *target_data, QString lables_, QString *name_, uint8_t flags)
	: MyIo(target_ui, name_, flags), data(target_data)
{
	labels = new std::vector<QString>;
	labels->push_back(lables_);

	initVector();
}

void MyIoVector::initVector()
{
	if (!data) data = new std::vector<QString>;
	Q_ASSERT(data);

	for (size_t i = 0; i <= data->size(); i++)
	{
		QHBoxLayout *local_layout = new QHBoxLayout;
		local_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
		entry_layout->addLayout(local_layout, i/ numberCols, i%numberCols);

		// Generate Labels
		if (labels) // labels should be set
		{
			QLabel *entry_label = new QLabel(this);
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
		QLineEdit *entry_lineedit = new QLineEdit(this);
		
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
			QLabel *entry_label = new QLabel(this);
			local_layout->addWidget(entry_label);
			if (labels->size() == 1) { //valid input II (always the same name)
				entry_label->setText(labels->at(0));
			}
		}


		//add LineEdit
		QLineEdit *entry_lineedit = new QLineEdit(this);
		local_layout->addWidget(entry_lineedit);
		entry_lineedit->setProperty("id", i + 1);
		connect(entry_lineedit, &QLineEdit::textChanged, this, &MyIoVector::setValue);
	}
}
