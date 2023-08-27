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

private slots:
    void on_btn_back_clicked();

    void on_btn_signup_clicked();


    void on_ln_password_textChanged(const QString &arg1);

private:
    Ui::SignupOrdinary *ui;
};

#endif // SIGNUPORDINARY_H
