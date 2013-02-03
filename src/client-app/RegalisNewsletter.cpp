#include <QSqlDatabase>

#include "RegalisNewsletter.hpp"
#include "FirstRunWizard.hpp"
#include "MainWindow.hpp"

RegalisNewsletter::RegalisNewsletter() {
	settings = new QSettings("Regalis", "regalis-newsletter");
	QSqlDatabase::addDatabase("QPSQL");
	wizard = NULL;
}

RegalisNewsletter *RegalisNewsletter::get() {
	static RegalisNewsletter *instance = new RegalisNewsletter();
	return instance;
}

bool RegalisNewsletter::isFirstRun() const {
	return (settings->contains("psql/host") &&
			settings->contains("psql/port") &&
			settings->contains("psql/user") &&
			settings->contains("psql/pass") &&
			settings->contains("psql/db"));
}

void RegalisNewsletter::exec() {
	if (isFirstRun()) {
		wizard = new FirstRunWizard();
		wizard->show();
	} else {
		initDatabase();
		initMainWindow();
	}
}

void RegalisNewsletter::initMainWindow() {
	main_window = new MainWindow();
	main_window->show();
}

bool RegalisNewsletter::initDatabase() {
	QSqlDatabase db = QSqlDatabase::database();
	db.setHostName("localhost");
	db.setUserName("rnewslettercli");
	db.setPassword("regalis_newsletter_client");
	db.setPort(5432);
	db.setDatabaseName("regalis_newsletter");
	db.open();
	return true;
}

RegalisNewsletter::~RegalisNewsletter() {
	delete settings;
	if (wizard != NULL)
		delete wizard;
}

