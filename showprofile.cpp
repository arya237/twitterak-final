#include "showprofile.h"
#include "ui_showprofile.h"
#include "user.hpp"
#include "QMessageBox"

showprofile::showprofile(user* porpose, user* my, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showprofile)
{
    ui->setupUi(this);
    target = porpose;
    me = my;
    set();
}

showprofile::~showprofile()
{
    delete ui;
}

void showprofile::set()
{
    QString username, name, phone, country, link, followers, birthday;

    bool follow = target->check_follow(me);

    username = QString::fromStdString( '@' + me->get_username());
    ui->lbl_username->setText(username);

    name = QString::fromStdString(me->get_name());
    ui->lbl_name->setText(name);

    country = QString::fromStdString(me->get_country());
    ui->lbl_country->setText(country);

    link = QString::fromStdString(me->get_link());
    ui->lbl_link->setText(link);

    phone = QString::fromStdString(me->get_phonenumber());
    ui->lbl_phone->setText(phone);

    birthday = QString::fromStdString(me->get_birthday());
    ui->lbl_age->setText(birthday);

    followers = QString::number(me->display_followers());
    ui->lbl_follower->setText(followers);

    if(follow)
    {
        ui->btn_follow->setText("unfollow");
    }

    else if(!follow)
    {
        ui->btn_follow->setText("follow");
    }
}



void showprofile::on_btn_follow_clicked()
{
    if(ui->btn_follow->text().toStdString() == "follow")
    {
        target->add_following(me);
        set();
    }

    else if(ui->btn_follow->text().toStdString() == "unfollow")
    {
        target->unfollow(me);
        set();
    }
}
