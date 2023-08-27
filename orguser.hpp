#ifndef ORGUSER_HPP
#define ORGUSER_HPP

#include <iostream>
#include "user.hpp"

using namespace std;

class orguser : public user
{       
    public:
    int get_age();
    void set_birthday();
    string get_birthday();
    bool validatebio(string bio);
    bool validatebirthday(date birthday);
    void display_followings();
    void print();
};

#endif