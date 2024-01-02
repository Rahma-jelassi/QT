#include "medicament.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

Medicament::Medicament()
{
    ID = 0;
    STOCK = 0;
}

Medicament::Medicament(int ID, QString NOM, QString FORME, QString FAMILLE, QDate DATECREATION, int PRIX,int STOCK)
{
    this->ID = ID;
    this->NOM = NOM;
    this->FORME = FORME;
    this->FAMILLE = FAMILLE;
    this->DATECREATION = DATECREATION;
    this->PRIX = PRIX;
    STOCK = 0;
}

QString Medicament::get_nom() { return NOM; }
QString Medicament::get_forme() { return FORME; }
QString Medicament::get_famille() { return FAMILLE; }
QDate Medicament::get_date() { return DATECREATION; }
int Medicament::get_identifiant() { return ID; }
int Medicament::get_prix() { return PRIX; }
int Medicament::get_stock() { return STOCK; }

bool Medicament::ajouter()
{
    //controle de saisi
    if (NOM.isEmpty() || FORME.isEmpty() || FAMILLE.isEmpty() || DATECREATION.isNull() || PRIX < 0 || STOCK < 0)
        {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                 QObject::tr("Veuillez remplir tous les champs correctement."), QMessageBox::Cancel);

            return false;
        }
    QSqlQuery query;
    QString res = QString::number(ID);
    query.prepare("INSERT INTO CLIENT (ID, NOM, FORME, FAMILLE, DATECREATION, PRIX, STOCK) "
                  "VALUES (:ID, :NOM, :FORME, :FAMILLE, :DATECREATION, :PRIX, :STOCK)");

    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":FORME", FORME);
    query.bindValue(":FAMILLE", FAMILLE);
    query.bindValue(":DATECREATION", DATECREATION);
    query.bindValue(":PRIX", PRIX);
    query.bindValue(":STOCK", STOCK);

    return query.exec();
}

bool Medicament::ajouterAvecIncrementationStock()
{
    STOCK = 0;
    if (ajouter()) {
        STOCK++; // Incrémentation
        if (STOCK <= 5) {
             QMessageBox::information(nullptr, QObject::tr("Notification"),
                                      QObject::tr("Le niveau de stock est  inférieur ou égal à 5."), QMessageBox::Ok);
        }
        QSqlQuery query;
        query.prepare("UPDATE CLIENT SET STOCK =  :STOCK  WHERE ID = :ID");
        query.bindValue(":STOCK", STOCK);
        query.bindValue(":ID", ID);

        return query.exec();
    }

    return false;
}

QSqlQueryModel *Medicament::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FORME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("FAMILLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATECREATION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("STOCK"));

    return model;
}

bool Medicament::supprimer(int ID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE ID = :ID");
    query.bindValue(":ID", ID);

    if (query.exec()) {
        // Médicament supprimé avec succès, maintenant mettre à jour le stock
        QSqlQuery updateStockQuery;
        updateStockQuery.prepare("UPDATE CLIENT SET STOCK = STOCK - 1 WHERE ID = :ID");
        updateStockQuery.bindValue(":ID", ID);
        updateStockQuery.exec();
        return true;
    }

    return false;
}


/*
bool Medicament::ajouter()
{
QSqlQuery query;
QString res= QString::number(ID);
query.prepare("INSERT INTO CLIENT (ID,NOM,FORME,FAMILLE,DATECREATION,PRIX) "
              "VALUES (:ID, :NOM, :FORME, :FAMILLE, :DATECREATION, :PRIX)");

query.bindValue(":ID", ID);
query.bindValue(":NOM", NOM);
query.bindValue(":FORME", FORME);
query.bindValue(":FAMILLE", FAMILLE);
query.bindValue(":DATECREATION", DATECREATION);
query.bindValue(":PRIX", PRIX);

return    query.exec();
}



QSqlQueryModel * Medicament::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from CLIENT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("FORME"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("FAMILLE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATECREATION"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIX"));
    return model;
}




bool Medicament::supprimer(int ID)
{
QSqlQuery query;
QString res= QString::number(ID);
query.prepare("Delete from CLIENT where ID = :ID ");
query.bindValue(":ID", ID);
return   query.exec();
}
*/
/*
bool Medicament::verifier_existence(int ID)
 {
     QSqlQuery query;
     QString res = QString::number(ID);

     query.prepare("SELECT ID FROM CLIENT WHERE ID = :ID");
     query.bindValue(":ID", res);

     if (query.exec() && query.next())
     {
         return true;
     }
     else
     {
         return false;
     }
 }
*/
bool Medicament::modifier(int ID, QString NOM, QString FORME, QString FAMILLE,QDate DATECREATION ,int PRIX ,int STOCK)
 {
     QSqlQuery query;
     QString res = QString::number(ID);


     QString updateQuery = "UPDATE CLIENT SET  ";
     bool fieldsmodified = false;

     if (!NOM.isEmpty())
     {
         updateQuery += "NOM = :NOM, ";
         fieldsmodified = true;
     }
     if (!FORME.isEmpty())
     {
         updateQuery += "FORME = :FORME, ";
         fieldsmodified = true;
     }


     if (!FAMILLE.isEmpty())
     {
         updateQuery += "FAMILLE = :FAMILLE, ";
         fieldsmodified = true;
     }

     if (!DATECREATION.isNull())
     {
         updateQuery += "DATECREATION = :DATECREATION, ";
         fieldsmodified = true;
     }
     if (PRIX != -1)
     {
         updateQuery += "PRIX = :PRIX, ";
         fieldsmodified = true;
     }


     updateQuery += " WHERE ID = :ID";


     query.prepare(updateQuery);
     query.bindValue(":ID", res);
     if (!NOM.isEmpty())
         query.bindValue(":NOM", NOM);
     else
          query.bindValue(":NOM", NOM);
     if (!FORME.isEmpty())
         query.bindValue(":FORME", FORME);
     else
          query.bindValue(":FORME", FORME);


     if (!FAMILLE.isEmpty())
         query.bindValue(":FAMILLE",FAMILLE);
     else
          query.bindValue(":FAMILLE", FAMILLE);

     if (!DATECREATION.isNull())
         query.bindValue(":DATECREATION", DATECREATION.toString("yyyy-MM-dd"));
     else
          query.bindValue(":DATECREATION",DATECREATION);


     if (PRIX != -1)
         query.bindValue(":PRIX", PRIX);
     else
          query.bindValue(":PRIX",PRIX);


 }
QSqlQueryModel* Medicament::rechercherParForme(QString FORME)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(QString("SELECT * FROM CLIENT WHERE FORME LIKE '%%1%'").arg(FORME));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FORME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("FAMILLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATECREATION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}
QSqlQueryModel* Medicament::rechercherParFamille(QString FAMILLE)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(QString("SELECT * FROM CLIENT WHERE FAMILLE LIKE '%%1%'").arg(FAMILLE));
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FORME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("FAMILLE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATECREATION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}
