#ifndef SIGNUPANONYMOUS_H
#define SIGNUPANONYMOUS_H

#include <QMainWindow>

namespace Ui {
class SignupAnonymous;
}

class SignupAnonymous : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignupAnonymous(QWidget *parent = nullptr);
    ~SignupAnonymous();

private slots:
    void on_btn_back_clicked();

    void on_btn_signup_clicked();

private:
    Ui::SignupAnonymous *ui;
};

#endif // SIGNUPANONYMOUS_H
