#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chooseaccount.h"
#include "login.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_signup_clicked()
{
    ChooseAccount *a = new ChooseAccount(this);
    a->show();
}

void MainWindow::on_btn_login_clicked()
{
    login *l = new login;
    l->show();
}

void MainWindow::on_btn_exit_clicked()
{
    this->close();
}
