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
    user.Sort(); //Sorting the users

    for (int i = 0; i < 5 ; i++)
    {
        if (user.getUser(i)!=NULL && user.getUser(i)!="0")
        {
            ui->UsercomboBox->addItem(user.getUser(i));
        }
    }


   //Assigning player that last played to current user
    currentUserName = user.getUser1();
    currentUserLevel = user.getLevelofUser1();
    currentUserTime = user.getTimeofUser1();

    setPictures(); //Setting pictures to appear in mainwindow.ui


    // Drawing main screen picture
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap("C://Users/User/Desktop/Plants vs Zombies files/plants-vs-zombies.png"));

    //Timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
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
    textSearch = ui->UsercomboBox->currentText();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete User", "Are you sure you want to delete user '"
                                  + ui->UsercomboBox->currentText() + "' ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes delete was clicked";
        user.deleteUser(textSearch); //Deletes User
        ui->UsercomboBox->clear(); //Clears combobox before readding non NULL users
        for (int i = 0; i < 5 ; i++)
        {
            if (user.getUser(i)!=NULL && user.getUser(i)!="0")
            {
                 ui->UsercomboBox->addItem(user.getUser(i));
            }
        }
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
//        if (user.getTotal()< 5)
//        {
            ui->UsercomboBox->addItem(userName);
            QString time = QString::number(QDateTime::currentDateTime().toTime_t());
            user.addLists(time,userName,"1");
            user.Read("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
            user.Sort();
//        }
//        else
//            QMessageBox::question(this,"Max 5 Users", "Maximum users reached. Delete a user before creating a new one.",
//                                  QMessageBox::Ok|QMessageBox::Cancel); //Max 5 users in csv
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
    scene->addRect(0,0,75,375,blackPen,pale); //adding pale tile, the home coloumn

    //Adding brown tiles according to level
    if(currentUserLevel.toInt() == 1) //Only 1 green row will be shown
    {
        scene->addRect(75,0,675,75,blackPen,brown);
        scene->addRect(75,75,675,75,blackPen,brown);
        scene->addRect(75,225,675,75,blackPen,brown);
        scene->addRect(75,300,675,75,blackPen,brown);
    }

    if(currentUserLevel.toInt() == 2) //Only 3 green rows will be shown
    {
        scene->addRect(75,0,675,75,blackPen,brown);
        scene->addRect(75,300,675,75,blackPen,brown);
    }

    //Adding lines vertically
    int squareSize = 75;

    for(int i=0; i<751; i+=squareSize)
    {
        scene->addLine(i,0,i,375,blackPen);
    }

    //Adding lines horizontally
    for(int i=0; i <376; i+=squareSize)
    {
        scene->addLine(0,i,750,i,blackPen);
    }

    //Adjusting graphicsview size
    ui->graphicsView->adjustSize();

    //Adding lawn mowers in the home column
    QPixmap LawnMower("C://Users/User/Desktop/Plants vs Zombies files/Lawn_Mower.png");
    scene->addPixmap(LawnMower)->setOffset(0,10);
    scene->addPixmap(LawnMower)->setOffset(0,85);
    scene->addPixmap(LawnMower)->setOffset(0,160);
    scene->addPixmap(LawnMower)->setOffset(0,235);
    scene->addPixmap(LawnMower)->setOffset(0,310);

    //Adding sun(testing)
    srand(time(NULL));
    QPixmap Sun1("C://Users/User/Desktop/Plants vs Zombies files/Sun.png");
    QGraphicsPixmapItem *Sun = new sunpoints();
    Sun->setPixmap(Sun1);
    scene->addItem(Sun);
    timer->start(18);
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
        {
            scene->setBackgroundBrush(QBrush(Qt::white));
            scene->clear();
            scene->addPixmap(QPixmap("C://Users/User/Desktop/Plants vs Zombies files/plants-vs-zombies.png"));
        }
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

    //Showing current user level on screen
    ui->LevellineEdit->setText(currentUserLevel);
}

void MainWindow::on_PeaShooterToolButton_clicked()
{

}
