#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void qMain();

private slots:


    void on_view_data_clicked();

    void on_connect_clicked();

    void on_insert_record_clicked();

    void on_delete_record_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
};
#endif // MAINWINDOW_H
