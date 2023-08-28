#include "signupordinary.h"
#include "ui_signupordinary.h"
#include "chooseaccount.h"
#include "twitterak.hpp"
#include "qfiledialog.h"

SignupOrdinary::SignupOrdinary(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignupOrdinary)
{
    ui->setupUi(this);
    //ui->lbl_warning->hide();
}

SignupOrdinary::~SignupOrdinary()
{
    delete ui;
}

void SignupOrdinary::on_btn_back_clicked()
{
    this->close();
    ChooseAccount *a = new ChooseAccount;
    a->show();
}

void SignupOrdinary::on_btn_signup_clicked()
{
    twitterak t;
    t.read_file();
    t.get_from_file();
    t.get_follower_following_infile();
    t.read_hashtag_fromfile();


    string username, name, password, link, country,biography, phonenumber, birthday, header;
    username = ui->ln_username->text().toStdString();
    name = ui->ln_name->text().toStdString();
    password = ui->ln_password->text().toStdString();
    link = ui->ln_link->text().toStdString();
    country = ui->ln_country->text().toStdString();
    biography = ui->txt_bio->toPlainText().toStdString();//max legnth func
    phonenumber = ui->ln_number->text().toStdString();
    birthday = ui->dateEdit->text().toStdString();
    header = ui->le_header->text().toStdString();


    this->close();
    t.ordsignup(username,name,country,phonenumber,link,password,biography, birthday, header, profile);
}




void SignupOrdinary::on_ln_password_textChanged(const QString &arg1)
{
//    if(ui->ln_password->text().size() < 8)
//    {
//        ui->lbl_warning->show();
//        ui->btn_signup->setEnabled(false);
//    }

//    else ui->lbl_warning->hide();

//    if(!ui->lbl_warning->isVisible())
//    {
//        ui->btn_signup->setEnabled(true);
//    }
}

void SignupOrdinary::on_pushButton_clicked()
{
    profile = QFileDialog::getOpenFileName(this, "open", "picture", "image(*.jpg)").toStdString();
}
