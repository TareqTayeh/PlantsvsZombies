#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "readingcsvfiles.h"
#include "plants.h"
#include "sunpoints.h"
#include "zombies.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QIcon>
#include <QToolButton>
#include <QToolTip>
#include <string>
#include <QGraphicsPixmapItem>
#include <ctime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setPictures();
    QString textSearch;
    void drawRect(int,int);
    void drawPeaShooter(int,int);
    void drawSunFlower(int,int);
    void drawCherryBomb(int,int);
    void drawWalNut(int,int);
    void drawPotatoMine(int,int);
    void drawSnowPea(int,int);
    void drawChomper(int,int);
    void drawRepeater(int,int);

private slots:
    void on_DeletepushButton_clicked();

    void on_NewpushButton_clicked();

    void on_StartpushButton_clicked();

    void on_RestartpushButton_clicked();

    void on_QuitpushButton_clicked();

    void on_UserpushButton_clicked();

    void on_PeaShooterToolButton_clicked();

    void on_SunFlowerToolButton_clicked();

    void on_CherryBombToolButton_clicked();

    void on_WalNutToolButton_clicked();

    void on_PotatoMineToolButton_clicked();

    void on_SnowPeaToolButton_clicked();

    void on_ChomperToolButton_clicked();

    void on_RepeaterToolButton_clicked();

private:
    Ui::MainWindow *ui;
    QString currentUserName;
    QString currentUserTime;
    QString currentUserLevel;
    QGraphicsScene *scene;
    QTimer *timer;
    int plant_ID;
};

#endif // MAINWINDOW_H
