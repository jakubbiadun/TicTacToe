#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *button[9];
    //QToolButton *turnLabel;
    bool player1Turn;
    int amountOfTurns;
    char board[9];

    void prepareBoard();
    void isWin();
    void clear();
    void turnOffButton();
    void changeTurnLabel();

private slots:
   void buttonClicked();
   void newGameClicked();


};
#endif // MAINWINDOW_H
