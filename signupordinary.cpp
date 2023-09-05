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
    ui->lbl_warning->hide();
    ui->lbl_warningusername->hide();
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


    string username, name, password, link, country,biography, phonenumber, birthday, header, status;
    username = ui->ln_username->text().toStdString();
    name = ui->ln_name->text().toStdString();
    password = ui->ln_password->text().toStdString();
    link = ui->ln_link->text().toStdString();
    country = ui->ln_country->text().toStdString();
    biography = ui->txt_bio->toPlainText().toStdString();//max legnth func
    phonenumber = ui->ln_number->text().toStdString();
    birthday = ui->dateEdit->text().toStdString();
    header = ui->le_header->text().toStdString();

    if(ui->rtbn_public->isChecked())
        status = "public";

    else if(ui->rbtn_private->isChecked())
        status = "private";



    this->close();
    t.ordsignup(username,name,country,phonenumber,link,password,biography, birthday, header, profile, status);
}




void SignupOrdinary::on_ln_password_textChanged(const QString &arg1)
{
    if(ui->ln_password->text().size() < 8)
    {
        ui->lbl_warning->show();
        ui->btn_signup->setEnabled(false);
    }

    else ui->lbl_warning->hide();

    if(!ui->lbl_warning->isVisible())
    {
        ui->btn_signup->setEnabled(true);
    }
}

void SignupOrdinary::on_pushButton_clicked()
{
    profile = QFileDialog::getOpenFileName(this, "open", "picture", "image(*.jpg)").toStdString();
}

bool SignupOrdinary::validateuser(string usernmae)
{
    twitterak t;

    t.read_file();

    if(t.validateusername(usernmae))
    {
        return 1;
    }

    else return 0;
}

bool SignupOrdinary::validatepass(string password)
{
    bool charflag = 0, upcaseflag = 0, lowcaseflag = 0, numflag = 0;

    try
    {

        for(int i : password)
        {
            if((i >= 33 && i <= 47 ) || ( 58 <= i && i <= 64) || i == 32)
            {
                charflag = 1;
            }

            if(i >= 48 && i <= 57)
            {
                numflag = 1;
            }

            if(i >= 65 && i <= 90)
            {
                upcaseflag = 1;
            }

            if(i >= 97 && i <= 122)
            {
                lowcaseflag = 1;
            }
        }

        if(charflag && lowcaseflag && upcaseflag && numflag)
        {
            return 0;
        }

        else throw std::invalid_argument
            ("! Password must have at least 8 digit and lowercaseand uppercase and number and character.");
    }

    catch (invalid_argument &e)
    {
        cout << e.what() << endl;
        return 1;
    }

}

void SignupOrdinary::on_btn_shopassword_clicked()
{
    if(ui->ln_password->echoMode() == QLineEdit::Password)
    {
        ui->ln_password->setEchoMode(QLineEdit::Normal);
    }

    else ui->ln_password->setEchoMode(QLineEdit::Password);
}

void SignupOrdinary::on_ln_username_textChanged(const QString &arg1)
{
    if(validateuser(ui->ln_username->text().toStdString()))
    {
        ui->lbl_warningusername->show();
        ui->btn_signup->setEnabled(false);
    }

    else
    {
        ui->lbl_warningusername->hide();
        ui->btn_signup->setEnabled(true);
    }
}
