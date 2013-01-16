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
		AccountForm *getNewAccountForm() const;
};

class Accounts::AccountForm : public QWidget {
	public:
		AccountForm();
		bool validate();
	
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
