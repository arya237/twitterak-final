#ifndef CHOOSEACCOUNT_H
#define CHOOSEACCOUNT_H

#include <QMainWindow>

namespace Ui {
class ChooseAccount;
}

class ChooseAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseAccount(QWidget *parent = nullptr);
    ~ChooseAccount();

private slots:
    void on_btn_ord_clicked();

    void on_btn_org_clicked();

    void on_btn_anon_clicked();

    void on_btn_back_clicked();

private:
    Ui::ChooseAccount *ui;
};

#endif // CHOOSEACCOUNT_H
