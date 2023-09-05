#include "notifactions.h"
#include "ui_notifactions.h"
#include <QMessageBox>
#include "QtWidgets"
#include "showprofile.h"

notifactions::notifactions(unordered_map<string, user*> &porpose, user* me, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::notifactions)
{
    ui->setupUi(this);
    users = porpose;
    currentuser = me;
    this->show();


    for(unsigned long long int i = 0; i < currentuser->show_notif_size(); i++)
    {
        ui->listWidget_messages->addItem(QString::fromStdString(currentuser->show_notif(i)));
    }
}

notifactions::~notifactions()
{
    delete ui;
}

void notifactions::on_listWidget_messages_itemClicked(QListWidgetItem *item)
{
    QMessageBox q, s;

    string username = ui->listWidget_messages->currentItem()->text().toStdString();

    int result = q.information(this, "follow", (QString::fromStdString(username) + " wants to follow you, do you accept?"), "yes", "No", "show profile");

    switch (result)
    {
        case 0:
            users[username]->fadd_following(currentuser);
            currentuser->delete_notif(username);
        break;

        case 1:
            currentuser->delete_notif(username);
        break;

        case 2:
            showprofile *l = new showprofile(users[username], currentuser, users);
            l->show();
        break;


    }

}
