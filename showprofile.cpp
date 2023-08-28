#include "showprofile.h"
#include "ui_showprofile.h"
#include "user.hpp"
#include "QMessageBox"
#include "fstream"

showprofile::showprofile(user* target, user* currentuser, unordered_map<string, user*> &users, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showprofile)
{
    ui->setupUi(this);
    this->target = target;
    this->currentuser = currentuser;
    this->users = users;
    set();
}

showprofile::~showprofile()
{
    delete ui;
}

void showprofile::set()
{
    QString username, name, phone, country, link, followers, birthday;

    bool follow = currentuser->check_follow(target);

    username = QString::fromStdString( '@' + target->get_username());
    ui->lbl_username->setText(username);

    name = QString::fromStdString(target->get_name());
    ui->lbl_name->setText(name);

    country = QString::fromStdString(target->get_country());
    ui->lbl_country->setText(country);

    link = QString::fromStdString(target->get_link());
    ui->lbl_link->setText(link);

    phone = QString::fromStdString(target->get_phonenumber());
    ui->lbl_phone->setText(phone);

    birthday = QString::fromStdString(target->get_birthday());
    ui->lbl_age->setText(birthday);

    followers = QString::number(target->display_followers());
    ui->lbl_follower->setText(followers);

    if(follow)
    {
        ui->btn_follow->setText("unfollow");
    }

    else if(!follow)
    {
        ui->btn_follow->setText("follow");
    }

    if(target->get_image() != "" && target->get_image() != "_")
    {
        QImage image(QString::fromStdString(target->get_image()));

        QImage image2 = image.scaled(1920, 1080, Qt::KeepAspectRatio);

        ui->lbl_profile->setPixmap(QPixmap::fromImage(image2));
        ui->lbl_profile->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        ui->lbl_profile->setFixedSize(50, 50);
        QRegion *region = new QRegion(0, 0, ui->lbl_profile->width(), ui->lbl_profile->height(), QRegion::Ellipse);
        ui->lbl_profile->setScaledContents(true);
        ui->lbl_profile->setMask(*region);

    }

    if(target->get_header() != "" && target->get_header() != "_")
    {
        ui->image_profile->setStyleSheet("background-color: " + QString::fromStdString(target->get_header()));
    }

    if(target->get_tweet() != 0)
    {
        ui->listwidget_tweets->clear();

        for(int i = 1; i <= target->get_tweet(); i++)
        {
            QString item =  QString::number((i)) + QString::fromStdString((": " + target->get_tweet(i)->get_post()) + '\n'
            + target->get_tweet(i)->get_date() + '\n') + QString::fromStdString("likes: ") + QString::number(target->get_tweet(i)->show_likes());

            ui->listwidget_tweets->addItem(item);
        }
    }
}



void showprofile::on_btn_follow_clicked()
{
    if(ui->btn_follow->text().toStdString() == "follow")
    {
        currentuser->add_following(target);
        store_follower_following_infile();
        set();

    }

    else if(ui->btn_follow->text().toStdString() == "unfollow")
    {
        currentuser->unfollow(target);
        store_follower_following_infile();
        set();
    }
}

void showprofile::store_follower_following_infile()
{
    fstream ufile;
    bool flag = 1;

    ufile.open("follow.txt", ios::out);

    for(auto i : users)
    {
        if(i.second->display_followers() != 0)
        {
            if(flag)
            {
                ufile << i.second->get_username() << '\n';
                flag = 0;
            }

            else ufile << '\n' << i.second->get_username() << '\n';

            ufile << "followers: ";

            for(int j = 0; j < i.second->display_followers(); j++)
            {
                ufile << i.second->get_followers(j) << " ";
            }

            ufile << "\n";
            ufile << "--------------------";
        }
    }

    ufile.close();
}
