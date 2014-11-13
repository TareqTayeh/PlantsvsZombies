#include "readingcsvfiles.h"
#include "mainwindow.h"

ReadingCSVFiles::ReadingCSVFiles()
{
    index = 0; total = 0;
}

bool ReadingCSVFiles::Read(QString Filename)
{
    QFile mFile(Filename);

    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Could not open file for reading, application closed with an error.";
        while(true){ QApplication::quit();}
    }

    QTextStream t( &mFile ); // use a text stream
    QString line;
    userList.clear();
    lastLevelPlayedList.clear();
    timeStampList.clear();

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

bool ReadingCSVFiles::Read2(QString)
{

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
            //stream << QDateTime::currentDateTime().toTime_t() << ":" << userName << ":" << 1 <<"\n";
        }

    }
        mFilename.flush();
        mFilename.close();

}

void ReadingCSVFiles::Sort()
{
    QString temp;
    for(int i = 0; i < total; i++)
        {
            for(int j = i; j < total; j++)
            {
                if(timeStampList[j] < timeStampList[i])
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
}

QString ReadingCSVFiles::getUser() const // function to return current user
{
    return userList.at(index);
}

QString ReadingCSVFiles::getLastLevelPlayed() const // function used to return user last level played
{
    return lastLevelPlayedList.at(index);
}

QString ReadingCSVFiles::getTimeStamp() const // function used to return time stamp of user
{
    return timeStampList.at(index);
}

QString ReadingCSVFiles::getIndex() const
{
    QString temp = QString::number(index+1);
    return temp;
}

QString ReadingCSVFiles::getTotal() const
{
    QString temp = QString::number(total);
    return temp;
}


