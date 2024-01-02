#include "connection.h"
#include <QDebug>
Connection::Connection()
{

}

bool Connection::ouvrirConnexion()
{db=QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("Source_Projet2A");
    db.setUserName("Rahma");//inserer nom de l'utilisateur
    db.setPassword("rahmaa123");//inserer mot de passe de cet utilisateur


    if (db.open())
          return true;
    return  false;
    }

    void Connection::fermerConnexion()
    {db.close();}


