#ifndef NOTIFACTIONS_H
#define NOTIFACTIONS_H

#include <QWidget>
#include <unordered_map>
#include "user.hpp"
#include "QListWidgetItem"

namespace Ui {
class notifactions;
}

class notifactions : public QWidget
{
    Q_OBJECT

public:
    explicit notifactions(unordered_map<string, user*> &porpose, user* currentuser, QWidget *parent = nullptr);
    ~notifactions();

private slots:
    void on_listWidget_messages_itemClicked(QListWidgetItem *item);

private:
    Ui::notifactions *ui;
    unordered_map<string, user*> users;
    user* currentuser;
};

#endif // NOTIFACTIONS_H
