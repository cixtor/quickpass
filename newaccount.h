#ifndef NEWACCOUNT_H
#define NEWACCOUNT_H

#include <QWidget>

namespace Ui {
class NewAccount;
}

class NewAccount : public QWidget {
  Q_OBJECT

public:
  explicit NewAccount(QWidget *parent = nullptr);
  ~NewAccount();

private slots:
  void on_accountAcceptedBtn_clicked();
  void on_accountRejectedBtn_clicked();
  void on_generatePasswordBtn_clicked();

private:
  Ui::NewAccount *ui;
};

#endif // NEWACCOUNT_H
