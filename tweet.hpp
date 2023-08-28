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
    vector <user*> likes;
    vector <tweet> mention;

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
    void set_mention(string, string);
    int get_mentions(){return this->mention.size();}
    tweet get_mentions(int);
    int get_mention_size(){return this->mention.size();}
    void mention_like(user* target, int index);
    unsigned int get_mention_like(int index);
    string get_mention_likers(int indexliker);
    void fmention_like(user* target, int index);

};

#endif
