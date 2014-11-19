#ifndef READINGCSVFILES_H
#define READINGCSVFILES_H
#include "mainwindow.h"

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
    bool Write();
    void Sort();
    QString SearchName(QString);
    QString SearchTime(QString);
    QString SearchLevel(QString);
    QString getUser(int) const;
    QString getLastLevelPlayed() const;
    QString getTimeStamp() const;
    QString getIndex() const;
    int getTotal() const;
    void addLists(QString, QString, QString);

private:
    QStringList userList;
    QStringList lastLevelPlayedList;
    QStringList timeStampList;
    int index;
    int total;
};

#endif // READINGCSVFILES_H
