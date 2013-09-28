#ifndef QUICKPASS_H
#define QUICKPASS_H

#include <QMainWindow>

namespace Ui {
class Quickpass;
}

class Quickpass : public QMainWindow
{
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

private:
    Ui::Quickpass *ui;
    void ResetTextBuffer();
    QString GetAccount();
    bool IsRequestedAccount(QString, QString);
    void SaveAccountChanges();
    void SetEditMode(bool);
};

#endif // QUICKPASS_H
