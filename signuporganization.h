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

    bool validatepass(std::string password);

    bool validateuser(std::string username);

private slots:
    void on_btn_back_clicked();

    void on_btn_signup_clicked();

    void on_btn_showpassword_clicked();

    void on_ln_password_textChanged(const QString &arg1);

    void on_ln_username_textChanged(const QString &arg1);

    void on_txt_bio_textChanged();

    void on_btn_profile_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);
private:
    Ui::SignupOrganization *ui;
    std::string profile;
};

#endif // SIGNUPORGANIZATION_H
