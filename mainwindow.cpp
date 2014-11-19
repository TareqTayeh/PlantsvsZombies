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
    //Assigning player that last played to current user
    currentUserName = user.getUser1();
    currentUserLevel = user.getLevelofUser1();
    currentUserTime = user.getTimeofUser1();

    setPictures(); //Setting pictures to appear in mainwindow.ui


    // Drawing main screen picture
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap("C://Users/User/Desktop/Plants vs Zombies files/plants-vs-zombies.png"));
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
        textSearch = ui->UsercomboBox->currentText();
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
        if (user.getTotal()< 5)
        {
            ui->UsercomboBox->addItem(userName);
            QString time = QString::number(QDateTime::currentDateTime().toTime_t());
            user.addLists(time,userName,"1");
            user.Read("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
            user.Sort();
        }
        else
            QMessageBox::question(this,"Max 5 Users", "Maximum users reached. Delete a user before creating a new one.",
                                  QMessageBox::Ok|QMessageBox::Cancel); //Max 5 users in csv
    } 
}

void MainWindow::on_StartpushButton_clicked()
{
    //Showing current user level on screen
    ui->LevellineEdit->setText(currentUserLevel);

    //Drawing 10x5 lawn grid
    scene->clear();
    QBrush darkGreenBrush(Qt::darkGreen);
    QBrush brown (QColor(102,51,0));
    QBrush pale (QColor(255,229,204));
    QPen blackPen(Qt::black);
    scene->setBackgroundBrush(QBrush(darkGreenBrush));

    //Adding brown and pale tiles according to level
    if(currentUserLevel.toInt() == 1)
    {
        scene->addRect(0,0,60,375,blackPen,pale);
        scene->addRect(60,0,540,75,blackPen,brown);
        scene->addRect(60,75,540,75,blackPen,brown);
        scene->addRect(60,225,540,75,blackPen,brown);
        scene->addRect(60,300,540,75,blackPen,brown);
    }

    if(currentUserLevel.toInt() == 2)
    {
        scene->addRect(60,0,540,75,blackPen,brown);
        scene->addRect(0,0,60,375,blackPen,pale);
        scene->addRect(60,300,540,75,blackPen,brown);
    }
    if(currentUserLevel.toInt() > 2)
    {
        scene->addRect(0,0,60,375,blackPen,pale);
    }

    //Adding lines vertically
    scene->addLine(0,0,0,375,blackPen);
    scene->addLine(60,0,60,375,blackPen);
    scene->addLine(120,0,120,375,blackPen);
    scene->addLine(180,0,180,375,blackPen);
    scene->addLine(240,0,240,375,blackPen);
    scene->addLine(300,0,300,375,blackPen);
    scene->addLine(360,0,360,375,blackPen);
    scene->addLine(420,0,420,375,blackPen);
    scene->addLine(480,0,480,375,blackPen);
    scene->addLine(540,0,540,375,blackPen);
    scene->addLine(600,0,600,375,blackPen);

    //Adding lines horizontally
    scene->addLine(0,0,600,0,blackPen);
    scene->addLine(0,75,600,75,blackPen);
    scene->addLine(0,150,600,150,blackPen);
    scene->addLine(0,225,600,225,blackPen);
    scene->addLine(0,300,600,300,blackPen);
    scene->addLine(0,375,600,375,blackPen);

    //Adjusting graphicsview size
    ui->graphicsView->adjustSize();
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

    //Searches for username in csv
    name = user.SearchName(textSearch);
    time = user.SearchTime(textSearch);
    level = user.SearchLevel(textSearch);
    currentUserName = name;
    currentUserTime = time;
    currentUserLevel = level;
    qDebug() << name << time << level;
}
