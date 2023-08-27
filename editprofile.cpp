#include "editprofile.h"
#include "ui_editprofile.h"
#include "ordinaryuser.hpp"
#include "orguser.hpp"
#include "anonymous.hpp"
#include "fstream"
#include "user.hpp"
#include "menu.h"

editprofile::editprofile(unordered_map<string, user*> &porpose, user* target, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::editprofile)
{
    ui->setupUi(this);
    currentuser = target;
    users = porpose;
    Default();
    AccountType();

}

editprofile::~editprofile()
{
    delete ui;
}

void editprofile::Default()
{
    ui->ln_username->setText(QString::fromStdString(currentuser->get_username()));
    ui->ln_password->setText(QString::fromStdString(currentuser->get_password()));
    ui->ln_link->setText(QString::fromStdString(currentuser->get_link()));
    ui->txt_bio->setText(QString::fromStdString(currentuser->get_biography()));
    ui->ln_number->setText(QString::fromStdString(currentuser->get_phonenumber()));
    ui->ln_country->setText(QString::fromStdString(currentuser->get_country()));
    ui->le_header->setText(QString::fromStdString(currentuser->get_header()));
    ui->ln_name->setText(QString::fromStdString(currentuser->get_name()));
}

void editprofile::AccountType()
{
    ordinaryuser *ordinary = nullptr;
    orguser *organization = nullptr;
    anonymous *Anonymous = nullptr;

    QString account;

    if((ordinary = dynamic_cast<ordinaryuser*>(currentuser)) != NULL)
    {
        ui->lbl_chief->setEnabled(false);
        ui->ln_chief->setEnabled(false);
    }

    if((organization = dynamic_cast<orguser*>(currentuser)) != NULL)
    {
         ui->dateEdit->setEnabled(false);
         ui->lbl_birthdate->setEnabled(false);
    }

     if((Anonymous = dynamic_cast<anonymous*>(currentuser)) != NULL)
     {
         ui->lbl_bio->setEnabled(false);
         ui->txt_bio->setEnabled(false);
         ui->ln_link->setEnabled(false);
         ui->lbl_link->setEnabled(false);
         ui->ln_name->setDisabled(true);
         ui->ln_country->setEnabled(true);
         ui->le_header->setEnabled(false);
         ui->lbl_chief->setDisabled(true);
         ui->ln_chief->setDisabled(true);
         ui->lbl_country->setEnabled(false);
         ui->lbl_name->setEnabled(false);
         ui->dateEdit->setEnabled(false);
         ui->lbl_birthdate->setEnabled(false);
         ui->lbl_header->setEnabled(false);
         ui->ln_country->setEnabled(false);
         ui->lbl_phonenumber->setEnabled(false);
         ui->ln_number->setEnabled(false);
     }
}


void editprofile::store_user_infile()
{
    remove("user.txt");

    ordinaryuser *oduser = nullptr;
    orguser *oguser = nullptr;
    anonymous *anonyuser = nullptr;


    fstream ufile;
    bool flag = 1;
    ufile.open("user.txt", ios::app);

    for(auto i : users)
    {
        if(flag)
        {
            flag = 0;
        }
        else ufile << '\n';

        if((oduser = dynamic_cast<ordinaryuser*>(i.second)) != NULL)
        ufile << "username: " << i.second->get_username() + 'P' << '\n';

        if((oguser = dynamic_cast<orguser*>(i.second)) != NULL)
        ufile << "username: " << i.second->get_username() + 'O' << '\n';

        if((anonyuser = dynamic_cast<anonymous*>(i.second)) != NULL)
        ufile << "username: " << i.second->get_username() + 'A' << '\n';

        ufile << "name: " << i.second->get_name() << '\n';

        ufile << "country: " << i.second->get_country() << '\n';

        ufile << "link: " << i.second->get_link() << '\n';

        ufile << "biography: " << i.second->get_biography() <<'\n';

        ufile << "birthday: "<< i.second->get_birthday() << '\n';

        ufile << "phonenumber: "<< i.second->get_phonenumber() << '\n';

        ufile << "password: " << i.second->get_password() << '\n';

        ufile << "header: " << i.second->get_header() << '\n';

        ufile << "=======================================";
    }

    ufile.close();
}



void editprofile::on_btn_save_clicked()
{

    string username = ui->ln_username->text().toStdString();

    if(username != currentuser->get_username())
    {
        user* copy;
        copy = currentuser;
        users.erase(currentuser->get_username());
        currentuser->set_username(username);

        users[currentuser->get_username()] = copy;
        stor_tweet_infile();
        store_follower_following_infile();
    }

    string name = ui->ln_name->text().toStdString();
    currentuser->set_name(name);
    string country = ui->ln_country->text().toStdString();
    currentuser->set_country(country);
    string link = ui->ln_link->text().toStdString();

    if(link == "")
    {
        link = '_';
    }

    currentuser->set_link(link);
    string password = ui->ln_password->text().toStdString();
    currentuser->set_password(password);
    string number = ui->ln_number->text().toStdString();
    currentuser->set_phonenumber(number);
    string header = ui->le_header->text().toStdString();

    if(header == "")
    {
        header = '_';
    }

    currentuser->set_header(header);
    store_user_infile();

    this->close();

    menu *l = new menu(users, currentuser);
    l->show();

}

void editprofile::stor_tweet_infile()
{
    remove("Tweets.txt");

    for(auto i: users)
    {
        i.second->save_in_file();
    }
}

void editprofile::store_follower_following_infile()
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
