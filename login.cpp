#include "login.h"
#include "ui_login.h"
#include "twitterak.hpp"
#include <QMessageBox>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_btn_doneloign_clicked()
{
    twitterak a;
       a.read_file();

       a.get_from_file();
       a.get_follower_following_infile();
       a.read_hashtag_fromfile();

       string username, password;
       username = ui->le_username->text().toStdString();
       password = ui->le_password->text().toStdString();

       this->close();
       a.login(username, password);
}

void login::on_pushButton_clicked()
{
    if(ui->le_password->echoMode() == QLineEdit::Password)
    {
        ui->le_password->setEchoMode(QLineEdit::Normal);
    }

    else ui->le_password->setEchoMode(QLineEdit::Password);
}
