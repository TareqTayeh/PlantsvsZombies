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
    for (int i = 0; i < 5 ; i++)
    {
        if (user.getUser(i)!=NULL)
        {
            ui->UsercomboBox->addItem(user.getUser(i));
        }
    }

    user.Sort(); //Sorting the users
    setPictures(); //Setting pictures to appear in mainwindow.ui


    // Drawing 10x5 lawn grid
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush darkGreenBrush(Qt::darkGreen);
    QPen greenPen(Qt::green);

    scene->setBackgroundBrush(QBrush(darkGreenBrush));
    //rect = scene->addRect(-450,0,70,70,greenPen,darkGreenBrush);
}

MainWindow::~MainWindow()
{
    user.Write();
    delete ui;
}

void MainWindow::setPictures() //Setting pictures to appear in mainwindow.ui
{
    QPixmap PeaShooter("C://Users/User/Desktop/Plants vs Zombies files/Peashooter_HDD.png");
    ui->PeaShooterToolButton->setIcon(QIcon(PeaShooter));
    QString tooltip="Pea Shooter \nCost 100";
    ui->PeaShooterToolButton->setToolTip(tooltip);

    QPixmap SunFlower("C://Users/User/Desktop/Plants vs Zombies files/Sunflower_HD.png");
    ui->SunFlowerToolButton->setIcon(QIcon(SunFlower));
    QString tooltip1="Sun Flower \nCost 50";
    ui->SunFlowerToolButton->setToolTip(tooltip1);

    QPixmap CherryBomb("C://Users/User/Desktop/Plants vs Zombies files/Cherry Bomb HD.png");
    ui->CherryBombToolButton->setIcon(QIcon(CherryBomb));
    QString tooltip2="Cherry Bomb \nCost 150";
    ui->CherryBombToolButton->setToolTip(tooltip2);

    QPixmap Walnut("C://Users/User/Desktop/Plants vs Zombies files/Hd_Wall-nut.png");
    ui->WalNutToolButton->setIcon(QIcon(Walnut));
    QString tooltip3="WalNut \nCost 50";
    ui->WalNutToolButton->setToolTip(tooltip3);

    QPixmap PotatoMine("C://Users/User/Desktop/Plants vs Zombies files/Potato_Mine_HD.png");
    ui->PotatoMineToolButton->setIcon(QIcon(PotatoMine));
    QString tooltip4="Potato Mine \nCost 25";
    ui->PotatoMineToolButton->setToolTip(tooltip4);

    QPixmap SnowPea("C://Users/User/Desktop/Plants vs Zombies files/Snow_Pea_(HD_size).png");
    ui->SnowPeaToolButton->setIcon(QIcon(SnowPea));
    QString tooltip5="Snow Pea \nCost 175";
    ui->SnowPeaToolButton->setToolTip(tooltip5);

    QPixmap Chomper("C://Users/User/Desktop/Plants vs Zombies files/ChomperHD2.png");
    ui->ChomperToolButton->setIcon(QIcon(Chomper));
    QString tooltip6="Chomper \nCost 150";
    ui->ChomperToolButton->setToolTip(tooltip6);

    QPixmap Repeater("C://Users/User/Desktop/Plants vs Zombies files/Repeater_HD_HD.png");
    ui->RepeaterToolButton->setIcon(QIcon(Repeater));
    QString tooltip7="Repeater \nCost 200";
    ui->RepeaterToolButton->setToolTip(tooltip7);

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
    QString userName = (ui->NamelineEdit->text());
    if (reply == QMessageBox::Ok)
    {
        ui->UsercomboBox->addItem(userName);
        QString time = QString::number(QDateTime::currentDateTime().toTime_t());
        user.addLists(time,userName,"1");
        user.Read("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
        user.Sort();
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
    textSearch = ui->UsercomboBox->currentText();
    QString name,time,level;
    name = user.SearchName(textSearch);
    time = user.SearchTime(textSearch);
    level = user.SearchLevel(textSearch);
    currentUserName = name;
    currentUserTime = time;
    currentUserLevel = level;
    qDebug() << name << time << level;
}
