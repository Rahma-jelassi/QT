#include "gestion_de_stock.h"
#include "ui_mainwindow.h"

#include "medicament.h"
#include <QMessageBox>

//declaration tmpmedicament
Medicament tmpmedicament;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);
ui->lineEdit_id->setValidator(new QIntValidator(0,99999999, this));


ui->tabmedicament->setModel(tmpmedicament.afficher());

proxyModel = new QSortFilterProxyModel(this); //tri

    proxyModel->setSourceModel(tmpmedicament.afficher());

    ui->tabmedicament->setModel(proxyModel);
    ui->tabmedicament->setSortingEnabled(true);
    ui->tabmedicament->update();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int ID = ui->lineEdit_id->text().toInt();
    QString NOM= ui->lineEdit_nom->text();
    QString FORME= ui->lineEdit_forme->text();
    QString FAMILLE= ui->lineEdit_famille->text();
    QDate DATECREATION= ui->dateEdit->date();
    int PRIX = ui->lineEdit_prix->text().toInt();
    int STOCK = ui->lineEdit_stock->text().toInt();

  Medicament e(ID,NOM,FORME,FAMILLE,DATECREATION,PRIX,STOCK);
  bool test=e.ajouter();
  if(test)
{

      ui->tabmedicament->setModel(tmpmedicament.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un medicament"),
                  QObject::tr("medicament ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un medicament"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_clicked()
{
int ID = ui->lineEdit_id->text().toInt();
bool test=tmpmedicament.supprimer(ID);
if(test)
{ui->tabmedicament->setModel(tmpmedicament.afficher());//refresh
    QMessageBox::information(nullptr, QObject::tr("Supprimer un medicament"),
                QObject::tr("medicament supprimé.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("Supprimer un medicament"),
                QObject::tr("Erreur !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_modifier_clicked()
{
    int ID = ui->lineEdit ->text().toInt();
    QString NOM = ui->lineEdit_2 ->text();
    QString FORME = ui->lineEdit_3 ->text();
    QString FAMILLE = ui->lineEdit_4 ->text();
    QDate DATECREATION = ui->dateEdit ->date();
    int PRIX = ui->lineEdit_5 ->text().toInt();
    int STOCK = ui->lineEdit_5 ->text().toInt();


    bool updateSuccess = tmpmedicament.modifier(ID, NOM, FORME, FAMILLE, DATECREATION ,PRIX,STOCK);

    if (updateSuccess)
    {
        ui->tabmedicament->setModel(tmpmedicament.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {

        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectuée.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
/*
void MainWindow::on_pb_forme_clicked()
{
    QString FORME = ui->lineEdit_6->text();
    ui->tabmedicament->setModel(tmpmedicament.rechercherParForme(FORME));
}
void MainWindow::on_pb_famille_clicked()
{
    QString FAMILLE = ui->lineEdit_7->text();
    ui->tabmedicament->setModel(tmpmedicament.rechercherParFamille(FAMILLE));
}
*/


void MainWindow::on_pb_forme_clicked()
{
    QString forme = ui->lineEdit_forme->text();

    // Filtrez par la colonne appropriée pour la recherche par forme
    proxyModel->setFilterKeyColumn(2);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterFixedString(forme);

    ui->lineEdit_forme->clear();
    ui->tableView_2->setModel(proxyModel);
}


void MainWindow::on_pb_famille_clicked()
{
    QString famille = ui->lineEdit_famille->text();

    // Filtrez par la colonne appropriée pour la recherche par famille
    proxyModel->setFilterKeyColumn(4);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterFixedString(famille);

    ui->lineEdit_famille->clear();
    ui->tableView_2->setModel(proxyModel);
}
