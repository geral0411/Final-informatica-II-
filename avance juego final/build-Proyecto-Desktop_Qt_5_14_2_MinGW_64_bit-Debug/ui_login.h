/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLineEdit *USERNAME;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLineEdit *PASSWORD;
    QPushButton *Registrar;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(400, 300);
        USERNAME = new QLineEdit(Login);
        USERNAME->setObjectName(QString::fromUtf8("USERNAME"));
        USERNAME->setGeometry(QRect(120, 120, 171, 20));
        USERNAME->setEchoMode(QLineEdit::Normal);
        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 40, 301, 51));
        QFont font;
        font.setPointSize(26);
        label->setFont(font);
        label_2 = new QLabel(Login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 120, 47, 13));
        pushButton_2 = new QPushButton(Login);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(210, 200, 81, 23));
        label_3 = new QLabel(Login);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 160, 47, 13));
        PASSWORD = new QLineEdit(Login);
        PASSWORD->setObjectName(QString::fromUtf8("PASSWORD"));
        PASSWORD->setGeometry(QRect(120, 160, 171, 20));
        PASSWORD->setEchoMode(QLineEdit::Password);
        Registrar = new QPushButton(Login);
        Registrar->setObjectName(QString::fromUtf8("Registrar"));
        Registrar->setGeometry(QRect(120, 200, 81, 23));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
#if QT_CONFIG(tooltip)
        USERNAME->setToolTip(QCoreApplication::translate("Login", "Enter an email address", nullptr));
#endif // QT_CONFIG(tooltip)
        USERNAME->setInputMask(QString());
        USERNAME->setText(QCoreApplication::translate("Login", "Register New User", nullptr));
        label->setText(QCoreApplication::translate("Login", "registro usuario", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "Username", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_2->setToolTip(QCoreApplication::translate("Login", "Cancel registration", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_2->setText(QCoreApplication::translate("Login", "Cancel", nullptr));
        label_3->setText(QCoreApplication::translate("Login", "Password", nullptr));
#if QT_CONFIG(tooltip)
        PASSWORD->setToolTip(QCoreApplication::translate("Login", "Password may contain A-Z upper or lowercase, 0-9, _underscore, and -hyphen. Max length is 20. Minimum length is 7", nullptr));
#endif // QT_CONFIG(tooltip)
        PASSWORD->setText(QCoreApplication::translate("Login", "Register New User", nullptr));
#if QT_CONFIG(tooltip)
        Registrar->setToolTip(QCoreApplication::translate("Login", "Submit info", nullptr));
#endif // QT_CONFIG(tooltip)
        Registrar->setText(QCoreApplication::translate("Login", "Check in", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
