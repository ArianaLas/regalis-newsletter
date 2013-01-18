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
	setOptions(QWizard::NoBackButtonOnStartPage);
	setWizardStyle(QWizard::ModernStyle);
	setWindowTitle(QString("Regalis Newsletter v%1 - first run").arg(REGALIS_NEWSLETTER_VERSION));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":res/images/wizard-watermark.png"));
}

QWizardPage *FirstRunWizard::createWelcomePage() const {
	QWizardPage *page = new QWizardPage();
	page->setTitle(tr("Welcome in Regalis Newsletter v%1").arg(REGALIS_NEWSLETTER_VERSION));
	QLabel *msg = new QLabel(tr("This is first run wizard which helps you configure your newsletter"));
	msg->setWordWrap(true);

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
	QLabel *msg = new QLabel(tr("This newsletter use MySQL database"));
	msg->setWordWrap(true);
	
	QLabel *host_label = new QLabel(tr("Host:"));
	host = new QLineEdit("localhost");
	host_label->setBuddy(host);

	QLabel *port_label = new QLabel(tr("Port:"));
	port = new QLineEdit("3306");
	port_label->setBuddy(port);
	port->setInputMask("9999999999");

	QLabel *db_label = new QLabel(tr("Database:"));
	db = new QLineEdit("regalis_newsletter");
	db_label->setBuddy(db);

	QLabel *user_label = new QLabel(tr("User:"));
	user = new QLineEdit("rnewsletter");
	user_label->setBuddy(user);

	QLabel *pass_label = new QLabel(tr("Password:"));
	pass = new QLineEdit();
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
		QMessageBox::warning(wizard(), tr("Fill all fields"), tr("You have to fill all fields in this step.."));		
		return false;
	}
	QSqlDatabase database = QSqlDatabase::database();
	database.setHostName(host->text());
	database.setPort(port->text().toInt());
	database.setDatabaseName(db->text());
	database.setUserName(user->text());
	database.setPassword(pass->text());
	if (!database.open()) {
		QMessageBox::critical(wizard(), tr("Connection error"), database.lastError().text());
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
		QMessageBox::information(wizard(), tr("Success"), "Inser OK");
	return true;
}

FirstRunWizard::AccountPage::~AccountPage() {
	delete form;
}

FirstRunWizard::~FirstRunWizard() {

}
