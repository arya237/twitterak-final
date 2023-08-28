#ifndef SHOWPROFILE_H
#define SHOWPROFILE_H

#include <QWidget>
#include "user.hpp"

namespace Ui {
class showprofile;
}

class showprofile : public QWidget
{
    Q_OBJECT

public:
    explicit showprofile( user* target, user* currentuser, unordered_map<string, user*> &users, QWidget *parent = nullptr);
    ~showprofile();
    void set();
    void store_follower_following_infile();

private slots:

    void on_btn_follow_clicked();

private:
    Ui::showprofile *ui;
    user * target;
    user * currentuser;
    unordered_map<string, user*> users;
};

#endif // SHOWPROFILE_H
