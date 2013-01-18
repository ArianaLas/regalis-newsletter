#include <QSqlDatabase>

#include "RegalisNewsletter.hpp"
#include "FirstRunWizard.hpp"
#include "MainWindow.hpp"

RegalisNewsletter::RegalisNewsletter() {
	settings = new QSettings("Regalis", "regalis-newsletter");
	QSqlDatabase::addDatabase("QMYSQL");
	wizard = NULL;
}

RegalisNewsletter *RegalisNewsletter::get() {
	static RegalisNewsletter *instance = new RegalisNewsletter();
	return instance;
}

bool RegalisNewsletter::isFirstRun() const {
	return (settings->contains("mysql/host") &&
			settings->contains("mysql/port") &&
			settings->contains("mysql/user") &&
			settings->contains("mysql/pass") &&
			settings->contains("mysql/db"));
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
	db.setUserName("rnewsletter");
	db.setPassword("regalis_newsletter");
	db.setPort(3306);
	db.setDatabaseName("regalis_newsletter");
	db.open();
	return true;
}

RegalisNewsletter::~RegalisNewsletter() {
	delete settings;
	if (wizard != NULL)
		delete wizard;
}

