/********************************************************************************
** Form generated from reading UI file 'quizverwalter.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZVERWALTER_H
#define UI_QUIZVERWALTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuizVerwalterClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonTeams;
    QPushButton *pushButtonQuiz;
    QPushButton *pushButtonData;
    QPushButton *pushButtonSave;
    QSpacerItem *verticalSpacer;
    QWidget *contentWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QuizVerwalterClass)
    {
        if (QuizVerwalterClass->objectName().isEmpty())
            QuizVerwalterClass->setObjectName(QStringLiteral("QuizVerwalterClass"));
        QuizVerwalterClass->resize(600, 400);
        centralWidget = new QWidget(QuizVerwalterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButtonTeams = new QPushButton(widget);
        pushButtonTeams->setObjectName(QStringLiteral("pushButtonTeams"));

        verticalLayout->addWidget(pushButtonTeams);

        pushButtonQuiz = new QPushButton(widget);
        pushButtonQuiz->setObjectName(QStringLiteral("pushButtonQuiz"));

        verticalLayout->addWidget(pushButtonQuiz);

        pushButtonData = new QPushButton(widget);
        pushButtonData->setObjectName(QStringLiteral("pushButtonData"));

        verticalLayout->addWidget(pushButtonData);

        pushButtonSave = new QPushButton(widget);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));

        verticalLayout->addWidget(pushButtonSave);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget);

        contentWidget = new QWidget(centralWidget);
        contentWidget->setObjectName(QStringLiteral("contentWidget"));

        horizontalLayout->addWidget(contentWidget);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 9);
        QuizVerwalterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QuizVerwalterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        QuizVerwalterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QuizVerwalterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QuizVerwalterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QuizVerwalterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QuizVerwalterClass->setStatusBar(statusBar);

        retranslateUi(QuizVerwalterClass);

        QMetaObject::connectSlotsByName(QuizVerwalterClass);
    } // setupUi

    void retranslateUi(QMainWindow *QuizVerwalterClass)
    {
        QuizVerwalterClass->setWindowTitle(QApplication::translate("QuizVerwalterClass", "QuizVerwalter", 0));
        pushButtonTeams->setText(QApplication::translate("QuizVerwalterClass", "Teams", 0));
        pushButtonQuiz->setText(QApplication::translate("QuizVerwalterClass", "Quiz", 0));
        pushButtonData->setText(QApplication::translate("QuizVerwalterClass", "Data", 0));
        pushButtonSave->setText(QApplication::translate("QuizVerwalterClass", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class QuizVerwalterClass: public Ui_QuizVerwalterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZVERWALTER_H
