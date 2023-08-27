#include <iostream>
#include "anonymous.hpp"
#include <algorithm>
#include "QMessageBox"


void anonymous::print()
{   
    cout << "|------------------------------------|" << endl;
    cout << "|                                    |" << endl;
    cout << "|              "<< "WELCOME"<<"               |" << endl;
    cout << "|                                    |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "                 | |                " << endl;
    cout << "                 | |                " <<endl;
    cout << "username :" <<this ->get_username() <<endl << "name: "<<this -> get_name()<<endl;
}

int anonymous::display_followers()
{
    cout<<"*this user hasn't any follower!"<<endl;
    return 0;
}

bool anonymous::SetTweet(string post, string date)
{
    QMessageBox q;
    q.setText("you cant tweet!");
    q.setWindowTitle("tweet");
    q.setDetailedText("you are a anonymous user and in twitterak anonumous users cant tweet!");
    q.exec();
    return 0;
}

bool anonymous::check_follow(user* target)
{
    if(count(this->followings.begin(), this->followings.end(), target))
    {   
        return 1;
    }

    return 0;
}

void anonymous::set_likes(user* currentuser, user* target, int index)
{
    QMessageBox q;
    q.setText("you havent followed this user!");

    if(check_follow(target))
    {
        QMessageBox q;

        if(target->copytweet[index].check_like(currentuser))
        {
            target->copytweet[index].set_likes(currentuser);
            q.setText("liked!");
            q.setWindowTitle("like");
            q.exec();
        }

        else
        {
            q.setText("you liked this tweet before!");
            q.setInformativeText("do yo want to dislike this tweet?");
            q.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            q.setDefaultButton(QMessageBox::No);
            int resault = q.exec();

            switch(resault)
            {
                case  QMessageBox::Yes:
                    dislike(currentuser, target, index);
                break;

                case QMessageBox::No:
                break;
            }

        }
    }

    else q.exec();
}


void anonymous::Edit_Tweet(string newtweet, int index)
{
    cout << "*this type of user has no tweet!" << endl;
}

void anonymous::qoutetweet(user* target, int tweetnum, string qoutetweet)
{
    cout << "*this type of user hasn't allowed to quote tweet!" << endl;
}

void anonymous::Retweet(user* target, int tweetnum, string date)
{
        QMessageBox q;
        q.setText("you cant retweet!");
        q.exec();
}

void anonymous::delete_tweet(int index)
{
    cout << "*this type of user hasn't any tweet!" << endl;
}

