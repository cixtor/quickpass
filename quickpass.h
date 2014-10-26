#ifndef QUICKPASS_H
#define QUICKPASS_H

#include <QMainWindow>

namespace Ui {
    class Quickpass;
}

class Quickpass : public QMainWindow {
    Q_OBJECT

public:
    explicit Quickpass(QWidget *parent = 0);
    QString Accounts;
    QString GetAccounts();
    QString GetAccountFilepath();
    ~Quickpass();

private slots:
    void on_editModeCheckbox_clicked();
    void on_generateNewAccount_clicked();
    void on_saveFileBtn_clicked();
    void on_searchEntry_returnPressed();

private:
    Ui::Quickpass *ui;
    QString GetAccount();
    bool IsEditable();
    bool IsRequestedAccount(QString, QString);
    void ResetTextBuffer();
    bool SaveAccountChanges();
    void SetEditMode(bool);

};

#endif // QUICKPASS_H
