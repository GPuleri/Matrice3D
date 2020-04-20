/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Nuovo;
    QPushButton *Apri;
    QPushButton *Salva;
    QPushButton *Salva_con_nome;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *Bold;
    QToolButton *Italic;
    QToolButton *Underline;
    QComboBox *Dimensione;
    QTextEdit *textEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(932, 569);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Nuovo = new QPushButton(centralWidget);
        Nuovo->setObjectName(QStringLiteral("Nuovo"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Nuovo->sizePolicy().hasHeightForWidth());
        Nuovo->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(Nuovo);

        Apri = new QPushButton(centralWidget);
        Apri->setObjectName(QStringLiteral("Apri"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Apri->sizePolicy().hasHeightForWidth());
        Apri->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(Apri);

        Salva = new QPushButton(centralWidget);
        Salva->setObjectName(QStringLiteral("Salva"));
        sizePolicy1.setHeightForWidth(Salva->sizePolicy().hasHeightForWidth());
        Salva->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(Salva);

        Salva_con_nome = new QPushButton(centralWidget);
        Salva_con_nome->setObjectName(QStringLiteral("Salva_con_nome"));
        sizePolicy1.setHeightForWidth(Salva_con_nome->sizePolicy().hasHeightForWidth());
        Salva_con_nome->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(Salva_con_nome);


        horizontalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        Bold = new QToolButton(centralWidget);
        Bold->setObjectName(QStringLiteral("Bold"));
        sizePolicy1.setHeightForWidth(Bold->sizePolicy().hasHeightForWidth());
        Bold->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        Bold->setFont(font);
        Bold->setCheckable(true);

        horizontalLayout_3->addWidget(Bold);

        Italic = new QToolButton(centralWidget);
        Italic->setObjectName(QStringLiteral("Italic"));
        sizePolicy1.setHeightForWidth(Italic->sizePolicy().hasHeightForWidth());
        Italic->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setItalic(true);
        Italic->setFont(font1);
        Italic->setCheckable(true);

        horizontalLayout_3->addWidget(Italic);

        Underline = new QToolButton(centralWidget);
        Underline->setObjectName(QStringLiteral("Underline"));
        sizePolicy1.setHeightForWidth(Underline->sizePolicy().hasHeightForWidth());
        Underline->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setUnderline(true);
        Underline->setFont(font2);
        Underline->setCheckable(true);

        horizontalLayout_3->addWidget(Underline);


        horizontalLayout->addLayout(horizontalLayout_3);

        Dimensione = new QComboBox(centralWidget);
        Dimensione->setObjectName(QStringLiteral("Dimensione"));
        sizePolicy1.setHeightForWidth(Dimensione->sizePolicy().hasHeightForWidth());
        Dimensione->setSizePolicy(sizePolicy1);
        Dimensione->setEditable(false);

        horizontalLayout->addWidget(Dimensione, 0, Qt::AlignLeft);


        verticalLayout->addLayout(horizontalLayout);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(true);
        QFont font3;
        font3.setPointSize(12);
        textEdit->setFont(font3);

        verticalLayout->addWidget(textEdit);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        Dimensione->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Nuovo->setText(QApplication::translate("MainWindow", "Nuovo", Q_NULLPTR));
        Apri->setText(QApplication::translate("MainWindow", "Apri", Q_NULLPTR));
        Salva->setText(QApplication::translate("MainWindow", "Salva", Q_NULLPTR));
        Salva_con_nome->setText(QApplication::translate("MainWindow", "Salva con nome..", Q_NULLPTR));
        Bold->setText(QApplication::translate("MainWindow", "G", Q_NULLPTR));
        Italic->setText(QApplication::translate("MainWindow", "C", Q_NULLPTR));
        Underline->setText(QApplication::translate("MainWindow", "S", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
