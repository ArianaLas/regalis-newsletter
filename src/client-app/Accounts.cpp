#include <QLabel>
#include <QGridLayout>
#include "Accounts.hpp"

Accounts::Accounts() {

}

Accounts::AccountForm *Accounts::getNewAccountForm() const {
	return new AccountForm();
}

Accounts::AccountForm::AccountForm() {
	QLabel *name_label = new QLabel(tr("Name:"));
	name = new QLineEdit();
	name_label->setBuddy(name);

	QLabel *email_label = new QLabel(tr("Email:"));
	email = new QLineEdit();
	email_label->setBuddy(email);

	QLabel *from_label = new QLabel(tr("From:"));
	from = new QLineEdit();
	from_label->setBuddy(from);

	QLabel *host_label = new QLabel(tr("SMTP Host:"));
	host = new QLineEdit();
	host_label->setBuddy(host);

	QLabel *user_label = new QLabel(tr("User:"));
	user = new QLineEdit();
	user_label->setBuddy(user);

	QLabel *pass_label = new QLabel(tr("Password:"));
	pass = new QLineEdit();
	pass->setEchoMode(QLineEdit::Password);
	pass_label->setBuddy(pass);

	QLabel *port_label = new QLabel(tr("SMTP Port:"));
	port = new QLineEdit("25");
	port->setInputMask("999999999");
	port_label->setBuddy(port);

	QLabel *description_label = new QLabel(tr("Description:"));
	description = new QTextEdit();
	description_label->setBuddy(description);

	QGridLayout *layout = new QGridLayout();

	layout->addWidget(name_label, 0, 0, Qt::AlignRight);
	layout->addWidget(name, 0, 1);

	layout->addWidget(email_label, 1, 0, Qt::AlignRight);
	layout->addWidget(email, 1, 1);

	layout->addWidget(from_label, 2, 0, Qt::AlignRight);
	layout->addWidget(from, 2, 1);

	layout->addWidget(host_label, 3, 0, Qt::AlignRight);
	layout->addWidget(host, 3, 1);

	layout->addWidget(port_label, 4, 0, Qt::AlignRight);
	layout->addWidget(port, 4, 1);

	layout->addWidget(user_label, 5, 0, Qt::AlignRight);
	layout->addWidget(user, 5, 1);

	layout->addWidget(pass_label, 6, 0, Qt::AlignRight);
	layout->addWidget(pass, 6, 1);

	layout->addWidget(description_label, 7, 0, Qt::AlignRight | Qt::AlignTop);
	layout->addWidget(description, 7, 1);

	layout->setColumnMinimumWidth(1, 250);
	setLayout(layout);

}

bool Accounts::AccountForm::validate() {
	if (name->text().isEmpty() || email->text().isEmpty() ||
		from->text().isEmpty() || host->text().isEmpty() ||
		user->text().isEmpty() || pass->text().isEmpty() ||
		port->text().isEmpty()) {
		error_msg = "Some fields are empty";
		return false;
	}
	// TODO: Check server connection
}
