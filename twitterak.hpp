#ifndef TWITTERAK_HPP
#define TWITTERAK_HPP

#include <iostream>
#include <unordered_map>
#include "user.hpp"
#include "tweet.hpp"
#include <vector>


using namespace std;


class twitterak
{   
    private:
    user *currentuser = nullptr;
    unordered_map <string,user*> users;
    unordered_map < string , vector <tweet*> > hashtags;

    public: 

        void run();
        void signup(string,string,string,string,string,string,string,string,string);
        void ordsignup(string,string,string,string,string,string,string,string,string,string);
        void anonymoussignup(string,string);
        void login(string,string);
        void inaccount(user* currentuser);
        void Help();
        void profile (user *o) const;
        void edit (vector <string> &command);
        void deleteuser(string keyusername);
        void post_tweet (vector<string> &command);
        void edit_tweet(int i);
        void delete_tweet(int i);
        void seperator(string key, vector <string> &command);
        void Show_Who_Liked(user* target , int tweetnum);
        void changeheader(string header);
        void find_hashtags();
        void set_hashtag(string hashtag , tweet* tweet);
        void get_hashtag(string hashtag);
        void retweet(string username, int tweetnum);
        // void quote_tweet(string username, int tweetnum, vector<string> &command);
        bool check_user(string username);
        void seperator(string &key);
        bool checknum(int index, user *choise);
        void DisLike(user* currentuser, user* target, int index);
        void view_tweet(user*o);
        void view_tweet(user*o, int index);
        string getpassword(const string& prompt);
        string SystemCurrentTime();
        int check_typeuser();
        void store_user_infile();
        void read_file();
        date seperate_time(string);
        void stor_tweet_infile();
        void get_from_file();
        void store_follower_following_infile();
        void get_follower_following_infile();
        void write_hashtag_infile();
        void read_hashtag_fromfile();
        bool validateusername(string username);
};

#endif
