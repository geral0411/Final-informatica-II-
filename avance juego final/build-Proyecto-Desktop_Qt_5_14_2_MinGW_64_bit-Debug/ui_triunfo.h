/********************************************************************************
** Form generated from reading UI file 'triunfo.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRIUNFO_H
#define UI_TRIUNFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Triunfo
{
public:
    QPushButton *iniciar;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *Triunfo)
    {
        if (Triunfo->objectName().isEmpty())
            Triunfo->setObjectName(QString::fromUtf8("Triunfo"));
        Triunfo->resize(400, 300);
        iniciar = new QPushButton(Triunfo);
        iniciar->setObjectName(QString::fromUtf8("iniciar"));
        iniciar->setGeometry(QRect(80, 130, 75, 23));
        iniciar->setStyleSheet(QString::fromUtf8(""));
        pushButton_2 = new QPushButton(Triunfo);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 130, 75, 23));
        pushButton_2->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(0, 255, 255);"));
        textBrowser = new QTextBrowser(Triunfo);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(30, 80, 291, 41));
        textBrowser->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/roca.png);"));

        retranslateUi(Triunfo);

        QMetaObject::connectSlotsByName(Triunfo);
    } // setupUi

    void retranslateUi(QDialog *Triunfo)
    {
        Triunfo->setWindowTitle(QCoreApplication::translate("Triunfo", "Dialog", nullptr));
        iniciar->setText(QCoreApplication::translate("Triunfo", "SI", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Triunfo", "NO", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("Triunfo", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">Quieres jugar de nuevo ?</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Triunfo: public Ui_Triunfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRIUNFO_H
