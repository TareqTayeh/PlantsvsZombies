#include "mainwindow.h"
#include "ui_mainwindow.h"

ReadingCSVFiles user;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->NamelineEdit->setPlaceholderText("Name");
    ui->LevellineEdit->setPlaceholderText("Level");
    QString playersFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
    QString levelsFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_levels.csv");
    user.Read(playersFile); //Reading the pvz_players.csv
    user.Read2(levelsFile); //Reading the pvz_levels.csv
    user.Sort();
}

MainWindow::~MainWindow()
{
    user.Write(); //Saving upon exit
    delete ui;
}

void MainWindow::on_DeletepushButton_clicked()
{

}

void MainWindow::on_NewpushButton_clicked()
{
    //Validate name
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"New User",ui->NamelineEdit->text()+ "?", QMessageBox::Ok|QMessageBox::Cancel);
    QString userName = ui->NamelineEdit->text();
    if (reply == QMessageBox::Ok)
    {
        ui->UsercomboBox->addItem(userName);
        currentUserName = userName;
        currentUserLevel = 1;
        currentUserTime = QDateTime::currentDateTime().toTime_t();
    } 
}

void MainWindow::on_StartpushButton_clicked()
{

}

void MainWindow::on_RestartpushButton_clicked()
{

}

void MainWindow::on_QuitpushButton_clicked() //Application closes when user presses Yes
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quit", "Are you sure you want to quit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QApplication::quit();
      } else {
        qDebug() << "Yes was *not* clicked";
      }
}

void MainWindow::on_UserpushButton_clicked()
{
    QMessageBox::information(this,"Title",ui->UsercomboBox->currentText());
}
