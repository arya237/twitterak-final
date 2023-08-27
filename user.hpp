#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include "tweet.hpp"
#include <map>
#include <unordered_map>


class tweet;
class twitterak;


using namespace std;


bool validatebio(string bio);
bool validatepass(string password);
bool validatebirthday(date birthday);
bool validatephonenumber(string phonenumber);
bool validateusername(string username);

class user
{   

    private:
    string username;
    string name;
    string header = "_";
    string password;
    string biography = "_";
    string country = "_";
    string link = "_";
    date birthday;
    string phonenumber;
    int numbertweet = 0;
    string image;

    protected:
    vector <user*> followers;
    vector <user*> followings;

    public:
    virtual void set_name(string name);
    virtual void set_username(string username);
    virtual void set_password(string password);
    virtual void set_header(string header);
    virtual void set_link(string link);
    virtual void set_birthday(date birthday);
    virtual void set_phonenumber(string phonenumber);
    virtual bool SetTweet(string post, string date);
    virtual void set_likes(user* currentuser, user* target, int index);
    virtual void set_numbertweet();
    virtual void set_country(string country);
    virtual void set_biography(string biography);
    virtual string get_name(){return name;}
    virtual string get_header(){return header;}
    virtual string get_username(){return username;}
    virtual string get_password(){return password;}
    virtual int get_numbertweet(){return numbertweet;}
    virtual string get_country(){return country;}
    virtual string get_link(){return link;}
    virtual string get_phonenumber(){return phonenumber;}
    virtual string get_biography(){return biography;}
    virtual string get_birthday();
    virtual int get_age();
    virtual string GetPost();
    virtual void dislike(user* currentuser, user* target, int index);
    virtual void View_Tweet();
    virtual void View_Tweet(int index);
    virtual void Edit_Tweet(string newtweet, int index);
    virtual void Retweet(user* target, int tweetnum, string date);
    // virtual void qoutetweet(user* target, int tweetnum, string qoutetweet, string date);
    virtual void show_who_liked(user* target, int tweetnum);
    virtual tweet* get_tweet(int index);
    virtual unsigned long long int get_tweet();
    virtual void delete_tweet(int index);
    virtual void print();
    virtual bool check(int index);
    virtual bool validatepass(string password);
    virtual bool validateusername(string username);
    virtual bool validatebirthday(date birthday);
    virtual bool validatebio(string bio);
    virtual bool validatephonenumber(string phonenumber);
    virtual void display_followings();
    virtual void add_following(user*target);
    virtual int display_followers();
    virtual int display_followings(int t);
    virtual void save_in_file();
    virtual void Set_filetweet(string post, string date);
    virtual void fadd_following(user* target);
    virtual void fget_like(user *target, int index);
    virtual string get_followers(int );
    virtual string get_followings(int );
    virtual bool check_follow(user* target);
    void unfollow(user* target);
    virtual void set_image(string image);
    virtual string get_image(){return image;}

    map <int, tweet> copytweet;

    
};

#endif
