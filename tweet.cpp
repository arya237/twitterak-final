#include <iostream>
#include <algorithm>
#include "tweet.hpp"
#include "user.hpp"
#include <algorithm>
#include "ordinaryuser.hpp"

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

