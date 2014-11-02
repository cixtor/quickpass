#ifndef QUICKPASS_H
#define QUICKPASS_H

#include <QMainWindow>
#include <QFile>

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
    QList<QString> GeneratePassword(QString, int, int, QString);
    int InsertNewAccountData(QString);
    ~Quickpass();

private slots:
    void on_editModeCheckbox_clicked();
    void on_generateNewAccount_clicked();
    void on_generateNewPassword_clicked();
    void on_saveFileBtn_clicked();
    void on_searchEntry_returnPressed();

private:
    Ui::Quickpass *ui;
    QString GetAccount();
    QString GetPasswordTypeChars(QString, QString);
    bool IsEditable();
    bool IsFileUsable(QFile&);
    bool IsRequestedAccount(QString, QString);
    void ResetTextBuffer();
    bool SaveAccountChanges();
    void SetEditMode(bool);

};

#endif // QUICKPASS_H
