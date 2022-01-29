#ifndef NEWPASSWORD_H
#define NEWPASSWORD_H

#include <QWidget>

class Quickpass;

namespace Ui {
class NewPassword;
}

class NewPassword : public QWidget {
  Q_OBJECT

public:
  explicit NewPassword(Quickpass *owner, QWidget *parent = nullptr);
  ~NewPassword();

private slots:
  void on_generateBtn_clicked();
  void on_cancelBtn_clicked();

private:
  Ui::NewPassword *ui;
  Quickpass *quickpass;
};

#endif // NEWPASSWORD_H
