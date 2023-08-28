#include "signuporganization.h"
#include "ui_signuporganization.h"
#include "chooseaccount.h"
#include "twitterak.hpp"
SignupOrganization::SignupOrganization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignupOrganization)
{
    ui->setupUi(this);
}

SignupOrganization::~SignupOrganization()
{
    delete ui;
}

void SignupOrganization::on_btn_back_clicked()
{
    this->close();
    ChooseAccount *a = new ChooseAccount;
    a->show();
}

void SignupOrganization::on_btn_signup_clicked()
{
    twitterak t;
    t.read_file();
    t.get_follower_following_infile();
    t.get_from_file();
    t.read_hashtag_fromfile();

    string username, name, password, link, country,biography, phonenumber, header;
    username = ui->ln_username->text().toStdString();
    name = ui->ln_name->text().toStdString();
    password = ui->ln_password->text().toStdString();
    link = ui->ln_link->text().toStdString();
    country = ui->ln_country->text().toStdString();
    biography = ui->txt_bio->toPlainText().toStdString();//max legnth func
    phonenumber = ui->ln_phonenumber->text().toStdString();
    header = ui->le_header->text().toStdString();


    this->close();
    t.signup(username,name,country,phonenumber,link,password,biography, header, profile);

}




