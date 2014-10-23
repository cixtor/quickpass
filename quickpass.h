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
    QString AccountsFilepath;
    QString Accounts;
    QString GetAccounts();
    ~Quickpass();

private slots:
    void on_searchEntry_returnPressed();
    void on_saveFileBtn_clicked();
    void on_editModeCheckbox_clicked();
    void on_generateNewAccount_clicked();

private:
    Ui::Quickpass *ui;
    void ResetTextBuffer();
    QString GetAccount();
    bool IsRequestedAccount(QString, QString);
    bool SaveAccountChanges();
    void SetEditMode(bool);
    bool IsEditable();

};

#endif // QUICKPASS_H
