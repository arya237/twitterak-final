#include "messages.h"

#include "ui_messages.h"
#include "user.hpp"

messages::messages(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::messages)
{
    ui->setupUi(this);
}

messages::~messages()
{
    delete ui;
}
