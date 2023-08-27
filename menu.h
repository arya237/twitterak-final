#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "user.hpp"
#include "QListWidget"
#include "QTimer"
#include "ordinaryuser.hpp"

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(unordered_map<string, user*> &, user*, QWidget *parent = nullptr);
    ~menu();
    string SystemCurrentTime();
    void stor_tweet_infile();
    void store_follower_following_infile();
    bool checknum(int index, user* choise);
    bool check_user(string username);
    void set_hashtag(string hashtag , tweet* tweet);
    void find_hashtags();
    void write_hashtag_infile();
    void read_hashtag_fromfile();
    void setinformation();
    void fill_followingswidget();
    void fill_tweetswidget();

private slots:

    void showtime();

    void on_btn_leftmenu_clicked();

    void on_btn_profile_clicked();

    void on_btn_calender_clicked();

    void on_btn_search_clicked();

    void on_btn_sendtweets_clicked();

    void on_btn_like_clicked();

private:
    Ui::menu *ui;
    user* currentuser;
    unordered_map<string, user*> users;
    unordered_map < string , vector <tweet*> > hashtags;
};

#endif // MENU_H
