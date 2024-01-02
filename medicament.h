#ifndef MEDICAMENT_H
#define MEDICAMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtSql>
#include<QDebug>

class Medicament
{public:
    Medicament();
    Medicament(int,QString,QString,QString,QDate,int,int);
    QString get_nom();
    QString get_forme();
    QString get_famille();
    QDate get_date();
    int get_identifiant();
    int get_prix();
    int get_stock();
    bool ajouter();

    bool ajouterAvecIncrementationStock();


    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool verifier_existence(int);
    bool modifier(int , QString NOM, QString FORME, QString FAMILLE,QDate DATECREATION,int PRIX,int STOCK );
    QSqlQueryModel* rechercherParForme(QString FORME);
    QSqlQueryModel* rechercherParFamille(QString FAMILLE);


private:
    Ui::Gestion_du_medicament *ui;
    Medicament tabmedicament;
    QString NOM,FORME,FAMILLE;
    int ID,PRIX,STOCK;
    QDate DATECREATION;
};

#endif
