#ifndef DATABASEBUFFER_H
#define DATABASEBUFFER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QVariant>
#include <QtAlgorithms>

struct User
{
    QString login;
    QString role;
    QString fio;
};

struct User_Database
{
    QString user_name;
    QString database_name;
};

struct DatabaseInfo
{
    QString name;
    QString text;
};

class DatabaseBuffer
{
    //Q_OBJECT

    QSqlDatabase *db;

    QList <User> UsersList;
    QList <DatabaseInfo> DatabaseList;
    QList <User_Database> UserDatabaseList;
    QList <QString> DatabaseNameList;


public:
    DatabaseBuffer();
    DatabaseBuffer(QSqlDatabase *newdb);

    void setDB(QSqlDatabase *newdb);
    bool findDB(QString DB_name);

    bool DownloadUsers();
    bool DownloadDatabase();
    bool DownloadDatabaseName();
    bool DownloadUsers_DB();

    bool FindDatabaseName(QString name);

    QList <User> getUsersList();
};

#endif // DATABASEBUFFER_H
