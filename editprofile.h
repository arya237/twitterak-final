#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QMainWindow>
#include "user.hpp"
#include "menu.h"

namespace Ui {
class editprofile;
}

class editprofile : public QMainWindow
{
    Q_OBJECT

public:
    explicit editprofile(unordered_map<string, user*> &, user*,QWidget *parent = nullptr);
    void Default();
    void AccountType();
    ~editprofile();
    void store_user_infile();
    void stor_tweet_infile();
    void store_follower_following_infile();

private slots:

    void on_btn_save_clicked();

private:
    Ui::editprofile *ui;
    user* currentuser;
    unordered_map<string, user*> users;
};

#endif // EDITPROFILE_H

