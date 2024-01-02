#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "facture.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTimer>
#include <QtSql>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialisation des widgets
    lineEditNom = ui->lineEditNom;
    lineEditPrenom = ui->lineEditPrenom;
    lineEditDate = ui->lineEditDate;
    lineEdit_date = ui->lineEdit_date;
    lineEdit_montant = ui->lineEdit_montant;

    proxyModel = new QSortFilterProxyModel(this); //tri

    proxyModel->setSourceModel(tmpfacture.afficher());

    ui->tabfacture->setModel(proxyModel);
    ui->tabfacture->setSortingEnabled(true);
    ui->tabfacture->update();
    // QTimer pour vérifier les rappels de paiement toutes les 24 heures
    QTimer *timerRappelPaiement = new QTimer(this);
    connect(timerRappelPaiement, &QTimer::timeout, this, &MainWindow::verifierRappelPaiement);
    timerRappelPaiement->start(24 * 60 * 60 * 1000); // Vérifier une fois par jour
}

    MainWindow::~MainWindow()
    {
        delete ui;
    }

    void MainWindow::on_pb_ajouter_clicked()
    {
        int id = ui->lineEdit_id->text().toInt();
        QString nom= ui->lineEdit_nom->text();
        QString prenom= ui->lineEdit_prenom->text();
        QString date = ui->lineEdit_date->text();
        int montant=ui->lineEdit_montant->text().toInt();
        QString statut = ui->lineEdit_Statut->text();
        QString type = ui->lineEdit_Type->text();
      Facture e(id,nom,prenom,date,montant,statut,type);
      bool test=e.ajouter();
      if(test)
    {
          proxyModel->setSourceModel(tmpfacture.afficher());
          proxyModel->invalidate();

    QMessageBox::information(nullptr, QObject::tr("Ajouter une facture"),
                      QObject::tr("Facture ajouté.\n"
                                  "Click ok to exit."), QMessageBox::Ok);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter une facture"),
                      QObject::tr("Erreur !.\n"
                                  "Click ok to exit."), QMessageBox::Ok);

       ui->lineEdit_id->clear();
       ui->lineEdit_nom->clear();
       ui->lineEdit_prenom->clear();
       ui->lineEdit_date->clear();
       ui->lineEdit_montant->clear();
       ui->lineEdit_Statut->clear();
       ui->lineEdit_Type->clear();
       //pour qu'apres avoir ecrire dans le champ l'info s'efface

    }

    void MainWindow::on_pb_supprimer_clicked()
    {
    int id = ui->lineEdit_id_2->text().toInt();
    bool test=tmpfacture.supprimer(id);
    if(test)
    {proxyModel->setSourceModel(tmpfacture.afficher());
        proxyModel->invalidate();
        QMessageBox::information(nullptr, QObject::tr("Supprimer une facture"),
                                 QObject::tr("Supression faite !.\n"
                                             "Click ok to exit."), QMessageBox::Ok);}
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une facture"),
                    QObject::tr("Erreur !.\n"
                                "Click ok to exit."), QMessageBox::Ok);

    ui->lineEdit_id_2->clear(); //pour qu'apres avoir ecrire dans le champ l'info s'efface

    }




void MainWindow::on_pb_ajouter_3_clicked()
{
    {
        // Récupération des valeurs à partir des champs de l'interface
        int id = ui->idUp->text().toInt();
        int montant = ui->montantUp->text().toInt();

        QString nom = ui->nomUp->text() ;
        QString prenom =ui->prenomUp->text();
        QString date=ui->dateUp->text();
        QString statut=ui->statutUp->text();
        QString type=ui->typeUp->text();




        // Effectuer la modification
        bool test = tmpfacture.modifier(id, nom, prenom,date,montant,statut,type);

        // Affichage du résultat de la modification
        if(test) {
            proxyModel->setSourceModel(tmpfacture.afficher()); // Update the source model
            proxyModel->invalidate();
            QMessageBox::information(nullptr, QObject::tr("Modifier une facture"),
                                     QObject::tr("Modification réussie !\n"
                                                 "Cliquez sur ok pour quitter."), QMessageBox::Ok);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Modifier une facture"),
                        QObject::tr("Erreur lors de la modification.\n"
                                    "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        }
}   ui->idUp->clear();
    ui->montantUp->clear();
    ui->nomUp->clear();//pour qu'apres avoir ecrire dans le champ l'info s'efface
    ui->prenomUp->clear();
    ui->dateUp->clear();
    ui->statutUp->clear();
    ui->typeUp->clear();
}


 //code recherche


void MainWindow::on_pushButton_clicked()
{

    QString ongletCourant = ui->TabwidgetN->tabText(ui->TabwidgetN->currentIndex());
    QString nom = ui->lineEditNom->text();
     QString prenom = ui->lineEditPrenom->text();
       QString date = ui->lineEditDate->text();

    QString columnName;

    if (ongletCourant == "NOM") {
        proxyModel->setFilterKeyColumn(1);
        proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxyModel->setFilterFixedString(nom);}
     if (ongletCourant == "PRENOM") {
             proxyModel->setFilterKeyColumn(2);
             proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
             proxyModel->setFilterFixedString(prenom);}
     if (ongletCourant == "DATE") {
             proxyModel->setFilterKeyColumn(3);
             proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
             proxyModel->setFilterFixedString(date);}
     ui->lineEditNom->clear();
     ui->lineEditPrenom->clear();//pour qu'apres avoir ecrire dans le champ l'info s'efface
     ui->lineEditDate->clear();
}
//    //////////////////////////////////////////metier generer fichier pdf

void MainWindow::on_pushButton_2_clicked()
{
    // Récupérer les données de la facture
    int id = ui->idUp->text().toInt();
    int montant = ui->montantUp->text().toInt();
    QString nom = ui->nomUp->text();
    QString prenom = ui->prenomUp->text();
    QString date = ui->dateUp->text();
    QString Statut = ui->statutUp->text();
    QString type = ui->typeUp->text();

    // Créer une instance de la classe Facture avec les données récupérées
    Facture facture(id, nom, prenom, date, montant,Statut,type);

    // Générer le fichier PDF avec un nom de fichier dynamique basé sur l'identifiant
    QString filename = QString("D:/generation_fichier_pdf_qt/Facture_%1.pdf").arg(id);
    facture.genererPDF(filename);

    // Afficher un message à l'utilisateur
    QMessageBox::information(this, "Génération PDF", "Le fichier PDF a été généré avec succès !");
}
//bouton impression Impression

void MainWindow::on_pushButton_3_clicked()
{
    // Sélectionner une imprimante
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Accepted) {
        // Appeler la fonction imprimer avec l'objet QPrinter
        tmpfacture.imprimer(&printer);

        // Informer l'utilisateur que l'impression a réussi
        QMessageBox::information(this, "Impression", "L'impression a été réalisée avec succès !");
    }
}
//notification
void MainWindow::verifierRappelPaiement()
{
    // Appel de la fonction vérifiant les rappels de paiement dans la classe Facture
    tmpfacture.verifierRappelPaiement();
}

void MainWindow::on_pushButton_4_clicked()//boutton notifier
{
    qDebug() << "Bouton de notification cliqué.";
    // Appel de la fonction vérifiant les rappels de paiement
    tmpfacture.verifierRappelPaiement();
}
