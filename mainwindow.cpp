#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto result = botan_version();
    ui->version_label->setText(result.vector[0]);
    clean_result(result);
    auto address = get_server();
    ui->address_label->setText(address.vector[0]);
    clean_result(address);
    ui->text_area->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_list_button_clicked()
{
    bool ok;
    auto password = QInputDialog::getText(this, "Password Input", "Password:", QLineEdit::Password, "", &ok).toStdString();
    if (ok && !password.empty()) {
        auto result = fetch_list(password.c_str());
        ui->text_area->clear();
        QTextCursor cursor(ui->text_area->document());
        cursor.beginEditBlock();
        for(size_t i = 0; i < result.length; ++i) {
            cursor.insertText(result.vector[i]);
            if(i != result.length - 1) cursor.insertText("\n");
        }
        cursor.endEditBlock();
        clean_result(result);
    }
}

void MainWindow::on_fetch_button_clicked()
{
    bool ok0;
    auto name = QInputDialog::getText(this, "Name Input", "Name:", QLineEdit::Normal, "", &ok0).toStdString();
    if (!ok0) return;
    bool ok1;
    auto password = QInputDialog::getText(this, "Password Input", "Password:", QLineEdit::Password, "", &ok1).toStdString();
    if (ok1 && !name.empty() && !password.empty()) {
        auto result = fetch_password(name.c_str(), password.c_str());
        ui->text_area->clear();
        if (result.length == 0) {
            ui->text_area->setText("fetch error");
        } else {
            ui->text_area->setText(result.vector[0]);
        }
        clean_result(result);
    }
}



void MainWindow::on_add_button_clicked()
{
    bool ok0;
    auto name = QInputDialog::getText(this, "Name Input", "Name:", QLineEdit::Normal, "", &ok0).toStdString();
    if (!ok0) return;
    bool ok1;
    auto content = QInputDialog::getText(this, "Password Input", "Content:", QLineEdit::Password, "", &ok1).toStdString();
    if (!ok1) return;
    bool ok2;
    auto password = QInputDialog::getText(this, "Password Input", "Password:", QLineEdit::Password, "", &ok2).toStdString();
    if (ok2 && !name.empty() && !content.empty() && !password.empty()) {
        auto result = add_password(name.c_str(), content.c_str(), password.c_str());
        ui->text_area->clear();
        if (result.length == 0) {
            ui->text_area->setText("add error");
        } else {
            ui->text_area->setText(result.vector[0]);
        }
        clean_result(result);
    }
}

void MainWindow::on_delete_button_clicked()
{
    bool ok0;
    auto name = QInputDialog::getText(this, "Name Input", "Name:", QLineEdit::Normal, "", &ok0).toStdString();
    if (!ok0 || name.empty()) return;
    auto name2 = QInputDialog::getText(this, "Name Input", "Retype:", QLineEdit::Normal, "", &ok0).toStdString();
    if (!ok0 || name != name2) return;
    auto password = QInputDialog::getText(this, "Password Input", "Password:", QLineEdit::Password, "", &ok0).toStdString();
    if (ok0 && !password.empty()) {
        auto result = delete_password(name.c_str(), password.c_str());
        ui->text_area->clear();
        if (result.length == 0) {
            ui->text_area->setText("delete error");
        } else {
            ui->text_area->setText(result.vector[0]);
        }
        clean_result(result);
    }
}

void MainWindow::on_generate_button_clicked()
{
    bool ok0;
    auto name = QInputDialog::getText(this, "Name Input", "Name:", QLineEdit::Normal, "", &ok0).toStdString();
    if (!ok0 || name.empty()) return;
    auto password = QInputDialog::getText(this, "Password Input", "Password:", QLineEdit::Password, "", &ok0).toStdString();
    if (ok0 && !password.empty()) {
        auto result = generate_password(name.c_str(), password.c_str());
        ui->text_area->clear();
        if (result.length == 0) {
            ui->text_area->setText("generate error");
        } else {
            ui->text_area->setText(result.vector[0]);
        }
        clean_result(result);
    }
}
