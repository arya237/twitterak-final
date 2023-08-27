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

bool user::validatepass(string password)
{       
    bool charflag = 0, upcaseflag = 0, lowcaseflag = 0, numflag = 0;

    try
    {

        for(int i : password)
        {
            if((i >= 33 && i <= 47 ) || ( 58 <= i && i <= 64) || i == 32)
            {
                charflag = 1;
            }

            if(i >= 48 && i <= 57)
            {
                numflag = 1;
            }

            if(i >= 65 && i <= 90)
            {
                upcaseflag = 1; 
            }

            if(i >= 97 && i <= 122)
            {
                lowcaseflag = 1;
            }
        }

        if(charflag && lowcaseflag && upcaseflag && numflag)
        {
            return 0;
        }

        else throw std::invalid_argument
            ("! Password must have at least 8 digit and lowercaseand uppercase and number and character.");
    }

    catch (invalid_argument &e)
    {
        cout << e.what() << endl;
        return 1;
    }

}



bool user::validateusername(string username)
{
    try
    {
        if(username.size() <  5)
        {
            QMessageBox s;
            s.setText("wrong username");
            s.exec();
        } 

        if(username == "login" || username == "signup" || username == "tweeet" || username == "edit" || username == "profile"
        || username == "retweet" || username == "quotetweet" || username == "exit" || username == "help" || username == "like")
        {
            QMessageBox s;
            s.setText("wrong username");
            s.exec();
        }
    }

    catch(out_of_range& e)
    {
        cout << e.what() << endl;
        return 1;
    }

    catch(invalid_argument &e)
    {
        cout << e.what() << endl;
        return 1;
    }
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
    if(link != "" && link != "_")
    this -> link = "https://" + link;

    else this->link = '_';
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


void user::print()
{
    cout << "|------------------------------------|" << endl;
    cout << "|                                    |" << endl;
    cout << "|              "<< "WELCOME"<<"               |" << endl;
    cout << "|                                    |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "                 | |                " << endl;
    cout << "                 | |                " <<endl;
    

    cout <<"username: "<< get_username() <<endl<< "name: " << get_name()<< endl << "biography : " << get_biography() << endl 
    << "link : " << get_link() << endl << "country : " << get_country() << endl<< "phonenumber: " <<
    get_phonenumber() << endl << "age: " << get_age() << endl;
    cout << "number of followers: " << display_followers();
    cout << endl;
    
    
    cout << "==================================" << endl;
}



bool user::validatebio(string bio)
{   try
    {
        if(bio.size() > 160)
        {
            throw out_of_range("max size of bio is 160 character!");
        }
    }

    catch(out_of_range &e)
    {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}

bool user::validatebirthday(date birthday)
{   
    try
    {
        if(birthday.year < 1900 || birthday.year > 2023)
            throw std::invalid_argument ("! Year invalid. try again");

        if(birthday.month < 1 || birthday.month > 12)
            throw std::invalid_argument ("! Month invalid. try again");

        if(birthday.day < 1 || birthday.day > 31)
            throw std::invalid_argument ("! Day invalid. try again");
    }

    catch(invalid_argument &e)
    {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}

bool user::validatephonenumber(string phonenumber)
{
    try
    {
        if ( phonenumber.size() != 10)
        {
            throw out_of_range ("! Phonenumber must be exactly 10 numbers");
        }

        for(int i : phonenumber)
        {
            if(i < 48 || i > 57)
            {
                throw std::invalid_argument("! Invalid argumnet. try again");
            }
        }
    }     

    catch(out_of_range &e)
    {
        cout << e.what() << endl;
        return 1;
    }

    catch(invalid_argument &e)
    {
        cout << e.what() << endl;
        return 1;
    }
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

void user::View_Tweet()
{
     for(auto i : this->copytweet)
    {
        cout << i.first << ": " << i.second.get_post() << endl << i.second.get_date() << "likes: " 
        << this->copytweet[int(i.first)].show_likes()<< endl << "--------------------------" << endl; 

    }
}

void user::View_Tweet(int index)
{   
    cout << index << ":" << this->copytweet[index].get_post() << endl << this->copytweet[index].get_date() << endl
    << "likes: " << this->copytweet[index].show_likes() << endl << "--------------------------" << endl; 
}

void user::Edit_Tweet(string newtweet, int index)
{
    this->copytweet[index].set_post(newtweet);
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
    if(!(target->copytweet[index].check_like(currentuser)))
    {
        target->copytweet[index].dislike(currentuser);
    }

    else cout << "* you have'nt like this tweet!" << endl;
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

void user::display_followings()
{
    for( auto i : this->followings)
    {
        cout << i->get_username() << endl;
    }

    cout << "number of followings: " << this->followings.size() << endl;
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
    cout << "this->followings: " << endl;
    for(auto i : this->followings)
    {
        cout << i->get_username() << " ";
    }

    cout << endl;

    cout << "target->followers: " << endl;
    for(auto i : target->followers)
    {
        cout << i->get_username() << " ";
    }

    for(unsigned int i = 0; i < this->followings.size(); i++)
    {
        if(this->followings[i] == target)
        {
            this->followings.erase(this->followings.begin(), this->followings.begin() + i + 1);
        }
    }

    for(unsigned int i = 0; i < target->followers.size(); i++)
    {
        if(target->followers[i] == this)
        {
            target->followers.erase(target->followers.begin(), target->followers.begin() + i + 1);
        }
    }

    cout << "this->followings: " << endl;
    for(auto i : this->followings)
    {
        cout << i->get_username() << " ";
    }

    cout << endl;

    cout << "target->followers: " << endl;
    for(auto i : target->followers)
    {
        cout << i->get_username() << " ";
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

void user::set_image(string image)
{
    this->image = image;
}



