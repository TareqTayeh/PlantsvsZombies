#include "mainwindow.h"
#include "ui_mainwindow.h"

ReadingCSVFiles user;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->UsercomboBox->addItem("Tarek");
    ui->UsercomboBox->addItem("Tayeh");
    ui->NamelineEdit->setPlaceholderText("Name");
    ui->LevellineEdit->setPlaceholderText("Level");

    QString playersFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
    QString levelsFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_levels.csv");
    user.Read(playersFile); //Reading the pvz_players.csv
    user.Read2(levelsFile); //Reading the pvz_levels.csv
    user.Sort(); //Sorting the users

    //Setting pictures to appear in mainwindow.ui
    QPixmap PeaShooter("C://Users/User/Desktop/Plants vs Zombies files/Peashooter_HD.png");
    ui->PeaShooterLabel->setPixmap(PeaShooter);
    QPixmap SunFlower("C://Users/User/Desktop/Plants vs Zombies files/Sunflower_HD.png");
    ui->SunFlowerLabel->setPixmap(SunFlower);
    QPixmap CherryBomb("C://Users/User/Desktop/Plants vs Zombies files/Cherry Bomb HD.png");
    ui->CherryBombLabel->setPixmap(CherryBomb);
    QPixmap Walnut("C://Users/User/Desktop/Plants vs Zombies files/Hd_Wall-nut.png");
    ui->WallNutLabel->setPixmap(Walnut);
    QPixmap PotatoMine("C://Users/User/Desktop/Plants vs Zombies files/Potato_Mine_HD.png");
    ui->PotatoMineLabel->setPixmap(PotatoMine);
    QPixmap SnowPea("C://Users/User/Desktop/Plants vs Zombies files/Snow_Pea_(HD_size).png");
    ui->SnowPeaLabel->setPixmap(SnowPea);
    QPixmap Chomper("C://Users/User/Desktop/Plants vs Zombies files/ChomperHD2.png");
    ui->ChomperLabel->setPixmap(Chomper);
    QPixmap Repeater("C://Users/User/Desktop/Plants vs Zombies files/Repeater_HD_HD.png");
    ui->RepeaterLabel->setPixmap(Repeater);
}

MainWindow::~MainWindow()
{
    user.Write(); //Saving upon exit
    delete ui;
}

void MainWindow::on_DeletepushButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete User", "Are you sure you want to delete user '"
                                  + ui->UsercomboBox->currentText() + "' ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes delete was clicked";
        //WRITE FUNCTIONALITY
      } else {
        qDebug() << "Yes delete was *not* clicked";
      }
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
    reply = QMessageBox::question(this, "Quit", "Are you sure you want to leave this level?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes quit was clicked";
        QApplication::quit();
      } else {
        qDebug() << "Yes quit was *not* clicked";
      }
}

void MainWindow::on_UserpushButton_clicked()
{
    QMessageBox::information(this,"Title",ui->UsercomboBox->currentText());
    QStringList info = user.Search(ui->UsercomboBox->currentText());
    //currentUserName = info[0];
    //currentUserTime = info[1];
    //currentUserLevel = info[2];

}
