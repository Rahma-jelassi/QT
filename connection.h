#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>

class Connection
{
private:
    QSqlDatabase db;
public:
    Connection();
    bool ouvrirConnexion();
    void fermerConnexion();

};

#endif // CONNEXION_H
