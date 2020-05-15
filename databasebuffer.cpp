#include "databasebuffer.h"
#include <QDebug>

bool SortUsersRule(const User &a, const User &b)
{ return a.fio > b.fio; }
bool SortDatabaseRule(const DatabaseInfo &a, const DatabaseInfo &b)
{ return  a.name > b.name; }
bool SortDatabaseNameRule(const QString &a, const QString &b)
{ return  a > b; }

DatabaseBuffer::DatabaseBuffer()
{

}

DatabaseBuffer::DatabaseBuffer(QSqlDatabase *newdb)
{
    db = newdb;
}

void DatabaseBuffer::setDB(QSqlDatabase *newdb)
{
    db = newdb;
}

bool DatabaseBuffer::DownloadUsers()
{
    if(db->open())
    {
        QSqlQuery query;
        query.exec("select * from study.users");

        if(!query.size())
            return false;

        User temp;

        while (query.next())
        {
            temp.login = query.value(0).toString();
            temp.role = query.value(1).toString();
            temp.fio = query.value(2).toString();
            UsersList.push_back(temp);
        }

        qSort(UsersList.begin(), UsersList.end(), SortUsersRule);

        return true;
    }

    return false;
}

bool DatabaseBuffer::DownloadDatabase()
{
    if(db->open())
    {
        QSqlQuery query;
        query.exec("SELECT * FROM study.databases;");

        if(!query.size())
            return false;

        DatabaseInfo temp;

        while (query.next())
        {
            temp.name = query.value(0).toString();
            temp.text = query.value(1).toString();
            DatabaseList.push_back(temp);
        }

        qSort(DatabaseList.begin(), DatabaseList.end(), SortDatabaseRule);

        return true;
    }

    return false;
}

bool DatabaseBuffer::DownloadUsers_DB()
{
    if(db->open())
    {
        QSqlQuery query;
        query.exec("SELECT * FROM study.user_database;");

        if(!query.size())
            return false;

        User_Database temp;

        while (query.next())
        {
            temp.user_name = query.value(0).toString();
            temp.database_name = query.value(1).toString();
            UserDatabaseList.push_back(temp);
        }

        return true;
    }

    return false;
}

bool DatabaseBuffer::DownloadDatabaseName()
{
    if(db->open())
    {
        qDebug() << "DB open!";
        QSqlQuery query;
        query.exec("SELECT name_db FROM study.databases;");

        if(!query.size())
            return false;

        QString temp;

        while (query.next())
        {
            temp = query.value(0).toString();
            DatabaseNameList.push_back(temp);
            qDebug() << temp;
        }

        qSort(DatabaseNameList.begin(), DatabaseNameList.end(), SortDatabaseNameRule);

        return true;
    }

    return false;
}

bool DatabaseBuffer::FindDatabaseName(QString name)
{
    QList<QString>::iterator it = qFind(DatabaseNameList.begin(), DatabaseNameList.end(), name);
    if(DatabaseNameList.end() == it && name.size() != 0)
        return false;

    return true;
}

QList <User> DatabaseBuffer::getUsersList()
{
    return UsersList;
}
