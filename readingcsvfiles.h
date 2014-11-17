#ifndef READINGCSVFILES_H
#define READINGCSVFILES_H
#include <QString>
#include <QFile>
#include <QStringList>
#include <QImage>
#include <QDebug>
#include <QTextStream>
#include <QStatusBar>
#include <QApplication>
#include <QMessageBox>
#include <QDateTime>

class ReadingCSVFiles
{
public:
    ReadingCSVFiles();
    bool Read(QString);
    bool Read2(QString);
    bool Write();
    void Sort();
    QStringList Search(QString);
    QString getUser() const;
    QString getLastLevelPlayed() const;
    QString getTimeStamp() const;
    QString getIndex() const;
    QString getTotal() const;
    QStringList info;


private:
    QStringList userList;
    QStringList lastLevelPlayedList;
    QStringList timeStampList;
    int index;
    int total;
};

#endif // READINGCSVFILES_H
