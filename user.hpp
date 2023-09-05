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
    string status;
    map <int, tweet> copytweet;


    protected:
    vector <user*> messages;
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
    virtual void set_image(string image);
    virtual void set_status(string status);

//============================================================================== getters

    virtual string get_image(){return image;}
    virtual string get_name(){return name;}
    virtual string get_header(){return header;}
    virtual string get_username(){return username;}
    virtual string get_password(){return password;}
    virtual string get_country(){return country;}
    virtual string get_link(){return link;}
    virtual string get_phonenumber(){return phonenumber;}
    virtual string get_biography(){return biography;}
    virtual string get_birthday();
    virtual string get_status(){return status;}
    virtual string GetPost();
    virtual string get_followers(int );
    virtual string get_followings(int );
    virtual int get_age();
    virtual int get_numbertweet(){return numbertweet;}
    virtual void fget_like(user *target, int index);
    virtual tweet* get_tweet(int index);

//===============================================================================

    virtual void dislike(user* currentuser, user* target, int index);
    virtual void Retweet(user* target, int tweetnum, string date);
    virtual void show_who_liked(user* target, int tweetnum);
    virtual void unfollow(user* target);
    virtual void set_mention(string, string, int);
    virtual void mention_like(user* target, int numbertweet, int indexmention);
    virtual void delete_tweet(int index);
    virtual void add_following(user*target);
    virtual void save_in_file();
    virtual void Set_filetweet(string post, string date);
    virtual void fadd_following(user* target);
    virtual int display_followers();
    virtual int display_followings(int t);
    virtual unsigned long long int get_tweet();
    virtual unsigned int get_mention_like(int numbertweet, int indexmention);
    virtual bool check_follow(user* target);
    virtual bool check_mention(int indxtweet, int indxmention);
    virtual bool check(int index);
    virtual void fmention_like(user* target, int numbertweet, int indexmention);
    virtual void follow_private(user* target);
    virtual string show_notif(int);
    virtual unsigned long long int show_notif_size(){return messages.size();}
    virtual void delete_notif(string);


};

#endif
