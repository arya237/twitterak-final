#ifndef ANONYMOUS_HPP
#define ANONYMOUS_HPP


#include <iostream>
#include "user.hpp"

using namespace std;

class anonymous : public user
{
    public :
    //username,password,header(set get),setlikes,disleke
    void set_link(string link){}
    void set_birthday(date birthday){}
    void set_phonenumber(string phonenumber){}
    void set_country(string country){}
    void set_biography(string biography){}
    int get_numbertweet(){}
    string get_country(){return "_";}
    string get_link(){return "_";}
    string get_phonenumber(){return "_";}
    string get_biography(){return "_";}
    string get_birthday(){return "_";}
    int get_age(){}
    string GetPost(){}
    bool SetTweet(string post, string date);
    void set_numbertweet(){}
    int display_followers();
    void Edit_Tweet(string newtweet, int index);
    void Retweet(user* target, int tweetnum, string date);
    void qoutetweet(user* target, int tweetnum, string qoutetweet);
    tweet* get_tweet(int index){}
    string get_header(){return "white";}
    void delete_tweet(int index);
    void print();
    bool check_follow(user* target);
    void set_likes(user* currentuser, user* target, int index);
    
};

#endif
