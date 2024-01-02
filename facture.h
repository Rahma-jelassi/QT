#ifndef FACTURE_H
#define FACTURE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
class Facture
{public:
    Facture();
    Facture(int,QString,QString,QString,int,QString,QString);
    QString get_nom();
    QString get_prenom();
    QString get_date();
    int get_id();
    int get_montant();
    QString get_statut();
    QString get_type();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,int,QString,QString);
    void genererPDF(const QString& filename) const;
    void imprimer(QPrinter *printer) const;

    void verifierRappelPaiement() const;
    bool estEnRetard(const QString& dateFacture, int delai) const;
private:
    QString nom,prenom,date,statut,type;
    int id,montant;
};

#endif

