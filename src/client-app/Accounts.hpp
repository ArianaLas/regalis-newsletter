#ifndef __ACCOUNTS_HPP_
#define __ACCOUNTS_HPP_

#include <QLineEdit>
#include <QTextEdit>
#include <QWidget>
#include <QString>

class Accounts {
	public:
		Accounts();
		class AccountForm;
		static AccountForm *getNewAccountForm();
};

class Accounts::AccountForm : public QWidget {
	public:
		AccountForm();
		bool validate();
		bool insert();
		QString getName() const;
		QString getEmail() const;
		QString getFrom() const;
		QString getHost() const;
		QString getUser() const;
		QString getPass() const;
		QString getPort() const;
		QString getDescription() const;
		QString getErrorMessage() const;
	
	protected:
		QLineEdit *name;
		QLineEdit *email;
		QLineEdit *from;
		QLineEdit *host;
		QLineEdit *user;
		QLineEdit *pass;
		QLineEdit *port;
		QTextEdit *description;
		QString error_msg;
};

#endif
