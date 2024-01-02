#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "facture.h"
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pb_ajouter_clicked();//boutton ajout

    void on_pb_supprimer_clicked();//boutton supprimer




    void on_pb_ajouter_3_clicked();//boutton modifier

    void on_pushButton_clicked();//boutton recherche



    void on_pushButton_2_clicked(); //boutton pdf

    void on_pushButton_3_clicked(); //boutton impression


    void verifierRappelPaiement();


    void on_pushButton_4_clicked();//boutton notifier

private:
    Ui::MainWindow *ui;
    Facture tmpfacture;
    QSortFilterProxyModel *proxyModel; //variable du tri
    QLineEdit *lineEditNom;
    QLineEdit *lineEditPrenom;
    QLineEdit *lineEditDate;
    void updateTabWidget();
    QLineEdit *lineEdit_id;
    QLineEdit *lineEdit_nom;
    QLineEdit *lineEdit_prenom;
    QLineEdit *lineEdit_date;
    QLineEdit *lineEdit_montant;
    QLineEdit lineEdit_statut;
    QLineEdit lineEdit_type;
    void imprimerFacture(QPrinter *printer);


};

#endif

