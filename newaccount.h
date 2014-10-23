#ifndef NEWACCOUNT_H
#define NEWACCOUNT_H

#include <QDialog>

namespace Ui {
    class NewAccount;
}

class NewAccount : public QDialog {
    Q_OBJECT

public:
    explicit NewAccount(QWidget *parent = 0);
    ~NewAccount();

private:
    Ui::NewAccount *ui;

};

#endif // NEWACCOUNT_H
