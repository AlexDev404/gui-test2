#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QMainWindow>
#include <QDebug>
int maxCID = 0; // Used to check to see if we're updating a row


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qMain();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Initialization code
void MainWindow::qMain(){
    QSqlQuery query;
    // Get the maximum cID value from the customer table
    query.exec("SELECT MAX(cID) FROM customer;");
    if (query.next()) {
        maxCID = query.value(0).toInt();
    }
}


// Top row
void MainWindow::on_connect_clicked()
{
    // Use the SQL driver
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("data");
    db.setUserName("root");
    db.setPassword("root");
    db.open();

    qDebug() << db.lastError().text();
}


void MainWindow::on_view_data_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM customer");
    ui->tableView->setModel(model);

}

// Bottom row
void MainWindow::on_insert_record_clicked()
{
    QSqlQuery query;

    // Get the maximum cID value from the customer table
    query.exec("SELECT MAX(cID) FROM customer;");
    if (query.next()) {
        maxCID = query.value(0).toInt();
    }


    query.prepare(QString::fromLatin1("INSERT INTO customer ()")
                  + QString::fromLatin1("VALUES (:cId, :c_name, :c_cname, :c_email, :c_cell);"));
    query.bindValue(":cID", maxCID);
    query.bindValue(":c_name", ui->c_name->text());
    query.bindValue(":c_cname", ui->c_cname->text());
    query.bindValue(":c_email", ui->c_email->text());
    query.bindValue(":c_cell", ui->c_cell->text());
    query.exec();

}

void MainWindow::on_delete_record_clicked()
{
    QSqlQuery query;
    // Get the selected indexes
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    // Remove the corresponding rows from the model
    for (const QModelIndex &index : selectedIndexes) {
        int row = index.row(); // Get the row number
        model->removeRow(row);
        query.prepare("DELETE FROM customer WHERE cID = :cID");
        query.bindValue(":cID", model->data(model->index(row, 0))); // Since column 0 contains the cID
    }
    query.exec(); // Execute
}

// Event listeners
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    // Ensure that the clicked index is valid
    if (index.isValid()) { // Set the fields for editingx
        maxCID = model->data(model->index(index.row(), 0)).toInt();
        ui->c_name->setText(model->data(model->index(index.row(), 1)).toString());
        ui->c_cname->setText(model->data(model->index(index.row(), 2)).toString());
        ui->c_email->setText(model->data(model->index(index.row(), 3)).toString());
        ui->c_cell->setText(model->data(model->index(index.row(), 4)).toString());
    }
}
