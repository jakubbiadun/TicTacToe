#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox> // https://doc.qt.io/qt-6/qmessagebox.html
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    prepareBoard();
   /* QObject::connect(ui->P1, SIGNAL(clicked()),this, SLOT(P1()));
    QObject::connect(ui->P2, SIGNAL(clicked()),this, SLOT(P2()));
    QObject::connect(ui->P3, SIGNAL(clicked()),this, SLOT(P3()));
    QObject::connect(ui->P4, SIGNAL(clicked()),this, SLOT(P4()));
    QObject::connect(ui->P5, SIGNAL(clicked()),this, SLOT(P5()));
    QObject::connect(ui->P6, SIGNAL(clicked()),this, SLOT(P6()));
    QObject::connect(ui->P7, SIGNAL(clicked()),this, SLOT(P7()));
    QObject::connect(ui->P8, SIGNAL(clicked()),this, SLOT(P8()));
    QObject::connect(ui->P9, SIGNAL(clicked()),this, SLOT(P9())); */
    QObject::connect(ui->newgame, SIGNAL(clicked()),this, SLOT(newGameClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::prepareBoard()
{
    player1Turn = 1;
    amountOfTurns = 0;
    button[0] = ui ->P1;
    button[1] = ui ->P2;
    button[2] = ui ->P3;
    button[3] = ui ->P4;
    button[4] = ui ->P5;
    button[5] = ui ->P6;
    button[6] = ui ->P7;
    button[7] = ui ->P8;
    button[8] = ui ->P9;

    for(int i =0; i<9;i++){
        connect(button[i],SIGNAL(clicked()), this, SLOT(buttonClicked()));
        button[i] -> setEnabled(1);
    }
    clear();
    changeTurnLabel();
}

void MainWindow::isWin()
{
    char currentPlayer;
    if(player1Turn == 1){
        currentPlayer = 'O';
    }
    else currentPlayer = 'X';

    if((board[0] == currentPlayer && board[1] == currentPlayer && board[2] == currentPlayer) ||
            (board[3] == currentPlayer && board[4] == currentPlayer && board[5] == currentPlayer) ||
            (board[6] == currentPlayer && board[7] == currentPlayer && board[8] == currentPlayer) ||
            (board[1] == currentPlayer && board[4] == currentPlayer && board[7] == currentPlayer) ||
            (board[2] == currentPlayer && board[5] == currentPlayer && board[8] == currentPlayer) ||
            (board[0] == currentPlayer && board[1] == currentPlayer && board[6] == currentPlayer) ||
            (board[0] == currentPlayer && board[4] == currentPlayer && board[8] == currentPlayer) ||
            (board[2] == currentPlayer && board[4] == currentPlayer && board[6] == currentPlayer)){
                QMessageBox::information(this,"Wynik","Wygrywa gracz " + QString(currentPlayer)); // czemu sypiesz bledami
                turnOffButton();
    }
    else if(amountOfTurns == 9){ // cale pole zapelnione
        QMessageBox::information(this,"Wynik", "Remis"); //czemu sypiesz bleadmi // https://www.obliczeniowo.com.pl/908
        turnOffButton();
    }
}

void MainWindow::clear()
{
    for(int i= 0;i<9;i++){
        button[i]->setIcon(QIcon());
        button[i]->setText("");
        board[i] = ' ';
    }
}

void MainWindow::turnOffButton()
{
    for(int i= 0;i<9;i++){
        button[i]->setEnabled(0);
    }
}

void MainWindow::changeTurnLabel()
{
    // do poprawy
    //QLabel *buttonl = ui->TurnIcon;
   // QPixmap pixmap;
    if(player1Turn == 1){
        QPixmap pixmap(":/img/img/osmall.bmp");
        ui->TurnIcon->setPixmap(pixmap);
    }
    else{
        QPixmap pixmap(":/img/img/xsmall.bmp");
        ui->TurnIcon->setPixmap(pixmap);
    }
//    QIcon icon(pixmap);
//    buttonl->setIcon(icon);
//    buttonl->setIconSize(pixmap.size());
}

void MainWindow::buttonClicked()
{
    QPushButton *buttonn = qobject_cast<QPushButton*>(sender());
    int bIndex = -1;

    for(int i=0;i<9;i++){
        if(button[i] == buttonn){
            bIndex = i;
            break;
        }
    }

    if(bIndex != -1 && board[bIndex] == ' '){
        if(player1Turn){
            QPixmap pixmap(":/img/img/o.bmp");
            QIcon icon(pixmap);
            buttonn->setIcon(icon);
            buttonn->setIconSize(pixmap.rect().size());
            board[bIndex] = 'O';
        }
        else{
            QPixmap pixmap(":/img/img/x.bmp");
            QIcon icon(pixmap);
            buttonn->setIcon(icon);
            buttonn->setIconSize(pixmap.rect().size());
            board[bIndex] = 'X';
        }
    }
    amountOfTurns++;
    isWin();
    player1Turn = !(player1Turn);
    changeTurnLabel();
}

void MainWindow::newGameClicked()
{
    clear();
    for(int i=0;i<9;i++){
        button[i]->setEnabled(1);
    }
    player1Turn = 1;
    amountOfTurns = 0;
    changeTurnLabel();
}



