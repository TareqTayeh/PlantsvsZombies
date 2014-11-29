#include "readingcsvfiles.h"
#include "mainwindow.h"

ReadingCSVFiles::ReadingCSVFiles()
{
   total = 0;
}

bool ReadingCSVFiles::ReadLevels(QString Filename) //Reads the file
{
    QFile mFile(Filename);

    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Could not open file for reading, application closed with an error.";
        while(true){ QApplication::quit();}
    }

    QTextStream t( &mFile ); // use a text stream
    QString line;
    levelList.clear();
    sequenceList.clear();
    rowsList.clear();
    startList.clear();
    intervalList.clear();
    decrementList.clear();

    while ( !t.atEnd() ) // loop until end of file...
    {
        line = t.readLine(); // line of text excluding '\n'
        QStringList fields = line.split(':');

        levelList.append(fields.at(0));
        sequenceList.append(fields.at(1));
        rowsList.append(fields.at(2));
        startList.append(fields.at(3));
        intervalList.append(fields.at(4));
        decrementList.append(fields.at(5));
    }

    qDebug() << levelList;
    qDebug() << sequenceList;
    qDebug() << rowsList;
    qDebug() << startList;
    qDebug() << intervalList;
    qDebug() << decrementList;

    return true;

    mFile.close();
}

bool ReadingCSVFiles::ReadPlayers(QString Filename)
{
    //QFile mFile(Filename);
    QFile mFile;
    mFile.setFileName("pvz_players.csv");
    QDir::setCurrent("C://Users/User/Desktop/Plants vs Zombies files/");
    if (mFile.exists() == false)
    {
        return true;
    }
    else
    {
        QTextStream t( &mFile ); // use a text stream
        userList.clear();
        lastLevelPlayedList.clear();
        timeStampList.clear();

        if(!mFile.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug() << "Could not open file for reading, starting application with no users";
            return false;
        }

            QString line;
            while ( !t.atEnd() ) // loop until end of file...
            {
                line = t.readLine(); // line of text excluding '\n'
                QStringList fields = line.split(':');
                if (fields.size() < 3)
                {
                    total = 0;

                    return false;
                }

                timeStampList.append(fields.at(0));
                userList.append(fields.at(1));
                lastLevelPlayedList.append(fields.at(2));

                total = userList.count();
            }

            qDebug() << timeStampList;
            qDebug() << userList;
            qDebug() << lastLevelPlayedList;


            return true;

             mFile.close();
    }

}

bool ReadingCSVFiles::Write()
{
    QString playersFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
    QFile mFilename(playersFile);

    if(mFilename.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream stream(&mFilename);
        for (int i = 0; i < total; i++)
        {
            stream << timeStampList[i] << ":" << userList[i] << ":" << lastLevelPlayedList[i] <<"\r\n";
        }

         mFilename.close();
    }
}

bool ReadingCSVFiles::Write(QString USER) //Writes to the file
{
    QString playersFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
    QFile mFilename(playersFile);

    for (int i = 0; i < total; i++)
     {
         if (USER == userList[i])
         {
            timeStampList[i]=QString::number(QDateTime::currentDateTime().toTime_t());
         }
    }

    if(mFilename.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream stream(&mFilename);
        for (int i = 0; i < total; i++)
        {
            stream << timeStampList[i] << ":" << userList[i] << ":" << lastLevelPlayedList[i] <<"\r\n";
        }

         mFilename.close();
    }
}

void ReadingCSVFiles::Sort() //Sorting in ascending order of time stamp
{
    QString temp;
    for(int i = 0; i < total; i++)
        {
            for(int j = i; j < total; j++)
            {
                if(timeStampList[j] > timeStampList[i])
                {
                    temp = timeStampList[i];
                    timeStampList[i] = timeStampList[j];
                    timeStampList[j] = temp;
                    temp = userList[i];
                    userList[i] = userList[j];
                    userList[j] = temp;
                    temp = lastLevelPlayedList[i];
                    lastLevelPlayedList[i] = lastLevelPlayedList[j];
                    lastLevelPlayedList[j] = temp;
                }
            }
    }

    qDebug() << timeStampList;
    qDebug() << userList;
    qDebug() << lastLevelPlayedList;
}

QString ReadingCSVFiles::SearchName(QString name) //Searches for name when user button clicked and returns name
{
    for (int i = 0; i < total; i++)
     {
         if (name == userList[i])
         {
            QString user = userList[i];
            return user;
         }
    }
}

QString ReadingCSVFiles::SearchTime(QString name) //Searches for name when user button clicked and returns time of user
{
    for (int i = 0; i < total; i++)
     {
         if (name == userList[i])
         {
            QString time = timeStampList[i];
            return time;
         }
    }
}

QString ReadingCSVFiles::SearchLevel(QString name) //Searches for name when user button clicked and returns level of user
{
    for (int i = 0; i < total; i++)
     {
         if (name == userList[i])
         {
            QString level = lastLevelPlayedList[i];
            return level;
         }
    }
}

QString ReadingCSVFiles::getUser(int x) const// function to return current user
{
    if (total > x)
        return userList[x];
    else
        return NULL;
}

QString ReadingCSVFiles::getUser1() const //Returns the name of the user with the highest timestamp(as its sorted)
{
    return userList[0];
}

QString ReadingCSVFiles::getLevelofUser1() const //Returns the level of the user with the highest timestamp(as its sorted)
{
    return lastLevelPlayedList[0];
}

QString ReadingCSVFiles::getTimeofUser1() const //Returns the time of the user with the highest timestamp(as its sorted)
{
    return timeStampList[0];
}

QString ReadingCSVFiles::getLevelList(int x) const
{
    return levelList[x];
}

QString ReadingCSVFiles::getRowsList(int x) const
{
    return rowsList[x];
}

QString ReadingCSVFiles::getStartList(int x) const
{
    return startList[x];
}

QString ReadingCSVFiles::getIntervalList(int x) const
{
    return intervalList[x];
}

QString ReadingCSVFiles::getDecrementList(int x) const
{
    return decrementList[x];
}

int ReadingCSVFiles::getTotal() const //Returns total number of users
{
    return total;
}

void ReadingCSVFiles::addLists(QString time, QString userName, QString level) //Called when new button is pressed, writes to csv file
{
    QString playersFile("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
    QFile mFilename(playersFile);

    if(mFilename.open(QFile::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&mFilename);
        stream << time << ":" << userName << ":" << level <<"\r\n";
        mFilename.close();
    }
}

void ReadingCSVFiles::deleteUser(QString name) //Deletes User
{
    for (int i = 0; i < total; i++)
     {
         if (name == userList[i])
         {
            userList[i]="0";
            lastLevelPlayedList[i]="0";
            timeStampList[i]="0";
         }
    }
    Write();
    ReadPlayers("C://Users/User/Desktop/Plants vs Zombies files/pvz_players.csv");
}



