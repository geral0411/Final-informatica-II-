#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class GameOver; }
QT_END_NAMESPACE

class GameOver : public QDialog
{
    Q_OBJECT

public:
    GameOver(QWidget *parent = nullptr);
    ~GameOver();

private slots:
    void on_iniciar_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H

