#include "quickpass.h"
#include "ui_quickpass.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>

Quickpass::Quickpass(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Quickpass)
{
    ui->setupUi(this);
    AccountsFilepath = qApp->applicationDirPath() + "/accounts.txt";
	ui->textView->setText( GetAccounts() );
    SetEditMode(false);
}

QString Quickpass::GetAccounts(){
    QString textViewContent;
    QFile file(AccountsFilepath);

    if( file.open(QIODevice::ReadOnly | QIODevice::Text) ){
        QTextStream in(&file);
        in.setCodec("UTF-8");

        int count(0);
        while( !in.atEnd() ){
            count += 1;
            QString line = in.readLine();
            textViewContent += line + "\n";
        }

        Accounts = textViewContent;
        ui->statusBar->showMessage("Accounts file loaded!", 1000);
        file.close();
    }else{
        ui->statusBar->showMessage("Error. Accounts file is not readable.", 3000);
    }

    return Accounts;
}

void Quickpass::ResetTextBuffer(){
    ui->textView->clear();
}

bool Quickpass::IsRequestedAccount(QString requestedAccount, QString accountCredentials){
    QStringList lines = accountCredentials.split( QRegExp("\n") );
    for( QStringList::iterator it=lines.begin(); it!=lines.end(); it++ ){
        QString currentLine = *it;
        if( currentLine.contains(QRegExp(requestedAccount)) ){
            return true;
        }
    }
    return false;
}

QString Quickpass::GetAccount(){
    int accountsFound(0);
    QString multipleAccounts;
    QString accountCredentials;
    QString requestedAccount = ui->searchEntry->text();

	if( requestedAccount.isEmpty() ){
		return Accounts;
    }else{
        QRegExp rx("\n");
        QStringList lines = Accounts.split(rx);

        for( QStringList::iterator it=lines.begin(); it!=lines.end(); it++ ){
            QString currentLine = *it;
            if( currentLine.contains( QRegExp("^===") ) ){
                if( IsRequestedAccount(requestedAccount, accountCredentials) ){
                    accountsFound += 1;
                    multipleAccounts += accountCredentials+"===\n";
                }
                accountCredentials = "";
            }else{
                accountCredentials += currentLine+"\n";
            }
        }
    }
    ui->statusBar->showMessage("Found "+QString::number(accountsFound)+" accounts.");

    return multipleAccounts;
}

void Quickpass::SaveAccountChanges(){
    bool fileIsWritable = true;
    QFile file(AccountsFilepath);
    if( file.exists() ){
        QFileInfo fileInfo(file);
        fileIsWritable = fileInfo.isWritable();
    }

    if( fileIsWritable ){
        QString currentTextBuffer = ui->textView->toPlainText();
        if( file.open(QIODevice::WriteOnly | QIODevice::Text) ){
            QTextStream out(&file);
            out << currentTextBuffer;
            file.close();
        }
    }
}

void Quickpass::SetEditMode(bool enabled=false){
    if( enabled == true ){
        ui->editModeCheckbox->setChecked(true);
        ui->textView->setReadOnly(false);
    }else{
        ui->editModeCheckbox->setChecked(false);
        ui->textView->setReadOnly(true);
    }
}

void Quickpass::on_searchEntry_returnPressed(){
    ui->textView->setText( GetAccount() );
}

void Quickpass::on_saveFileBtn_clicked(){
    SaveAccountChanges();
    ui->textView->setText( GetAccounts() );
    ui->statusBar->showMessage("Changes made saved!", 3000);
}

void Quickpass::on_editModeCheckbox_clicked(){
    bool editModeEnabled = ui->editModeCheckbox->isChecked();
    SetEditMode(editModeEnabled);

    QString editModeState = editModeEnabled ? "enabled" : "disabled";
    ui->statusBar->showMessage("Edit mode "+editModeState, 3000);
}

Quickpass::~Quickpass()
{
    delete ui;
}
