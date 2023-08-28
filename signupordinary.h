#ifndef SIGNUPORDINARY_H
#define SIGNUPORDINARY_H

#include <QMainWindow>

namespace Ui {
class SignupOrdinary;
}

class SignupOrdinary : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignupOrdinary(QWidget *parent = nullptr);
    ~SignupOrdinary();
     bool validatepass(std::string password);

     bool validateuser(std::string usernmae);

private slots:
    void on_btn_back_clicked();

    void on_btn_signup_clicked();


    void on_ln_password_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_btn_shopassword_clicked();

    void on_ln_username_textChanged(const QString &arg1);

private:
    Ui::SignupOrdinary *ui;
    std::string profile;
};

#endif // SIGNUPORDINARY_H
