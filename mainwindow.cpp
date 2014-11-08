#include "mainwindow.h"
#include "ui_mainwindow.h"

ReadingCSVFiles csvUser;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->UsercomboBox->addItem("Tareq");
    ui->UsercomboBox->addItem("Tayeh");
    ui->NamelineEdit->setPlaceholderText("Name");
    ui->LevellineEdit->setPlaceholderText("Level");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DeletepushButton_clicked()
{

}

void MainWindow::on_NewpushButton_clicked()
{
    //Validate name
    //Write user to csv file, level 1, timestamp is automatic
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Title",ui->NamelineEdit->text()+ "?", QMessageBox::Ok|QMessageBox::Cancel);
    QString userName = ui->NamelineEdit->text();
    if (reply == QMessageBox::Ok)
        csvUser.setUser(userName);
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
