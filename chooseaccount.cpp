#include "chooseaccount.h"
#include "ui_chooseaccount.h"
#include "signupordinary.h"
#include "signuporganization.h"
#include "signupanonymous.h"
#include "mainwindow.h"
ChooseAccount::ChooseAccount(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseAccount)
{
    ui->setupUi(this);
}

ChooseAccount::~ChooseAccount()
{
    delete ui;
}

void ChooseAccount::on_btn_ord_clicked()
{
    this->close();
    SignupOrdinary *o = new SignupOrdinary;
    o->show();
}

void ChooseAccount::on_btn_org_clicked()
{
    this->close();
    SignupOrganization *o = new SignupOrganization;
    o->show();
}

void ChooseAccount::on_btn_anon_clicked()
{
    this->close();
    SignupAnonymous *o = new SignupAnonymous;
    o->show();
}


void ChooseAccount::on_btn_back_clicked()
{
    this->close();
        MainWindow *m = new MainWindow;
        m->show();
}
