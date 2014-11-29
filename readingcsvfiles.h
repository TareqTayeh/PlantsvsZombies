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
#include <QDir>

class ReadingCSVFiles
{
public:
    ReadingCSVFiles();
    bool ReadPlayers(QString);
    bool ReadLevels(QString);
    bool Write();
    bool Write(QString);
    void Sort();
    QString SearchName(QString);
    QString SearchTime(QString);
    QString SearchLevel(QString);
    QString getUser(int) const;
    QString getUser1() const;
    QString getLevelofUser1() const;
    QString getTimeofUser1() const;
    QString getLevelList(int) const;
    QString getRowsList(int) const;
    QString getStartList(int) const;
    QString getIntervalList(int) const;
    QString getDecrementList(int) const;
    int getTotal() const;
    void addLists(QString, QString, QString);
    void deleteUser(QString);

private:
    QStringList userList;
    QStringList lastLevelPlayedList;
    QStringList timeStampList;
    QStringList levelList;
    QStringList sequenceList;
    QStringList rowsList;
    QStringList startList;
    QStringList intervalList;
    QStringList decrementList;
    int total;
};

#endif // READINGCSVFILES_H
