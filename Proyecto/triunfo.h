#ifndef TRIUNFO_H
#define TRIUNFO_H

#include <QDialog>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class Triunfo;
}
QT_END_NAMESPACE

class Triunfo : public QDialog
{
    Q_OBJECT

public:
    explicit Triunfo(QWidget *parent = nullptr);
    ~Triunfo();

private slots:
    void on_iniciar_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Triunfo *ui;
};


#endif // TRIUNFO_H
