#ifndef TWEET_HPP
#define TWEET_HPP

#include <iostream>
#include <vector>

class user;
class ordinatyuser;


using namespace std;


struct date
{
    int day;
    int month;
    int year;
    int age;
};


class tweet
{   
    
    private:
    string post;
    string date;
    vector<user*> likes;
    
    public:
    bool check_like(user *currentuser);
    void set_post(string post);
    void set_likes(user *currentuser);
    string get_post(){return post;}
    void get_likes();
    int check_tag(string post);
    int show_likes();
    void dislike(user *currentuser);
    string get_likes(int index);
    void set_date(string date);
    string get_date(){return date;}
    
};

#endif