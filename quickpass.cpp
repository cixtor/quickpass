#include "quickpass.h"
#include "newaccount.h"
#include "newpassword.h"
#include "ui_newaccount.h"
#include "ui_newpassword.h"
#include "ui_quickpass.h"

#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

#define ACCOUNT_FILENAME "accounts.txt"
#define ACCOUNT_DELIMITER "~~~"
#define ACCOUNT_PATTERN "^~~~"
#define TYPE_ALPHA_LOWER "abcdefghijklmnopqrstuvwxyz"
#define TYPE_ALPHA_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define TYPE_SPECIAL "!@$%&*_+=-_?/.,:;#"
#define TYPE_NUMERIC "0123456789"

Quickpass::Quickpass(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Quickpass) {
  ui->setupUi(this);
}

NewAccount::NewAccount(QWidget *parent)
    : QWidget(parent), ui(new Ui::NewAccount) {
  ui->setupUi(this);
}

NewPassword::NewPassword(QWidget *parent)
    : QWidget(parent), ui(new Ui::NewPassword) {
  ui->setupUi(this);
}

QString Quickpass::GetAccountFilepath() {
  return qApp->applicationDirPath() + "/" + ACCOUNT_FILENAME;
}

void Quickpass::LoadCurrentAccounts() { ui->textView->setText(GetAccounts()); }

QString Quickpass::GetAccounts() {
  QString textViewContent;
  QFile file(GetAccountFilepath());

  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    in.setCodec("UTF-8");

    int count(0);
    while (!in.atEnd()) {
      count += 1;
      QString line = in.readLine();
      textViewContent += line + "\n";
    }

    Accounts = textViewContent;
    ui->statusBar->showMessage("Accounts file loaded.", 1000);
    file.close();
  } else {
    ui->statusBar->showMessage("Accounts file is not readable.", 3000);
  }

  return Accounts;
}

void Quickpass::ResetTextBuffer() { ui->textView->clear(); }

bool Quickpass::IsRequestedAccount(QString requestedAccount,
                                   QString accountCredentials) {
  QStringList lines = accountCredentials.split(QRegExp("\n"));

  for (QStringList::iterator it = lines.begin(); it != lines.end(); it++) {
    QString currentLine = *it;

    if (currentLine.contains(QRegExp(requestedAccount))) {
      return true;
    }
  }

  return false;
}

bool Quickpass::IsFileUsable(QFile &file) {
  if (file.exists()) {
    QFileInfo fileInfo(file);

    return fileInfo.isWritable();
  }

  return false;
}

QString Quickpass::GetAccount() {
  int accountsFound(0);
  QString multipleAccounts;
  QString accountCredentials;
  QString requestedAccount = ui->searchEntry->text();

  if (requestedAccount.isEmpty()) {
    return Accounts;
  }

  QRegExp rx("\n");
  QStringList lines = Accounts.split(rx);

  for (QStringList::iterator it = lines.begin(); it != lines.end(); it++) {
    QString currentLine = *it;

    if (currentLine.contains(QRegExp(ACCOUNT_PATTERN))) {
      if (IsRequestedAccount(requestedAccount, accountCredentials)) {
        accountsFound += 1;
        multipleAccounts += accountCredentials;
        multipleAccounts += ACCOUNT_DELIMITER;
        multipleAccounts += "\n";
      }

      accountCredentials = "";
    } else {
      accountCredentials += currentLine + "\n";
    }
  }

  ui->statusBar->showMessage(QString::number(accountsFound) +
                             " accounts found.");

  return multipleAccounts;
}

QString Quickpass::GetPasswordTypeChars(QString typeName) {
  QString dictionary;

  if (typeName == "all") {
    dictionary += TYPE_ALPHA_LOWER;
    dictionary += TYPE_ALPHA_UPPER;
    dictionary += TYPE_SPECIAL;
    dictionary += TYPE_NUMERIC;
  } else if (typeName == "alpha_lower") {
    dictionary = TYPE_ALPHA_LOWER;
  } else if (typeName == "alpha_upper") {
    dictionary = TYPE_ALPHA_UPPER;
  } else if (typeName == "special") {
    dictionary = TYPE_SPECIAL;
  } else if (typeName == "numeric") {
    dictionary = TYPE_NUMERIC;
  }

  return dictionary;
}

QList<QString> Quickpass::GeneratePassword(QString dictionary, int length,
                                           int quantity) {
  QList<QString> passwordList;
  int dictionaryLength = dictionary.length();

  if (dictionaryLength > 0) {
    for (int i = 0; i < quantity; i++) {
      QString password;

      for (int j = 0; j < length; j++) {
        int index = arc4random() % dictionaryLength;
        QChar nextChar = dictionary.at(index);
        password.append(nextChar);
      }

      passwordList.append(password);
    }
  }

  return passwordList;
}

bool Quickpass::SaveAccountChanges() {
  QFile file(GetAccountFilepath());

  if (IsFileUsable(file)) {
    QString currentTextBuffer = ui->textView->toPlainText();

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      out << currentTextBuffer;
      file.close();

      return true;
    }
  }

  return false;
}

int Quickpass::InsertNewAccountData(QString account_info) {
  if (account_info.isEmpty()) {
    QMessageBox::warning(this, "Quickpass warning",
                         "Can not save empty information.\n"
                         "Add at least a username and password.");

    return 2;
  }

  QFile file(GetAccountFilepath());

  if (file.open(QIODevice::Append | QIODevice::WriteOnly)) {
    QTextStream out(&file);
    out << ACCOUNT_DELIMITER;
    out << "\n";
    out << account_info;
    file.close();

    return 0;
  }

  return 1;
}

void Quickpass::SetEditMode(bool enabled = false) {
  if (enabled) {
    ui->editModeCheckbox->setChecked(true);
    ui->textView->setReadOnly(false);
    ui->saveFileBtn->setEnabled(true);
  } else {
    ui->editModeCheckbox->setChecked(false);
    ui->textView->setReadOnly(true);
    ui->saveFileBtn->setEnabled(false);
  }
}

bool Quickpass::IsEditable() { return ui->editModeCheckbox->isChecked(); }

void Quickpass::on_searchEntry_returnPressed() {
  ui->textView->setText(GetAccount());
}

void Quickpass::on_saveFileBtn_clicked() {
  if (IsEditable()) {
    SaveAccountChanges();
    ui->textView->setText(GetAccounts());
    ui->statusBar->showMessage("Changes saved successfully.", 3000);
  } else {
    QMessageBox::critical(this, "Quickpass error",
                          "Error saving data in file.\n"
                          "Edit mode is disabled.");
  }
}

void Quickpass::on_editModeCheckbox_clicked() {
  bool editModeEnabled = IsEditable();
  QString editModeState = "enabled";

  if (!editModeEnabled) {
    editModeState = "disabled";
  }

  SetEditMode(editModeEnabled);

  ui->statusBar->showMessage("Edit mode " + editModeState, 3000);
}

void Quickpass::on_generateNewAccount_clicked() {
  QWidget *widget = new NewAccount;
  widget->show();
}

void Quickpass::on_generateNewPassword_clicked() {
  QWidget *widget = new NewPassword;
  widget->show();
}

void NewAccount::on_accountAcceptedBtn_clicked() {
  Quickpass quickpass;
  QString new_account_str;

  QString uniqueid = ui->uniqueIdInput->text();
  QString hostname = ui->hostnameInput->text();
  QString username = ui->usernameInput->text();
  QString password = ui->passwordInput->text();
  QString moreinfo = ui->extraInfoInput->toPlainText();

  if (!uniqueid.isEmpty()) {
    new_account_str += "uniqueid: " + uniqueid + "\n";
  }

  if (!hostname.isEmpty()) {
    new_account_str += "hostname: " + hostname + "\n";
  }

  if (!username.isEmpty()) {
    new_account_str += "username: " + username + "\n";
  }

  if (!password.isEmpty()) {
    new_account_str += "password: " + password + "\n";
  }

  if (!moreinfo.isEmpty()) {
    new_account_str += "moreinfo:\n" + moreinfo + "\n";
  }

  int newAccountSaved = quickpass.InsertNewAccountData(new_account_str);

  if (newAccountSaved == 0) {
    NewAccount::close();
  } else if (newAccountSaved == 1) {
    QMessageBox::critical(this, "Quickpass error",
                          "Could not save new account information.\n"
                          "Close the window and try again.");
  }
}

void NewAccount::on_generatePasswordBtn_clicked() {
  Quickpass quickpass;
  QString dictionary = quickpass.GetPasswordTypeChars("all");
  QList<QString> passwordList = quickpass.GeneratePassword(dictionary, 15, 1);

  ui->passwordInput->setText(passwordList[0]);
}

void NewAccount::on_accountRejectedBtn_clicked() { NewAccount::close(); }

void NewPassword::on_generateBtn_clicked() {
  Quickpass quickpass;

  QString dictionary;
  int length = ui->lengthInput->text().toInt();
  int quantity = ui->quantityInput->text().toInt();
  QString customChars = ui->typeCustomInput->text();

  ui->passwordListInput->setText("");

  if (length <= 0) {
    length = 25;
  }

  if (quantity <= 0) {
    quantity = 5;
  }

  if (ui->typeAlphaLowerCheckbox->isChecked()) {
    dictionary += quickpass.GetPasswordTypeChars("alpha_lower");
  }

  if (ui->typeAlphaUpperCheckbox->isChecked()) {
    dictionary += quickpass.GetPasswordTypeChars("alpha_upper");
  }

  if (ui->typeNumericCheckbox->isChecked()) {
    dictionary += quickpass.GetPasswordTypeChars("numeric");
  }

  if (ui->typeSpecialCheckbox->isChecked()) {
    dictionary += quickpass.GetPasswordTypeChars("special");
  }

  if (!customChars.isEmpty()) {
    dictionary += customChars;
  }

  if (!dictionary.isEmpty()) {
    QList<QString> passwordList =
        quickpass.GeneratePassword(dictionary, length, quantity);

    for (int i = 0; i < passwordList.size(); i++) {
      ui->passwordListInput->append(passwordList[i]);
    }
  }
}

void NewPassword::on_cancelBtn_clicked() { NewPassword::close(); }

Quickpass::~Quickpass() { delete ui; }

NewAccount::~NewAccount() { delete ui; }

NewPassword::~NewPassword() { delete ui; }
