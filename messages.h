#ifndef MESSAGES_H
#define MESSAGES_H

#include <QWidget>

#include "unordered_map"
#include "user.hpp"

namespace Ui {
class messages;
}

class messages : public QWidget
{
    Q_OBJECT

public:
    explicit messages(QWidget *parent = nullptr);
    ~messages();

private:
    Ui::messages *ui;
};

#endif // MESSAGES_H
