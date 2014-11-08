#ifndef READINGCSVFILES_H
#define READINGCSVFILES_H
#include <QString>
#include <QFile>
#include <QStringList>
#include <QImage>
#include <QDebug>
#include <QTextStream>
#include <QStatusBar>

class ReadingCSVFiles
{
private:
    QString user;
    int lastPlayedLevel;
    unsigned int timeStamp;

public:
    ReadingCSVFiles();
    QString getUser();
    int getLastPlayedLevel();
    unsigned int getTimeStamp();
    void setUser(QString);
    void setLastPlayedLevel(int);
    void setTimeStamp(unsigned int);
};

#endif // READINGCSVFILES_H
