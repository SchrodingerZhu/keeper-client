#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSettings>
#include <keeper.h>
#include <QInputDialog>
#include <QClipboard>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_list_button_clicked();

    void on_fetch_button_clicked();

    void on_add_button_clicked();

    void on_delete_button_clicked();

    void on_generate_button_clicked();

private:
    Ui::MainWindow *ui;
    size_t counter = 0;

};
#endif // MAINWINDOW_H
