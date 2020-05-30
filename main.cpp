#include "authorization.h"

#include <QApplication>
#include "databaseselectiondialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile*    fileStyle = new QFile( ":qdarkstyle\\style.qss" );
    if ( fileStyle->exists() )
    {
        fileStyle->open( QFile::ReadOnly | QFile::Text );
        QTextStream      textStream( fileStyle );

        a.setStyleSheet( textStream.readAll() );
    }
    delete fileStyle;

    Authorization auth;
    auth.show();

//    QList <QString> list;

//    list.push_back("DB___1");
//    list.push_back("DB___2");
//    list.push_back("DB___3");
//    list.push_back("DB___4");
//    list.push_back("DB___5");
//    list.push_back("DB___6");
//    list.push_back("DB___7");
//    list.push_back("DB___8");
//    list.push_back("DB___9");
//    list.push_back("DB___10");
//    list.push_back("DB___11");
//    list.push_back("DB___12");
//    list.push_back("DB___13");
//    list.push_back("DB___14");
//    list.push_back("DB___15");
//    list.push_back("DB___16");
//    list.push_back("DB___17");
//    list.push_back("DB___18");
//    list.push_back("DB___19");


//    DatabaseSelectionDialog dialog;
//    qDebug() << "Set Available";
//    dialog.setAvailableDB(list);
//    qDebug() << "Show";
//    dialog.show();
//    qDebug() << "end";

    return a.exec();
}
