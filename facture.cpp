#include "facture.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QTextDocument>
#include <QPdfWriter>
#include <QPainter>
#include <QDir>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QMessageBox>
#include <QDate>


Facture::Facture()
{
id=0;
nom="";
prenom="";
date="";
montant=0;
statut="";
type="";
}
Facture::Facture(int id,QString nom,QString prenom,QString date,int montant,QString statut,QString type)
{
  this->id=id;
  this->nom=nom;
  this->prenom=prenom;
  this->date=date;
  this->montant=montant;
  this->statut=statut;
  this->type=type;
}
QString Facture::get_nom(){return  nom;}
QString Facture::get_prenom(){return prenom;}
int Facture::get_id(){return  id;}
QString Facture::get_date(){return  date;}
int Facture::get_montant(){return  montant;}
QString Facture::get_statut(){return  statut;}
QString Facture::get_type(){return  type;}

bool Facture::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO FACTURES (IDENTIFIANT, NOM, PRENOM, DATEE ,MONTANT,STATUT_DE_PAIEMENT,TYPE_DE_PAIMENT) "
                    "VALUES (:id, :nom, :prenom, :date, :montant, :statut, :type)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":date", date);
query.bindValue(":montant", montant);
query.bindValue(":statut", statut);
query.bindValue(":type", type);

return    query.exec();
}

QSqlQueryModel * Facture::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from FACTURES");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("MONTANT"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("STATUT_DE_PAIEMENT"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("TYPE_DE_PAIMENT"));

    return model;
}

bool Facture::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from FACTURES where IDENTIFIANT = :id ");
query.bindValue(":id", res);
return    query.exec();
}
bool Facture::modifier(int id,QString n,QString p,QString d,int m,QString s,QString t){
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Update FACTURES set  NOM=:nom, PRENOM=:prenom, DATEE=:date, MONTANT=:montant, STATUT_DE_PAIEMENT=:statut, TYPE_DE_PAIMENT=:type where IDENTIFIANT=:id ");
query.bindValue(":id", res);
query.bindValue(":nom", n);
query.bindValue(":prenom", p);
query.bindValue(":date", d);
query.bindValue(":montant", m);
query.bindValue(":statut", s);
query.bindValue(":type", t);
return    query.exec();

}
//pdf
void Facture::genererPDF(const QString& filename) const
{
    QPdfWriter writer(filename);
    writer.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter(&writer);

    int i = 4000;
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 30));
        painter.drawText(1100, 1200, "FACTURES");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 14));
        painter.drawRect(100, 100, 7300, 2600);
        painter.drawRect(0, 3000, 9600, 500);
        painter.setFont(QFont("Arial", 8));
        painter.drawText(300, 3300, "IDENTIFIANT");
        painter.drawText(1300, 3300, "NOM");
        painter.drawText(2200, 3300, "PRENOM");
        painter.drawText(3200, 3300, "DATE ");
        painter.drawText(4700, 3300, "MONTANT");
        painter.drawText(6200, 3300, "STATUT_DE_PAIEMENT");
        painter.drawText(8000, 3300, "TYPE_DE_PAIMENT");

        QSqlQuery query;
        query.prepare("select * from FACTURES");
        query.exec();
        while (query.next()) {
            painter.drawText(300, i, query.value(0).toString());
            painter.drawText(1300, i, query.value(1).toString());
            painter.drawText(2200, i, query.value(2).toString());
            painter.drawText(3200, i, query.value(3).toString());
            painter.drawText(4700, i, query.value(4).toString());
            painter.drawText(6200, i, query.value(5).toString());
            painter.drawText(8000, i, query.value(6).toString());

            i = i + 500;
        }

    painter.end();
}
//impression
void Facture::imprimer(QPrinter *printer) const

{
    QPainter painter(printer);

    // Ajuster la taille de la page pour le format A4
    printer->setPageSize(QPageSize(QPageSize::A4));

    int i = 4000;
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(1100, 1200, "FACTURES");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14));
    painter.drawRect(100, 100, 8000, 2600);
    painter.drawRect(0, 3000, 9600, 500);

    painter.setFont(QFont("Arial", 8));
    painter.drawText(300, 3300, "IDENTIFIANT");
    painter.drawText(1300, 3300, "NOM");
    painter.drawText(2200, 3300, "PRENOM");
    painter.drawText(3200, 3300, "DATE ");
    painter.drawText(4700, 3300, "MONTANT");
    painter.drawText(6200, 3300, "STATUT_DE_PAIEMENT");
    painter.drawText(7700, 3300, "TYPE_DE_PAIMENT");

    QSqlQuery query;
    query.prepare("select * from FACTURES");
    query.exec();
    while (query.next()) {
        painter.drawText(300, i, query.value(0).toString());
        painter.drawText(1300, i, query.value(1).toString());
        painter.drawText(2200, i, query.value(2).toString());
        painter.drawText(3200, i, query.value(3).toString());
        painter.drawText(4700, i, query.value(4).toString());
        painter.drawText(6200, i, query.value(5).toString());
        painter.drawText(7700, i, query.value(6).toString());
        i = i + 500;
    }
}
//notification
void Facture::verifierRappelPaiement() const
{
    QSqlQuery query("SELECT * FROM FACTURES WHERE STATUT_DE_PAIEMENT = 'impaye'");
    while (query.next())
    {
        QString dateFacture = query.value("DATEE").toString();

        //  notification si la facture est en retard de 30 jours
        if (estEnRetard(dateFacture, 20))
        {
            QString message = "Rappel de paiement pour la facture #" + query.value("IDENTIFIANT").toString();
            QMessageBox::warning(nullptr, "Rappel de paiement", message);
        }
    }
}

bool Facture::estEnRetard(const QString& dateFacture, int delai) const
{
    QDate dateFactureObj = QDate::fromString(dateFacture, "dd/MM/yy");
    QDate dateActuelle = QDate::currentDate();
    return dateFactureObj.addDays(delai) < dateActuelle;
}
