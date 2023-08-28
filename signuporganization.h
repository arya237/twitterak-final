#ifndef SIGNUPORGANIZATION_H
#define SIGNUPORGANIZATION_H

#include <QMainWindow>

namespace Ui {
class SignupOrganization;
}

class SignupOrganization : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignupOrganization(QWidget *parent = nullptr);
    ~SignupOrganization();

    void validate();

private slots:
    void on_btn_back_clicked();

    void on_btn_signup_clicked();

private:
    Ui::SignupOrganization *ui;
    std::string profile;
};

#endif // SIGNUPORGANIZATION_H
