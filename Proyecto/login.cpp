/*


 Clase login: ventana que permite registrar un nuevo usuario.

 */


#include "login.h"
#include "ui_login.h"
#include <QDebug>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::escribir_txt(string name, string data)
{
        fstream k(name,fstream::app);
        k << data; // se escribe sobre archivo ensayo
        //k.write(data.c_str(),data.length());
        k.close();//cerrar archivo
}

void Login::on_Registrar_clicked()
{
    string dato;
    nombre=ui->USERNAME->text();
    contrasena= ui->PASSWORD->text();
    std::string stringNombre = nombre.toLocal8Bit().constData();
    std::string stringContrasena = contrasena.toLocal8Bit().constData();
    dato.append(stringNombre);
    dato.push_back(',');
    dato.append(stringContrasena);
    dato.push_back('\n');
    escribir_txt("usuarios.txt",dato);
    Login::reject();
}

void Login::on_pushButton_2_clicked()
{
    Login::reject();
}
