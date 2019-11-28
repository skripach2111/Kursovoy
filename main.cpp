#include "authorization.h"

#include <QApplication>

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
    return a.exec();
}
