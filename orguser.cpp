#include <iostream>
#include"orguser.hpp"

bool orguser::validatebio(string bio)
{   try
    {
        if(bio.size() > 1100)
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

bool orguser::validatebirthday(date birthday)
{

}

void orguser::set_birthday()
{
    
}

void orguser::display_followings()
{

}

string orguser::get_birthday()
{
    return "_";
}

int orguser::get_age()
{
    return -1;
}

void orguser::print()
{
    cout << "|------------------------------------|" << endl;
    cout << "|                                    |" << endl;
    cout << "|              "<< "WELCOME"<<"               |" << endl;
    cout << "|                                    |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "                 | |                " << endl;
    cout << "                 | |                " <<endl;
    

    cout <<"username: "<< get_username() <<endl<< "name: " << get_name()<< endl << "biography : " << get_biography() << endl 
    << "link : " << get_link() << endl << "country : " << get_country() << endl << "phonenumber: " <<
    get_phonenumber() << endl;
}