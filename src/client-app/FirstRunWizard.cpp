#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QString>
#include <QSqlError>

#include "RegalisNewsletter.hpp"
#include "FirstRunWizard.hpp"
#include "Accounts.hpp"
#include "version.hpp"

FirstRunWizard::FirstRunWizard() : QWizard() {
	addPage(createWelcomePage());
	addPage(createDatabasePage());
	addPage(createNewAccountPage());
	addPage(createLastPage());
	setOptions(QWizard::NoBackButtonOnStartPage | QWizard::NoBackButtonOnLastPage | QWizard::NoCancelButton);
	setWizardStyle(QWizard::ModernStyle);
	setWindowTitle(QString("Regalis Newsletter v%1 - first run").arg(REGALIS_NEWSLETTER_VERSION));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":res/images/wizard-watermark.png"));
	connect(this, SIGNAL(accepted()), this, SLOT(finish()));
}

void FirstRunWizard::finish() {
	RegalisNewsletter::get()->exec();
}

QWizardPage *FirstRunWizard::createWelcomePage() const {
	QWizardPage *page = new QWizardPage();
	page->setTitle(tr("Welcome in Regalis Newsletter v%1").arg(REGALIS_NEWSLETTER_VERSION));
	QLabel *msg = new QLabel(tr("Regalis Newsletter is simple, multiplatform tool for mass mailing including subscribers managing, groups and campaigns.<p>This program is <strong>free software</strong>: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p><p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.</p>"));
	msg->setWordWrap(true);
	msg->setAlignment(Qt::AlignJustify);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(msg);
	page->setLayout(layout);

	return page;
}

QWizardPage *FirstRunWizard::createLastPage() const {
	QWizardPage *page = new QWizardPage();
	page->setTitle(tr("Your Regalis Newsletter is ready to use"));
	QLabel *msg = new QLabel(tr("We hope that the program will be helpful. To help make it better - please feel free to report new idas/bugs!"));
	msg->setWordWrap(true);
	msg->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(msg);
	page->setLayout(layout);

	return page;
}

QWizardPage *FirstRunWizard::createDatabasePage() const {
	return new DatabasePage();
}

QWizardPage *FirstRunWizard::createNewAccountPage() const {
	return new AccountPage();
}

FirstRunWizard::DatabasePage::DatabasePage() : QWizardPage() {
	setTitle(tr("Please configure your database connection"));
	QLabel *msg = new QLabel(tr("This newsletter use PostgreSQL database"));
	msg->setWordWrap(true);
	
	QLabel *host_label = new QLabel(tr("Host:"));
	host = new QLineEdit("localhost");
	host_label->setBuddy(host);

	QLabel *port_label = new QLabel(tr("Port:"));
	port = new QLineEdit("5432");
	port_label->setBuddy(port);
	port->setInputMask("9999999999");

	QLabel *db_label = new QLabel(tr("Database:"));
	db = new QLineEdit("regalis_newsletter");
	db_label->setBuddy(db);

	QLabel *user_label = new QLabel(tr("User:"));
	user = new QLineEdit("rnewslettercli");
	user_label->setBuddy(user);

	QLabel *pass_label = new QLabel(tr("Password:"));
	pass = new QLineEdit("regalis_newsletter_client");
	pass->setEchoMode(QLineEdit::Password);
	pass_label->setBuddy(pass);

	QGridLayout *layout = new QGridLayout();
	layout->addWidget(msg, 0, 0, 1, 0);
	layout->addWidget(host_label, 1, 0, Qt::AlignRight);
	layout->addWidget(host, 1, 1);
	layout->addWidget(port_label, 2, 0, Qt::AlignRight);
	layout->addWidget(port, 2, 1);
	layout->addWidget(db_label, 3, 0, Qt::AlignRight);
	layout->addWidget(db, 3, 1);
	layout->addWidget(user_label, 4, 0, Qt::AlignRight);
	layout->addWidget(user, 4, 1);
	layout->addWidget(pass_label, 5, 0, Qt::AlignRight);
	layout->addWidget(pass, 5, 1);
	layout->setColumnMinimumWidth(1, 250);
	setLayout(layout);
}

bool FirstRunWizard::DatabasePage::validatePage() {
	if (host->text().isEmpty() || port->text().isEmpty() ||
		db->text().isEmpty() || user->text().isEmpty() ||
		pass->text().isEmpty()) {
		QMessageBox::warning(wizard(), tr("Please fill all fields"), tr("You have to fill all fields in this step..."));	
		return false;
	}
	QSettings *settings = RegalisNewsletter::get()->getSettings();
	settings->setValue("psql/host", host->text());
	settings->setValue("psql/port", port->text().toInt());
	settings->setValue("psql/user", user->text());
	settings->setValue("psql/pass", pass->text());
	settings->setValue("psql/db", db->text());
	if (!RegalisNewsletter::get()->initDatabase()) {
		settings->clear();
		QMessageBox::critical(wizard(), tr("Connection error"), RegalisNewsletter::get()->initDatabaseError());
		return false;
	}
	return true;
}

FirstRunWizard::AccountPage::AccountPage() : QWizardPage() {
	form = Accounts::getNewAccountForm();
	setTitle("Configure your default e-mail account");
	setLayout(form->layout());
}

bool FirstRunWizard::AccountPage::validatePage() {
	if (!form->validate()) {
		QMessageBox::warning(wizard(), tr("Unable to create new account"), form->getErrorMessage());
		return false;
	}
	if (!(form->initModel() && form->insert())) {
		QMessageBox::warning(wizard(), tr("Unable to create new account"), tr("Something is wrong with SQL query, this looks like an internal error, please report it."));
		return false;
	}
	return true;
}

FirstRunWizard::AccountPage::~AccountPage() {
	delete form;
}

FirstRunWizard::~FirstRunWizard() {

}
