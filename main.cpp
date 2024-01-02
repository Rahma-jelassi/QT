#include "mainwindow.h"
#include "gestion_de_stock.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    if(c.ouvrirConnexion())
    {

        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n""Click Cancel to exit."), QMessageBox::Cancel);

        // qDebug()<<"Connection successful";
    }
    else

        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n""Click Cancel to exit."), QMessageBox::Cancel);

       // qDebug()<<"Connection failed";


    //c.closeConnection();*/
   MainWindow w;
   w.show();

    return a.exec();
}
