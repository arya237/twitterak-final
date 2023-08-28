#include <iostream>
#include <algorithm>
#include "tweet.hpp"
#include "user.hpp"
#include <algorithm>
#include "ordinaryuser.hpp"
#include "QMessageBox"

using namespace std;

void tweet::set_post(string post)
{
    this -> post = post;
}

int tweet::check_tag(string post)
{
    int flag = -1;
    flag = post.find('#');

    if(flag == -1)
    return 0;

    else return 1;
}

void tweet::set_likes(user* currentuser)
{
   this->likes.push_back(currentuser);
}

void tweet::dislike(user *currentuser)
{
    for(int i = 0; i < this->likes.size(); i++)
    {
        if(likes[i] == currentuser)
        {
            this->likes.erase(this->likes.begin() + i);
        }
    }
}

void tweet::get_likes()
{
    for(auto i: likes)
    {
        cout << i->get_username() << endl;
    }
}

string tweet::get_likes(int index)
{
    return likes[index]->get_username();
}

int tweet:: show_likes()
{
    return likes.size();
}

bool tweet::check_like(user *currentuser)
{
    if(count(this->likes.begin(), this->likes.end(), currentuser))
    {
        return 0;
    }

    return 1;
}

void tweet::set_date(string date)
{
    this->date = date;
}

void tweet::set_mention(string mention, string date)
{
    tweet t;
    t.set_post(mention);
    t.set_date(date);

    this->mention.push_back(t);
}

tweet tweet::get_mentions(int index)
{
    return this->mention[index];
}
// flag
void tweet::mention_like(user* target, int index)
{
    QMessageBox q;

    if(this->mention[index -1].check_like(target))
    {
        this->mention[index - 1].set_likes(target);
        q.setText("mention liked!");
        q.exec();
    }

    else
    {
        q.setText("you liked this tweet before!");
        q.exec();
    }
}
//
unsigned int tweet::get_mention_like(int index)
{
    return this->mention[index].show_likes();
}

string tweet::get_mention_likers(int indexliker)
{
    return this->likes[indexliker]->get_username();
}

//like mention to read from file and no print any message

void tweet::fmention_like(user* target, int index)
{
    this->mention[index - 1].set_likes(target);
}

