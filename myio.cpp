#include "myio.h"
#include <QWidget>


/// <summary>
/// Initializes a new instance of the <see cref="MyIo"/> class.
/// </summary>
/// <param name="target_ui">Widget in which the new Widget will be build.</param>
/// <param name="target_name">Add a editable Nameline to the Widget</param>
/// <param name="clearWidgetOnInit">if set to <c>true</c> the widget will be emptied before generating the new widget</param>
/// <returns></returns>
MyIo::MyIo(QWidget *parent, QString *target_name, uint8_t flags_)
	: QWidget(parent), name (target_name), flags(flags_)
{
	initLayouts();
	if (name) initName();
}

/// <summary>
/// Initializes a new instance of the <see cref="MyIo"/> class.
/// </summary>
/// <param name="target_ui">Widget in which the new Widget will be build.</param>
/// <param name="target_name">Add a Nameline to the Widget</param>
/// <param name="clearWidgetOnInit">if set to <c>true</c> the widget will be emptied before generating the new widget</param>
MyIo::MyIo(QWidget *target_ui, QString target_name)
	: QWidget(target_ui)
{
	initLayouts();
	setName(target_name);
}


void MyIo::initLayouts()
{
	if (!ui_layout) ui_layout = new QVBoxLayout(this);
	if (!name_layout) name_layout = new QHBoxLayout;
	if (!entry_layout) entry_layout = new QGridLayout;

	ui_layout->addLayout(name_layout);
	ui_layout->addLayout(entry_layout);

	ui_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	name_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	entry_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	entry_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	name_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	ui_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
}

void MyIo::clear()
{
	for (auto it = this->children().begin(); it != this->children().end(); ++it)
	{
		if (*it != this)delete *it;
	}
}

void MyIo::initName()
{
	name_edit = new QLineEdit(this);
	QLabel * label = new QLabel(this);
	label->setText("Name:");
	
	connect(name_edit, &QLineEdit::textEdited, this, &MyIo::setName);

	name_layout->addWidget(label);
	name_layout->addWidget(name_edit);
}

/// <summary>
/// Sets the name.
/// name: (if needed) an aditional name for the data set
/// </summary>
/// <param name="str">The string.</param>
void MyIo::setName(QString str)
{
	if (!name_edit) {
		name_edit->setReadOnly(true);
		name_edit = new QLineEdit(this);
		name_layout->addWidget(name_edit);
	}
	name_edit->setText(str);

	if (name) *name = str;
}
