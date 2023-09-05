#include <iostream>
#include <ctime>
#include <chrono>
#include <sstream>
#include "user.hpp"
#include "twitterak.hpp"
#include <fstream>
#include "QMessageBox"

using namespace std;


void user::set_username(string username)
{
    this -> username = username;
}

void user::set_name(string name)
{
    this -> name = name;
}


void user::set_password(string password)
{
    this -> password = password;
}

void user:: set_header(string header)
{
    this -> header = header;
}


void user::set_biography(string biography)
{
    if(biography != "")
    this -> biography = biography;
}

void user::set_country(string country)
{
    if(country != "")
    this -> country = country;
}

void user::set_link(string link)
{
    if(link == "")
    {
        this->link = "_";
    }

    if(link == "_")
    {
        this->link = "_";
    }

    else this->link = "https://" + link;
}

void user::set_birthday(date birthday)
{
    this -> birthday.year = birthday.year;
    this -> birthday.month = birthday.month;
    this -> birthday.day = birthday.day;
    this -> birthday.age = 2023 - (birthday.year);
}

void user::set_phonenumber(string phonenumber)
{
    if(phonenumber.substr(0,2) != "98")
    this -> phonenumber =  "98" + phonenumber;

    else this -> phonenumber = phonenumber;
}

void user::set_numbertweet()
{
    this->numbertweet++;
}


bool user::SetTweet(string post, string date)
{
    this->set_numbertweet();
    this->copytweet[numbertweet].set_post(post);
    this->copytweet[numbertweet].set_date(date);
    QMessageBox q;
    q.setText("your tweet was sent succesfuly!");
    q.exec();
    return 1;

}

void user::Set_filetweet(string post, string date)
{
    this->set_numbertweet();
    this->copytweet[numbertweet].set_post(post);
    this->copytweet[numbertweet].set_date(date);
}

bool user::check(int index)
{
    if(this->copytweet.count(index) == 1)
    {
        return 1;
    }

    return 0;
}


string user::GetPost()
{
    return this->copytweet[numbertweet].get_post();
}

void user::set_likes(user* currentuser, user* target, int index)
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

void user::dislike(user* currentuser, user* target, int index)
{
    target->copytweet[index].dislike(currentuser);
}

void user::delete_tweet(int index)
{
    this->copytweet.erase(index);
    QMessageBox q;
    q.setText("tweet deleted successfully");
    q.setWindowTitle("deleting tweet");
    q.exec();
}

void user::Retweet(user* target, int tweetnum, string date)
{
    string retweet;
    retweet += '@' + (target->get_username()) + ": " + target->copytweet[tweetnum].get_post();
    SetTweet(retweet, date);

}

void user::show_who_liked(user* target, int tweetnum)
{
    target->copytweet[tweetnum].get_likes();
}

tweet* user::get_tweet(int index)
{
    return &this->copytweet[index];
}


int user::display_followings(int t)
{
    return this->followings.size();
}

void user::add_following(user *target)
{
    QMessageBox q;

    if (target->get_name() != "Anonymous")
    {
        if(!count(target->followers.begin(), target->followers.end(), this) && !(target == this))
        {
            target->followers.push_back(&(*this));
            this->followings.push_back(target);
            q.setText(QString::fromStdString(target->get_username()) + " follwed");
            q.exec();
        }

        else
        {
            q.setWindowTitle("following");
            q.setText("you cant follow!");
            q.setDetailedText("may you want to follow an user that followed before or you try following yourself!");
            q.exec();
        }
    }


    else
    {
        q.setWindowTitle("follow");
        q.setText("this user is anonymous user!");
        q.setDetailedText("in twitterak we have 3type of users and anonymous users and you cant follow an anonymous user!");
        q.exec();
    }

}

void user::unfollow(user* target)
{

    for(unsigned int i = 0; i < this->followings.size(); i++)
    {
        if(this->followings[i] == target)
        {
            this->followings.erase(this->followings.begin() + i);
        }
    }

    for(unsigned int i = 0; i < target->followers.size(); i++)
    {
        if(target->followers[i] == this)
        {
            target->followers.erase(target->followers.begin() + i);
        }
    }


    QMessageBox q;
    q.setText(QString::fromStdString(target->get_username()) + "unfollowed!");
    q.setWindowTitle("unfollow");
    q.exec();
}

void user::fadd_following(user* target)
{
    target->followers.push_back(&(*this));
    this->followings.push_back(target);
}

string user::get_followers(int index)
{
    return this->followers[index]->get_username();
}

string user::get_followings(int index)
{
    return this->followings[index]->get_username();
}

int user::display_followers()
{
    return this->followers.size();
}

string user::get_birthday()
{
    stringstream birth;
    string b;

    birth << this->birthday.year << '/' <<  this->birthday.month << '/' << this->birthday.day;
    birth >> b;

    return b;
}

int user::get_age()
{
    return this->birthday.age;
}

void user::save_in_file()
{
    fstream output;
    output.open("Tweets.txt", ios::app);

    if(this->copytweet.size() != 0)
    {
        output << this ->get_username()<<endl;


        for(auto i : this->copytweet)
        {
            output << i.first << ": " << i.second.get_post() << endl << i.second.get_date() << endl << "likes: ";

            for(int j = 0; j < i.second.show_likes(); j++)
            {
                output << i.second.get_likes(j) << " ";
            }

            output << '\n' << "----\n";

            output << "mentions: " << endl;

            for(int j = 0; j < i.second.get_mentions(); j++)
            {
                output << i.second.get_mentions(j).get_post() << endl;
                output << i.second.get_mentions(j).get_date() << endl;
                output << "likes: ";

                for(int k = 0; k  < i.second.get_mention_like(j); k++)
                {
                    output << i.second.get_mentions(j).get_mention_likers(k) << " ";
                }

                output << "\n&&&&\n";


            }

            output << "====\n";

        }

        output <<"****\n";


        output.close();
    }

}

void user::fget_like( user *target, int index)
{
    this->copytweet[index].set_likes(target);
}

unsigned long long int user::get_tweet()
{
    return copytweet.size();
}

bool user::check_follow(user* target)
{

    if(count(this->followings.begin(), this->followings.end(), target))
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void user::set_mention(string post, string date, int index)
{
    this->copytweet[index].set_mention(post, date);
}

void user::set_image(string image)
{
    this->image = image;
}

void user::set_status(string status)
{
    this->status = status;
}

void user::mention_like(user* target, int numbertweet, int indexmention)
{
    target->copytweet[numbertweet].mention_like(this, indexmention);
}
// for like when we read from file

void user::fmention_like(user* target, int numbertweet, int indexmention)
{
    target->copytweet[numbertweet].fmention_like(this, indexmention);
}

void user::follow_private(user *target)
{
    target->messages.push_back(this);
}

string user::show_notif(int index)
{
    return this->messages[index]->get_username();
}

void user::delete_notif(string username)
{
    for(int i = 0; i < this->messages.size(); i++)
    {
        if(this->messages[i]->get_username() == username)
        {
            this->messages.erase(this->messages.begin() + i);
        }
    }
}

unsigned int user::get_mention_like(int numbertweet, int indexmention)
{
    return this->copytweet[numbertweet].get_mention_like(indexmention);
}

bool user::check_mention(int indxtweet, int indxmention)
{
    if(this->copytweet[indxtweet].get_mention_size() >= indxmention)
    {
        return 1;
    }

    else return 0;
}



