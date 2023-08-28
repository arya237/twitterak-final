#include <iostream>
#include "user.hpp"
#include "ordinaryuser.hpp"
#include <sstream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include "twitterak.hpp"
#include "tweet.hpp"
#include <ctime>
#include <limits>
#include <stdexcept>
#include <string>
#include <windows.h>
#include <conio.h>
#include "orguser.hpp"
#include "anonymous.hpp"
#include <fstream>
#include "QMessageBox"
#include "signuporganization.h"
#include "menu.h"
#include "QDebug"

using namespace std;

vector <string> command;
tweet temp;

//Program starts here by getting command from user.User must sign up or log in first.


//========================================================================= signingup
//Sign up function which asks for users information. 

void twitterak::signup(string username,string name,string country,string phonenumber,string link,string password,string biography, string header, string profile)
{
    currentuser = new orguser;


    if(link == "")
    {
        link = '_';
    }

    if(header == "")
    {
        header = '_';
    }

    currentuser->set_username(username);
    currentuser->set_name(name);
    currentuser->set_header(header);
    currentuser->set_password(password);
    currentuser->set_country(country);
    currentuser->set_link(link);
    currentuser->set_biography(biography);
    currentuser->set_image(profile);
    currentuser->set_phonenumber(phonenumber);
    currentuser->set_header(header);

    //saving current user information in users map.
    users[currentuser->get_username()] = currentuser;
     store_user_infile();
    //after sign up user is allowed to run program with inaccount function.

    QMessageBox s;
    s.setText("successful");
    s.exec();

    inaccount(currentuser);

}

void twitterak::ordsignup(string username,string name,string country,string phonenumber,string link,string password,string biography, string birthday, string header, string profile)
{
        //Some validations done in user header file.
    currentuser = new ordinaryuser;

    //setters
    currentuser->set_username(username);
    currentuser->set_name(name);
    currentuser->set_header(header);
    currentuser->set_password(password);
    currentuser->set_country(country);
    currentuser->set_link(link);
    currentuser->set_biography(biography);
    currentuser->set_header(header);
    currentuser->set_birthday(seperate_time(birthday));
    currentuser->set_phonenumber(phonenumber);
    currentuser->set_image(profile);

    //saving current user information in users map.

    users[currentuser->get_username()] = currentuser;
    store_user_infile();

    //after sign up user is allowed to run program with inaccount function.

    QMessageBox s;
    s.setText("successful");
    s.exec();

    inaccount(currentuser);
}
void twitterak::anonymoussignup(string username , string password)
{   

        currentuser = new anonymous ;

        currentuser->set_name("Anonymous");
        currentuser->set_username(username);
        currentuser->set_password(password);
        currentuser->set_biography("");
        currentuser->set_country("");
        currentuser->set_link("");
        currentuser->set_phonenumber("");
        currentuser->set_header("white");
        users[currentuser->get_username()] = currentuser;
        store_user_infile();

        QMessageBox s;
        s.setText("successful");
        s.exec();
        inaccount(currentuser);

}

//=================================================== login

void twitterak::login(string username , string password)
{   
    //if user already has an account , this function wll be called
     //which asks for username and password

    QMessageBox q;

//    for(auto i: users)
//    {
//        cout << i.first << " : " << i.second->get_username() << endl;
//    }

//    cout << users[username]->get_password();
//    cout << users[username]->get_username();

        if(users.count(username) == 1)
        {
            if(users[username]->get_password() == password)
            {   
                currentuser = users[username];

                q.setText("login succesful");
                q.exec();
                inaccount(users[username]);
            }

            else
            {
                q.setText("password is incorrect!");
                q.exec();
            }
        }

        else
        {
            q.setText("username notfound!");
            q.exec();
        }

}

//================================================ inaccount menu

void twitterak::inaccount(user *currentuser)
{
    menu *l = new menu(users, currentuser);
    l->show();


//    currentuser->


//    changeheader(currentuser->get_header());
//    system("cls");

//    while(1)
//    {
//        cout << "> @" << users[currentuser->get_username()]->get_username();
//        cout << " > ";
        
//        string key;
//        //program inputs command and checks for wanted option
//        getline(cin , key);
//        seperator(key, command);
        
//        for(int i = 0; i < command[0].size(); i++)
//        {
//            command[0][i] = tolower(command[0][i]);
//        }

        
//        if (command.size() == 0)
//        {
//            continue;
//        }

//        //outputs other users profile
//        if(command[0] == "profile" && command.size() == 2)
//        {
//            string user;
//            user = command[1].substr(1, command[1].size());

//            if(check_user(user))
//            {
//                profile(users[user]);
//            }

//            else cout << "! User not found!" << endl;
//        }
        
//        //outputs current user profile.
//        else if(command[0] == "profile" || command[0] == "me")
//        {
//            profile(currentuser);
//        }
//        //outputs all tweets of current user.
//        else if(command[0] == "@me")
//        {
//            view_tweet(currentuser);
//        }

//        else if (command[0][0] == '@' )
//        {
//            //outputs usernames that liked a certain tweet.
//            //command format is: @username:tweet number:likes

//            if(command[0].find("likes") != string::npos)
//            {
//                string username;
//                for(int i = 1; i <command[0].size(); i++)
//                {
//                    username += command[0][i];
//                }
                
//                //seperating username and tweet number.
//                int tweetnum;
//                string copyuser;
//                stringstream key(username), copy1;
//                getline(key , copyuser , ':');
//                username = copyuser;
//                getline(key , copyuser , ':');
//                copy1 << copyuser;
//                copy1 >> tweetnum;

//                if(username[0] == '@')
//                {
//                    username = username.substr(1, username.size());
//                }
                    
//                if(check_user(username) && checknum(tweetnum, users[username]))
//                {
//                    user* target = users[username];
//                    currentuser->show_who_liked(target, tweetnum);
//                }

//                else cout << "! User or tweetnumber not exist!" << endl;
//            }

//            else if(command[0].find(":")  != string :: npos)
//            {
//                //outputs a certain tweet from entered username
//                //command format is: @username:tweet number.
//                int tweetnum;
//                string username;
//                string number;
//                stringstream copy(command[0]), copy1;
//                getline(copy, username, ':');
//                getline(copy, number, ':');

//                copy1 << number;
//                copy1 >> tweetnum;
                
//                if(username[0] == '@')
//                username = username.substr(1, username.size());

//                if(check_user(username) && checknum(tweetnum, users[username]))
//                {
//                    view_tweet(users[username], tweetnum);
//                }

//                else cout << "! User or tweet number not found!" << endl;
//            }

//            else
//            {
//                //outputs all tweets of wanted user
//                string username;
//                for(int i = 1; i <command[0].size(); i++)
//                {
//                    username += command[0][i];
//                }

//                if(check_user(username))
//                {
//                    view_tweet(users[username]);
//                }

//                else cout << "! User or tweetnumber not found!" << endl;
//            }
//        }

//        //editting tweets or profile
//        else if ( command[0] == "edit")
//        {
//            if(command[1] == "profile")
//            {
//                edit(command);
//            }

//            else if (command[1] == "tweet")
//            {
//                int i = stoi(command[2]);
//                if(checknum(i, currentuser))
//                {
//                    edit_tweet(i);
//                }

//                else cout << "! Tweet doesn't exist." << endl;
                
        
//            }
//        }

//        //this part saves current user's username that likes others tweets.
//        //command format: like @username:tweetnume
//        else if (command[0] == "like")
//        {
//                //seperating username and tweet number
//                int index;
//                string str1 = command[1];
//                string str2 ;
//                stringstream copy(str1), copy1;
//                getline (copy , str2 , ':');
//                string username = str2 ;
//                getline (copy , str2 , ':');
//                string tweetnum = str2;

//                copy1 << tweetnum;
//                copy1 >> index;
                
//                if(username[0] == '@')
//                username = username.substr(1,username.size()- 1);

//                if(check_user(username) && checknum(index, users[username]))
//                {
//                    user *target = users[username];
//                    currentuser->set_likes(currentuser, target, index);
//                }

//                else cout << "! User or tweetnumber not found!" << endl;
//        }

      
//        else if ( command[0] == "logout" )
//        {
//            run();
//        }

//        else if (command[0] == "tweet")
//        {
//            post_tweet(command);
//        }
        
//        else if(command[0] == "delete")
//        {
//            if(command[1] == "account")
//            {
//                deleteuser(currentuser->get_username());
//                cin.ignore();
//                run();
//            }

//            else if(command[1] == "tweet")
//            {
//                int i = stoi(command[2]);
//                currentuser->delete_tweet(i);

//            }
//        }

//        else if (command[0] == "exit")
//        {
//            stor_tweet_infile();
//            store_user_infile();
//            store_follower_following_infile();
//            write_hashtag_infile();

//            cout << "please rate us in google play: ******" << endl;
//            exit(0);
//        }

//        else if(command[0] == "help")
//        {
//            Help();
//        }

//        else if(command[0] == "retweet")
//        {
//            //seperates username and twwetnumber of wanted tweet.
//            string username = command[1].substr(1,command[1].size());
//            string copyusername;
//            int tweetnum;
//            stringstream copy(username), copy1;
//            getline(copy, copyusername ,':');
//            username = copyusername;
//            getline(copy, copyusername ,':');
//            copy1 << copyusername;
//            copy1 >> tweetnum;

//            cout << username << " : " << tweetnum;

//            if(check_user(username) && checknum(tweetnum, users[username]))
//            {
//                retweet(username, tweetnum);
//            }

//            else cout << "! User or tweetnumber not found!" << endl;
            
//        }

//        else if(command[0][0] == '#')
//        {
//            get_hashtag(command[0]);
//        }

//        // else if(command[0] == "quotetweet")
//        // {
//        //     //seperates username and twwetnumber of wanted tweet.

//        //     string username;

//        //     if(command[1][0] == '@')
//        //     username = command[1].substr(1,command[1].size());
            
//        //     else username = command[1];

//        //     string copyusername;
//        //     int tweetnum;
//        //     stringstream copy(username), copy1;
//        //     getline(copy, copyusername ,':');
//        //     username = copyusername;
//        //     getline(copy, copyusername ,':');

//        //     copy1 << copyusername;
//        //     copy1 >> tweetnum;

//        //     if(check_user(username) && checknum(tweetnum, users[username]))
//        //     {
//        //         quote_tweet(username, tweetnum, command);
//        //     }

//        //     else cout << "! User or tweetnumber found." << endl;
//        // }

//        else if(command[0] == "dislike")
//        {
//            string str1 = command[1];
//            string str2 ;
//            int index = 0;
//            stringstream copy(str1);
//            getline (copy , str2 , ':');
//            string username = str2 ;
//            getline (copy , str2 , ':');
//            string tweetnum = str2;
//            copy.clear();
//            copy << tweetnum;
//            copy >> index;

//            if(username[0] == '@')
//            username = username.substr(1,username.size()- 1);
            
//            user *target = users[username];
            
//            if(check_user(username) && checknum(index, users[username]))
//            {
//                DisLike(currentuser, target, index);
//            }
//        }

//        else if(command[0] == "cls" || command[0] == "clear")
//        {
//            system("cls");
//        }

//        else if (command[0] == "follow")
//        {
//            string username;

//            if(command[1][0] == '@')
//            username = command[1].erase(0,1);

//            else username = command[1];

//            if(check_user(username))
//            currentuser->add_following(users[username]);

//            else cout << "user not found!" << endl;
//        }

//        else if(command[0] == "showfollowing")
//        {
//            currentuser->display_followings();
//        }

//        else cout << "! Invalid command" << endl;

//        command.clear();
//    }
}

//=============================================== help

//void twitterak::Help()
//{
//    cout << setw(13) << "=======================" << endl << setw(13) << "menu" << endl;
//    cout << setw(16) << ">Profile" << endl << setw(13) << ">edit" << endl << setw(15) << ">logout" << endl << setw(23)
//    << ">delete account" <<endl << setw(14) << ">tweet" << endl << setw(13) << setw(15) << ">retweet" << endl <<setw(15)<< ">exit" << endl
//    << setw(18) <<">qoutetweet" << endl << setw(15) << "like" << endl << setw(18) <<"dislike"<<endl;
//}

////==================================== profile
////outputs current users profile information using getter

//void twitterak::profile (user *o) const
//{
//    o->print();
//}

////==================================== edit profile

//void twitterak::edit (vector <string> &command)
//{

//    if (command[2] == "username")
//    {
//        //changing username in both key and value of users map.
//        user *copy;
//        copy = currentuser;

//        //sepereating double qout and @.
//        command[3] = command[3].erase(0,1);

//        if(command[3][0] == '@')
//        {
//            command[3] = command[3].erase(0,1);
//        }

//        command[3] = command[3].erase(command[3].size()-1 ,1);

//        while(currentuser->validateusername(command[3]))
//        {
//            cin >> command[3];

//            command[3] = command[3].erase(0,1);

//            if(command[3][0] == '@')
//            {
//                command[3] = command[3].erase(0,1);
//            }

//            //deleting account by erasing current usernames' element in users map.
//            command[3] = command[3].erase(command[3].size()-1 ,1);

//            cin.ignore();

//        }

//        users.erase(currentuser->get_username());
//        currentuser->set_username(command[3]);
//        users[command[3]] = copy;
//    }

//    else if (command[2] == "password" )
//    {
//        command[3] = command[3].erase(0,1);
//        command[3] = command[3].erase(command[3].size()-1 ,1);

//        while(currentuser->validatepass(command[3]))
//        {
//            cin >> command[3];

//            command[3] = command[3].erase(0,1);
//            command[3] = command[3].erase(command[3].size()-1 ,1);

//        }

//        currentuser->set_password(command[3]);
//    }

//    else if(command[2] == "country")
//    {
//        command[3] = command[3].erase(0,1);
//        command[3] = command[3].erase(command[3].size()-1 ,1);
//        currentuser->set_country(command[3]);
//    }

//    else if(command[2] == "link")
//    {
//        command[3] = command[3].erase(0,1);
//        command[3] = command[3].erase(command[3].size()-1 ,1);
//        currentuser->set_link(command[3]);
//    }


//    else if(command[2] == "phonenumber")
//    {
//        while(currentuser->validatephonenumber(command[3]))
//        {
//            cin >> command[3];
//        }

//        currentuser->set_phonenumber(command[3]);
//    }

//    else if(command[2] == "name")
//    {
//        command[3] = command[3].erase(0,1);
//        command[3] = command[3].erase(command[3].size()-1 ,1);

//        currentuser->set_name(command[3]);
//    }

//    else if(command[2] == "biography")
//    {
//        command[3] = command[3].erase(0,1);
//        command[3] = command[3].erase(command[3].size()-1 ,1);

//        currentuser->set_biography(command[3]);
//    }

//    else cout << "command invalid!" << endl;
//}



////============================================== delete user

////void twitterak::deleteuser(string keyusername)
////{
////    char ch;
////    cout << "Do you want delete your account? y/n";
////    cin >> ch;

////    if(ch == 'y')
////    {
////        users.erase(keyusername);
////         cout << "* Account deleted successfully." << endl;
////    }
////    cin.ignore();
//////    run();
////}

////============================================== post tweet
// //sets tweet and its number and saves in a map.
 
//void twitterak::post_tweet (vector<string> &command)
//{
//    string post, date;
//    string number;

//    for(int i = 1; i < command.size(); i++)
//    {
//        post += command[i] + " ";
//    }

//    seperator(post);

    
//    date = SystemCurrentTime();

//    if(currentuser->SetTweet(post, date))
//    {
//        find_hashtags();
//    }
//}

////============================================== view tweet
////outputs all tweets
//void twitterak::view_tweet(user* o)
//{
    
//    o->View_Tweet();
//}

////oveloaded function outputs specific tweet.
//void twitterak::view_tweet(user*o, int index)
//{
//    o->View_Tweet(index);
//}

////============================================= edit tweet

//void twitterak::edit_tweet(int i)
//{
//    if(currentuser->get_age() == -1)
//    {
//        cout << "Enter your new tweet:"<< endl;
//        string newtweet;
//        getline(cin , newtweet);

//        newtweet += '\n' + SystemCurrentTime();
//        currentuser->Edit_Tweet(newtweet,i);
//    }

//    else if ( currentuser->get_age() < 18)
//    cout << "! You can't access editng tweets because you're under 18." << endl;
//    //edits tweet if user is older than 18.
//    //accessing tweets map at wanted index.

//    else
//    {
//        cout << "Enter your new tweet:"<< endl;
//        string newtweet;
//        getline(cin , newtweet);

//        newtweet += '\n' + SystemCurrentTime();
//        currentuser->Edit_Tweet(newtweet,i);
//    }
 
//}



////============================================= delete tweet

//void twitterak::retweet(string username, int tweetnum)
//{
//    string date = SystemCurrentTime();
//    currentuser->Retweet(users[username], tweetnum, date);
//}

//// void twitterak::quote_tweet(string username, int tweetnum, vector<string> &command)
//// {
////     string qoute, date;

////     for(int i = 2; i < command.size(); i++)
////     {
////         qoute += command[i] + " ";
////     }
   
////     date = SystemCurrentTime();

////     currentuser->qoutetweet(users[username], tweetnum, qoute, date);
////     //setting entered tweet with username and qouted tweet together and set it as a post for current user.

////     cout << "* Your tweet sent successfully." <<endl;
//// }

//void twitterak:: find_hashtags()
//{
//    tweet *temp;
//    string copy;
//    stringstream key(currentuser->GetPost());
//    int counter = 0 ;
//    int index = currentuser->get_numbertweet();

//    for(int i = 0 ; i < currentuser->GetPost().size(); i++)
//    {
//        //checking if entered post has a hashtag or not.ascii code for # is 35.
//        if(currentuser->GetPost()[i] == 35 )
//        {
//            counter ++;
//        }
//    }

//    while(counter --)
//    {
//        temp = (currentuser->get_tweet(index));
//        //seperates hashtags from a post
//        getline(key,copy,'#');
//        getline(key,copy,' ');
//        set_hashtag(copy, temp);
//    }
    
//}

void  twitterak::set_hashtag(string hashtag , tweet* tweet)
{
    hashtags[hashtag].push_back(tweet);
}

//void twitterak::get_hashtag(string hashtag)
//{
//        string copy;
//        copy = hashtag.substr(1, hashtag.size() - 1);

//        for(auto i: hashtags[copy])
//        {
//            cout << i->get_post()<<endl;
//        }
//}


//void twitterak::changeheader(string header = "white")
//{
//    if(header == "yellow")
//    {
//        system("color 06");
//    }

//    else if(header == "blue")
//    {
//        system("color 03");
//    }

//    else if(header == "red")
//    {
//        system("color 04");
//    }

//    else if(header == "purple")
//    {
//        system("color 05");
//    }

//    else if(header == "green")
//    {
//        system("color 02");
//    }

//    else if (header == "white")
//    {
//        system("color 07");
//    }

//    else
//    cout << "! Wrong command. Please choose a color from list";
        
//}


//seperator sensitive to space. using for seperating command and entered information.
void twitterak::seperator(string key, vector <string> &command)
{   
    command.clear();
    int j = 0;

    for(int i = 0; i < key.size(); i++)
    {   
        if(key[i] == ' ')
        j = i;

        else break;
    }

    j = (j > 0) + j;
    key = key.substr(j, key.size());

    string key2;
    stringstream copy(key);

    while(getline(copy, key2, ' '))
    {
        command.push_back(key2);
    }
}
//overload sepereator
void twitterak :: seperator(string &key)
{
    int j = 0;
    for(int i = 0; i < key.size(); i++)
    {   
        if(key[i] == ' ')
        j = i;

        else break;
    }

    j = (j > 0) + j;
    key = key.substr(j, key.size());

}

bool twitterak::check_user(string username)
{   

   if( users.count(username))
   {    
        return 1;
   } 

   else return 0;
}

bool twitterak :: checknum(int index, user* choise)
{   
    
    if(choise->check(index))
    return 1;

    else return 0;
}

void twitterak::DisLike(user* currentuser, user* target, int index)
{
    currentuser->dislike(currentuser, target, index);
}

//get passwrod and print * instead of

string twitterak::getpassword( const string& prompt = "$password: ")
{
  string result;

  // Set the console mode to no-echo, not-line-buffered input
  DWORD mode, count;
  HANDLE ih = GetStdHandle( STD_INPUT_HANDLE  );
  HANDLE oh = GetStdHandle( STD_OUTPUT_HANDLE );
  if (!GetConsoleMode( ih, &mode ))
    throw runtime_error(
      "getpassword: You must be connected to a console to use this program.\n"
      );
  SetConsoleMode( ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

  // Get the password string
  WriteConsoleA( oh, prompt.c_str(), prompt.length(), &count, NULL );
  char c;
  while (ReadConsoleA( ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
    {
    if (c == '\b')
      {
      if (result.length())
        {
        WriteConsoleA( oh, "\b \b", 3, &count, NULL );
        result.erase( result.end() -1 );
        }
      }
    else
      {
      
      cout << c;
      Sleep(190);
      WriteConsoleA( oh, "\b \b", 3, &count, NULL );
      WriteConsoleA( oh, "*", 1, &count, NULL );
      result.push_back( c );
      }
    }

    cin.ignore();
  // Restore the console mode
  SetConsoleMode( ih, mode );

  return result;
}

int twitterak::check_typeuser()
{   
    int choice = 0;

    while(1)
    {
        cout << "1.anonymous user" << "\n2.personal user" << "\n" << "3.organization user \n";
        cout << "enter your choise number: ";
        cin >> choice;

        if(choice == 1 || choice == 2 || choice == 3)
        {   
            cin.ignore();
            return choice;
        }

        else cout << "wrong choice! try again." << endl;
    } 
    
}

//Function to get time and date from pc.
string twitterak:: SystemCurrentTime()
{
    time_t t;
    struct tm *tt;
    time(&t);
    tt = localtime(&t);
    string time = asctime(tt);
    return time;
}

void twitterak::store_user_infile()
{   
    remove("user.txt");

    ordinaryuser *oduser = nullptr;
    orguser *oguser = nullptr;
    anonymous *anonyuser = nullptr;


    fstream ufile;
    bool flag = 1;
    ufile.open("user.txt", ios::app);

    for(auto i : users)
    {   
        if(flag)
        {
            flag = 0;
        }
        else ufile << '\n';
        
        if((oduser = dynamic_cast<ordinaryuser*>(i.second)) != NULL)
        ufile << "username: " << i.second->get_username() + 'P' << '\n';

        if((oguser = dynamic_cast<orguser*>(i.second)) != NULL)
        ufile << "username: " << i.second->get_username() + 'O' << '\n';

        if((anonyuser = dynamic_cast<anonymous*>(i.second)) != NULL)
        ufile << "username: " << i.second->get_username() + 'A' << '\n';

        ufile << "name: " << i.second->get_name() << '\n';

        ufile << "country: " << i.second->get_country() << '\n';
        
        if(i.second->get_link() == "")
        ufile << "link: " << "_" << '\n';

        else ufile << "link: " << i.second->get_link() << '\n';
        
        ufile << "biography: " << i.second->get_biography() <<'\n';

        ufile << "birthday: "<< i.second->get_birthday() << '\n';

        ufile << "phonenumber: "<< i.second->get_phonenumber() << '\n';

        ufile << "password: " << i.second->get_password() << '\n';

        if(i.second->get_header() == "")
        ufile << "header: " << "_" << '\n';

        else ufile << "header: " << i.second->get_header() << '\n';
        
        ufile << "=======================================";
    }

    ufile.close();
}

date twitterak::seperate_time(string birth)
{
    stringstream temp(birth), copy;
    string year, month, day;
    int y, m, d;
    date birthday;

    getline(temp, year, '/');
    getline(temp, month, '/');
    getline(temp, day, '/');
    
    copy.clear();

    copy << year;
    copy >> y;

    copy.clear();

    copy << month;
    copy >> m;

    copy.clear();

    copy << day;
    copy >> d;

    birthday.year = y;
    birthday.month = m;
    birthday.day = d;

    return birthday;

}

void twitterak::read_file()
{
    string username, name, bio, link, birthday, phone, password, header, country;

    fstream ufile;
    ufile.open("user.txt", ios::in);

    if(ufile.is_open())
    {
        while(!ufile.eof())
        {
            ufile >> username >> username;
            ufile >> name >> name;
            ufile >> country >> country;
            ufile >> link >> link;
            ufile >> bio >> bio;
            ufile >> birthday >> birthday;
            ufile >> phone >> phone;
            ufile >> password >> password;
            ufile >> header >> header;

            if(username[username.size() - 1] == 'A')
            {
                username = username.substr(0,username.size() - 1);

                currentuser = new anonymous;
            }

            else if(username[username.size() - 1] == 'O')
            {
                username = username.substr(0,username.size() - 1);

                currentuser = new orguser;
            }


            else if(username[username.size() - 1] == 'P')
            {
                username = username.substr(0,username.size() - 1);

                currentuser = new ordinaryuser;
            }

            currentuser->set_username(username);

            currentuser->set_name(name);

            if(bio != "_")
            currentuser->set_biography(bio);

            if(country != "_")
            currentuser->set_country(country);

            if(link != "_")
            currentuser->set_link(link);

            if(birthday != "_")
            currentuser->set_birthday(seperate_time(birthday));

            if(phone != "_")
            currentuser->set_phonenumber(phone);

            currentuser->set_password(password);

            if(header != "_")
            currentuser->set_header(header);

            users[currentuser->get_username()] = currentuser;
           
            ufile.ignore(40);

        }
        
        ufile.close();
    }

}

void twitterak::stor_tweet_infile()
{   
    remove("Tweets.txt");
    
    for(auto i: users)
    {
        i.second->save_in_file();
    }
}

void twitterak::get_from_file()
{   

    fstream input;
    input.open("Tweets.txt", ios::in);

    if(input.is_open())
    {
        while(!input.eof())
        {
            string username;

            input >> username;

            if(username == "")
            {
                break;
            }

            while(1)
            {   
                string tweet, likes, date, index;
                stringstream toindex;
                int indx;

                input >> index;

                if(index == "****")
                {   
                    input.ignore(1);
                    break;
                }

                index.pop_back();
                toindex << index;
                toindex >> indx;

                getline(input, tweet);

                tweet = tweet.substr(1, tweet.size());
                
                getline(input, date);

                input >>likes;
                date += '\n';


                users[username]->Set_filetweet(tweet, date);

                while(1)
                {   
                    input >>likes;

                    if(likes == "----")
                    {   
                        input.ignore(1);
                        break;
                    }
                    
                    users[username]->fget_like(users[likes], indx);
                }
            }
        }

        input.close();
    }
}

void twitterak::store_follower_following_infile()
{   
    fstream ufile;
    bool flag = 1;

    ufile.open("follow.txt", ios::out);

    for(auto i : users)
    {
        if(i.second->display_followers() != 0)
        {   
            if(flag)
            {
                ufile << i.second->get_username() << '\n';
                flag = 0;
            }

            else ufile << '\n' << i.second->get_username() << '\n';

            ufile << "followers: ";

            for(int j = 0; j < i.second->display_followers(); j++)
            {
                ufile << i.second->get_followers(j) << " ";
            }

            ufile << "\n";    
            ufile << "--------------------";
        }
    }

    ufile.close();
}

void twitterak::get_follower_following_infile()
{       

    fstream ufile;
    ufile.open("follow.txt", ios::in);

    if(ufile.is_open())
    {   
        while(!ufile.eof())
        {   
            
            string followers, followings, username;
            ufile >> username;

            if(username == "")
            {
                break;
            }

            ufile >> followings;


            while (1)
            {   
                ufile >> followers;

                if(followers == "--------------------")
                {   
                    break;
                }

                users[followers]->fadd_following(users[username]);

            }     
        }

        ufile.close();
    }

}

void twitterak::write_hashtag_infile()
{
    fstream input;
    bool flag = 1;
    input.open("hashtags.txt", ios::out);
    
        for(auto i: hashtags)
        {   
            if(flag)
            {
                input << i.first << ": ";
                flag = 0;
            }
            
            else input << '\n' << i.first << ": ";

            for(auto j : i.second)
            {
                input << j->get_post() << endl;
            }

            input << "------------";
        }
        
    input.close();
    
}

void twitterak::read_hashtag_fromfile()
{
    fstream output;
    output.open("hashtags.txt", ios::in);


    if(output.is_open())
    {
        string hashtags, temp;
        tweet *post = nullptr;

        while(output >> hashtags)
        {   
            
            hashtags.pop_back();


            while(getline(output, temp))
            {  
                post = new tweet;

                if(temp == "------------")
                {   
                    break;
                }
                
                post->set_post(temp);

                temp = temp.substr(1, temp.size());
                
                set_hashtag(hashtags, post);
            }
        }

        output.close();
    }
}




