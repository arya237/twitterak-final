#include "signupanonymous.h"
#include "ui_signupanonymous.h"
#include "chooseaccount.h"
#include "twitterak.hpp"

SignupAnonymous::SignupAnonymous(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignupAnonymous)
{
    ui->setupUi(this);
}

SignupAnonymous::~SignupAnonymous()
{
    delete ui;
}

void SignupAnonymous::on_btn_back_clicked()
{
    this->close();
    ChooseAccount *a = new ChooseAccount;
    a->show();
}

void SignupAnonymous::on_btn_signup_clicked()
{
    twitterak t;
    t.read_file();
    t.get_from_file();
    t.get_follower_following_infile();
    t.read_hashtag_fromfile();

    string username , password ;
    username = ui->ln_username->text().toStdString();
    password = ui->ln_password->text().toStdString();

    this->close();
    t.anonymoussignup(username,password);

}
