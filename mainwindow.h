#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "readingcsvfiles.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_DeletepushButton_clicked();

    void on_NewpushButton_clicked();

    void on_StartpushButton_clicked();

    void on_RestartpushButton_clicked();

    void on_QuitpushButton_clicked();

    void on_UserpushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString currentUserName;
    QString currentUserLevel;
    QString currentUserTime;

};

#endif // MAINWINDOW_H
