#include "readingcsvfiles.h"
#include "mainwindow.h"

ReadingCSVFiles::ReadingCSVFiles()
{

}

QString ReadingCSVFiles::getUser() // function to return current caption
{
    return user;
}

int ReadingCSVFiles::getLastPlayedLevel() // function to return current image
{
    return lastPlayedLevel;
}

unsigned int ReadingCSVFiles::getTimeStamp()
{
    return timeStamp;
}

void ReadingCSVFiles::setUser(QString user)
{
    this->user = user;
}

void ReadingCSVFiles::setLastPlayedLevel(int lastPlayedLevel)
{
    this->lastPlayedLevel = lastPlayedLevel;
}

void ReadingCSVFiles::setTimeStamp(unsigned int timeStamp)
{
    this->timeStamp = timeStamp;
}

