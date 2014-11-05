#ifndef NEWPASSWORD_H
#define NEWPASSWORD_H

#include <QWidget>

namespace Ui {
    class NewPassword;
}

class NewPassword : public QWidget {
    Q_OBJECT

public:
    explicit NewPassword(QWidget *parent = 0);
    ~NewPassword();

private slots:
    void on_generateBtn_clicked();
    void on_cancelBtn_clicked();

private:
    Ui::NewPassword *ui;

};

#endif // NEWPASSWORD_H
