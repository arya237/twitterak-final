#include "menu.h"
#include "ui_menu.h"
#include "showprofile.h"
#include "QGroupBox"
#include "QPushButton"
#include "fstream"
#include "QDateTime"
#include "QMessageBox"
#include "orguser.hpp"
#include "anonymous.hpp"
#include "sstream"
#include "editprofile.h"
#include "QDebug"
#include "QTimer"
#include "QImage"



menu::menu(unordered_map<string, user*> &porpose, user* target, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu),
    currentuser(target),
    users(porpose)

{
    ui->setupUi(this);
    setinformation();
}

menu::~menu()
{
    delete ui;
}

void menu::stor_tweet_infile()
{
    remove("Tweets.txt");

    for(auto i: users)
    {
        i.second->save_in_file();
    }
}

void menu::store_follower_following_infile()
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

string menu::SystemCurrentTime()
{
    time_t t;
    struct tm *tt;
    time(&t);
    tt = localtime(&t);
    string time = asctime(tt);
    return time;
}

void menu::write_hashtag_infile()
{
    fstream input;
    bool flag = 1;
    input.open("hashtags.txt", ios::out);

        for(auto i: hashtags)
        {
            if(flag)
            {
                input << i.first << ":";
                flag = 0;
            }

            else input << '\n' << i.first << ":";

            for(auto j : i.second)
            {
                input << '\n' << j->get_post() << endl;
            }

            input << "------------";
        }

    input.close();
}

void menu::find_hashtags()
{
    tweet *temp;
    string copy;
    stringstream key(currentuser->GetPost());
    int counter = 0 ;
    int index = currentuser->get_numbertweet();

    for(int i = 0 ; i < currentuser->GetPost().size(); i++)
    {
        //checking if entered post has a hashtag or not.ascii code for # is 35.
        if(currentuser->GetPost()[i] == 35 )
        {
            counter ++;
        }
    }

    while(counter --)
    {
        temp = (currentuser->get_tweet(index));
        //seperates hashtags from a post
        getline(key,copy,'#');
        getline(key,copy,' ');
        set_hashtag(copy, temp);
    }

}

void menu::set_hashtag(string hashtag , tweet* tweet)
{
    hashtags[hashtag].push_back(tweet);
}

bool menu :: checknum(int index, user* choise)
{

    if(choise->check(index))
    return 1;

    else return 0;
}

bool menu::check_user(string username)
{

   if( users.count(username))
   {
        return 1;
   }

   else return 0;
}


void menu::on_btn_leftmenu_clicked()
{
    if(ui->btn_logout->isHidden())
    {
        ui->frame_leftmenu->resize(141, 850);

        QFont *font = new QFont("Dubai", 9);

        ui->frame_btn_rightmenu->resize(141, 51);
        ui->frame_btnprofile->resize(141, 61);
        ui->frame_setting->resize(141, 155);
        ui->frame_btn_calender->resize(141, 51);

        ui->btn_setting->setText("setting");
        ui->btn_setting->setFont(*font);

        ui->btn_profile->setText("profile");
        ui->btn_profile->setFont(*font);

        ui->btn_calender->setText("calender");
        ui->btn_calender->setFont(*font);

        ui->box_tweets->setGeometry(151, 65, 911, 731);

        ui->btn_logout->show();
        ui->btn_editprofile->show();
        ui->btn_deleteaccount->show();
    }

    else
    {
        ui->frame_leftmenu->resize(61, 850);
        ui->frame_btn_rightmenu->resize(61, 51);
        ui->frame_btnprofile->resize(61, 61);
        ui->frame_setting->resize(61, 155);
        ui->frame_btn_calender->resize(61, 51);

         ui->btn_setting->setText("");
         ui->btn_profile->setText("");
         ui->btn_calender->setText("");

         ui->box_tweets->setGeometry(71, 65, 911, 731);

        ui->btn_logout->hide();
        ui->btn_editprofile->hide();
        ui->btn_deleteaccount->hide();



    }
}

void menu::on_btn_profile_clicked()
{
    if(ui->box_profile->isHidden())
    {
        ui->box_tweets->setGeometry(408, 65, 861, 731);
        ui->box_profile->setGeometry(151, 65, 256, 731);
        ui->box_profile->show();
    }

    else
    {
        ui->box_profile->hide();
         ui->box_tweets->setGeometry(161, 65, 911, 731);

    }
}

void menu::showtime()
{
    QTime time = QTime::currentTime();

    QString Time = time.toString("hh : mm : ss");

    ui->lbl_showclock->setText(Time);

}

void menu::on_btn_calender_clicked()
{
    if(ui->calendarWidget->isHidden())
    {
        ui->calendarWidget->show();
        ui->box_tweets->resize(911, 731);
    }

    else
    {
        ui->calendarWidget->hide();
        ui->box_tweets->resize(911, 531);
    }

}

void menu::on_btn_search_clicked()
{
    if(ui->frame_search->isHidden())
    ui->frame_search->show();

    else ui->frame_search->hide();
}

void menu::on_btn_sendtweets_clicked()
{
    string date, post = ui->le_tweet->text().toStdString();

    if(post != "")
    {
        date = SystemCurrentTime();

        if(currentuser->SetTweet(post, date))
        {
            find_hashtags();
            write_hashtag_infile();
            setinformation();
        }

        stor_tweet_infile();
    }

    ui->le_tweet->clear();
}



void menu::on_btn_like_clicked()
{
    string username = ui->le_usernamelike->text().toStdString();
    int index = ui->le_numbertweetlike->text().toInt();

    if(username[0] == '@')
    {
        username = username.substr(1, username.size());
    }

    QMessageBox q;


    if(check_user(username) && checknum(index, users[username]))
    {
        currentuser->set_likes(currentuser, users[username], index);
        stor_tweet_infile();

        ui->listWidget_mytweets->clear();

        fill_tweetswidget();
    }


    else q.warning(this, "like", "user or numbertweet not exist!");

    ui->le_usernamelike->clear();

    ui->le_numbertweetlike->clear();

    ui->le_numbermentionlike->clear();

}

void menu::setinformation()
{
    ui->lbl_username->setText(QString::fromStdString('@' + currentuser->get_username()));
    ui->lbl_name->setText(QString::fromStdString( currentuser->get_name()));
    ui->lbl_country->setText(QString::fromStdString( currentuser->get_country()));
    ui->lbl_phone->setText(QString::fromStdString( currentuser->get_phonenumber()));
    ui->lbl_birthday->setText(QString::fromStdString( currentuser->get_birthday()));

    if(currentuser->get_link() != "" && currentuser->get_link() != "_")
    ui->lbl_link->setText(QString::fromStdString("https://" + currentuser->get_link()));

    if(currentuser->get_header() != "" && currentuser->get_header() != "_")
    {
        ui->frame->setStyleSheet("background-color: " + QString::fromStdString(currentuser->get_header()));
    }

    else   ui->lbl_link->setText(QString::fromStdString(currentuser->get_link()));

    ui->lcd_followers->display(currentuser->display_followers());

    QImage image(QString::fromStdString(currentuser->get_image()));

    QImage image2 = image.scaled(1920, 1080, Qt::KeepAspectRatio);

    ui->lbl_profile->setPixmap(QPixmap::fromImage(image2));
    ui->lbl_profile->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->lbl_profile->setFixedSize(50, 50);
    QRegion *region = new QRegion(0, 0, ui->lbl_profile->width(), ui->lbl_profile->height(), QRegion::Ellipse);
    ui->lbl_profile->setScaledContents(true);
    ui->lbl_profile->setMask(*region);

    ui->btn_logout->hide();
    ui->btn_editprofile->hide();
    ui->btn_deleteaccount->hide();
    ui->box_profile->hide();
    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(showtime()));

    timer->start(1000);

    QImage image3("C:/Users/Aryan/Desktop/icons/clock.png");

    ui->lbl_showclocklogo->setPixmap(QPixmap::fromImage(image3));
    ui->lbl_showclocklogo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->lbl_showclocklogo->setFixedSize(24, 24);
    ui->frame_search->hide();
    ui->calendarWidget->hide();

    fill_tweetswidget();
    fill_followingswidget();

}

void menu::fill_followingswidget()
{
    ui->listWidget_followings->clear();

    for(int i = 0; i < currentuser->display_followings(0); i++)
    {
        ui->listWidget_followings->addItem(QString::fromStdString(currentuser->get_followings(i)));

    }
}

void menu::fill_tweetswidget()
{
    if(currentuser->get_tweet() != 0)
    {
        ui->listWidget_mytweets->clear();

        for(int i = 1; i <= currentuser->get_tweet(); i++)
        {
            QString item =  QString::number((i)) + QString::fromStdString((": " + currentuser->get_tweet(i)->get_post()) + '\n'
            + currentuser->get_tweet(i)->get_date() + '\n') + QString::fromStdString("likes: ") + QString::number(currentuser->get_tweet(i)->show_likes());

            ui->listWidget_mytweets->addItem(item);
        }
    }
}


void menu::on_rbtn_users_clicked()
{
    ui->listWidget_showusersandhastags->clear();

    for(auto i : users)
    {
        ui->listWidget_showusersandhastags->addItem(QString::fromStdString( i.second->get_username()));
    }
}

void menu::on_btn_showprofile_clicked()
{
    string username = ui->le_showprofile->text().toStdString();

    if(username[0] == '@')
    {
        username = username.substr(1, username.size());
    }

    if(check_user(username))
    {
        showprofile *p = new showprofile(users[username], currentuser, users);
        p->show();

        ui->listWidget_followings->clear();

        for(int i = 0; i < currentuser->display_followings(0); i++)
        {
            ui->listWidget_followings->addItem(QString::fromStdString(currentuser->get_followings(i)));

        }
    }

    else QMessageBox::warning(this, "profile", "this user not found!");

    ui->le_showprofile->clear();

}



void menu::on_btn_retweet_clicked()
{
    string username = ui->le_usernameretweet->text().toStdString();
    int index = ui->le_numberretweet->text().toInt();
    string date = SystemCurrentTime();
    QMessageBox q;

    if(username[0] == '@')
    {
        username = username.substr(1, username.size());
    }



    if(check_user(username) && checknum(index, users[username]))
    {
        currentuser->Retweet(users[username], index, date);
        stor_tweet_infile();

        fill_tweetswidget();
    }

    else q.warning(this, "retweet", "user or numbertweet not exist!");

    ui->le_numberretweet->clear();
    ui->le_usernameretweet->clear();
}

void menu::on_btn_follow_clicked()
{
    string username = ui->le_follow->text().toStdString();
    QMessageBox q;

    if(username[0] == '@')
    {
        username = username.substr(1, username.size());
    }


    if(check_user(username))
    {
        currentuser->add_following(users[username]);
        store_follower_following_infile();

        fill_followingswidget();

    }

    else q.warning(this, "follow", "user not found!");



    ui->le_follow->clear();
}

void menu::on_btn_logout_clicked()
{
    this->close();
}

void menu::on_btn_deletetweet_clicked()
{
    int index = ui->le_deletetweet->text().toInt();
    QMessageBox q;


    if(checknum(index, currentuser))
    {
        for(auto i: hashtags)
        {
            for(int j = 0; j < i.second.size(); j++)
            {
                if(i.second[j] == currentuser->get_tweet(index))
                {
                    i.second.erase(i.second.begin() + j);
                    break;
                }
            }

            if(i.second.size() == 0)
            {
                hashtags.erase(i.first);
            }
        }

        currentuser->delete_tweet(index);
        stor_tweet_infile();
        write_hashtag_infile();

        fill_tweetswidget();
    }

    else q.warning(this, "deleting tweet", "this tweet not exist!");

    ui->le_deletetweet->clear();
    ui->le_deletetweet->hide();

}

void menu::on_btn_sendmention_clicked()
{
    string username = ui->le_usernamemention->text().toStdString();
    int index = ui->le_numbertweetemtion->text().toInt();

    if(check_user(username) && checknum(index, users[username]))
    {
        string post = ui->le_mentionpost->text().toStdString();
        string date = SystemCurrentTime();

        users[username]->set_mention(post, date, index);
    }

    stor_tweet_infile();

    ui->le_mentionpost->clear();

    ui->le_numbertweetemtion->clear();

    ui->le_usernamemention->clear();

}
