#include "signuporganization.h"
#include "ui_signuporganization.h"
#include "chooseaccount.h"
#include "twitterak.hpp"
#include "QValidator"
#include "QFileDialog"
#include "QMessageBox"

SignupOrganization::SignupOrganization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignupOrganization)
{
    ui->setupUi(this);

    ui->lbl_warning->hide();
    ui->lbl_warningusername->hide();
    ui->lbl_ceowarning->hide();

    ui->ln_phonenumber->setValidator(new QIntValidator(this));
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

    string username, name, password, link, country,biography, phonenumber, header, status;
    username = ui->ln_username->text().toStdString();
    name = ui->ln_name->text().toStdString();
    password = ui->ln_password->text().toStdString();
    link = ui->ln_link->text().toStdString();
    country = ui->ln_country->text().toStdString();
    biography = ui->txt_bio->toPlainText().toStdString();
    phonenumber = ui->ln_phonenumber->text().toStdString();
    header = ui->le_header->text().toStdString();

    if(ui->rbtn_public->isChecked())
        status = "public";

    else if(ui->rbtn_private->isChecked())
        status = "private";

    this->close();
    t.signup(username,name,country,phonenumber,link,password,biography, header,profile, status);

}

bool SignupOrganization::validatepass(string password)
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


void SignupOrganization::on_ln_password_textChanged(const QString &arg1)
{
    if(validatepass(ui->ln_password->text().toStdString()))
    {
        ui->lbl_warning->show();
        ui->btn_signup->setEnabled(false);
    }

    else
    {
        ui->lbl_warning->hide();
        ui->btn_signup->setEnabled(true);
    }
}


bool SignupOrganization::validateuser(string username)
{
    twitterak t;

    t.read_file();

    if(t.validateusername(username))
    {
        return 1;
    }

    else return 0;
}

void SignupOrganization::on_ln_username_textChanged(const QString &arg1)
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


void SignupOrganization::on_btn_profile_clicked()
{
    profile = QFileDialog::getOpenFileName(this, "open", "picture", "image(*.jpg)").toStdString();
}

void SignupOrganization::on_lineEdit_3_textChanged(const QString &arg1)
{
    if(validateuser(ui->lineEdit_3->text().toStdString()))
    {
        ui->lbl_ceowarning->hide();
        ui->btn_signup->setEnabled(true);
    }

    else
    {
        ui->lbl_ceowarning->show();
        ui->btn_signup->setEnabled(false);
    }
}



void SignupOrganization::on_txt_bio_textChanged()
{
    string t = ui->txt_bio->toPlainText().toStdString();
    if(t.size()>1100)
    {
        ui->txt_bio->textCursor().deletePreviousChar();
    }
}

void SignupOrganization::on_btn_showpassword_clicked()
{

    if(ui->ln_password->echoMode() == QLineEdit::Password)
    {
        ui->ln_password->setEchoMode(QLineEdit::Normal);
    }

    else ui->ln_password->setEchoMode(QLineEdit::Password);
}
