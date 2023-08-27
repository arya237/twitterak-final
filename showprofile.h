#ifndef SHOWPROFILE_H
#define SHOWPROFILE_H

#include <QWidget>
#include "user.hpp"

namespace Ui {
class showprofile;
}

class showprofile : public QWidget
{
    Q_OBJECT

public:
    explicit showprofile(user*, user*, unordered_map<string, user*> &, QWidget *parent = nullptr);
    ~showprofile();
    void set();

private slots:

    void on_btn_follow_clicked();

private:
    Ui::showprofile *ui;
    user * target;
    user * me;
    unordered_map<string, user*> users;
};

#endif // SHOWPROFILE_H
