#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

#include "RegalisNewsletter.hpp"
#include "FirstRunWizard.hpp"
#include "MainWindow.hpp"

RegalisNewsletter::RegalisNewsletter() {
	settings = new QSettings("regalis", "regalis-newsletter");
	wizard = NULL;
}

RegalisNewsletter *RegalisNewsletter::get() {
	static RegalisNewsletter *instance = new RegalisNewsletter();
	return instance;
}

bool RegalisNewsletter::isFirstRun() const {
	return !(settings->contains("psql/host") &&
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
	if (isFirstRun())
		return false;
	QSqlDatabase db = QSqlDatabase::database();
	if (db.isOpen())
		return true;
	db = QSqlDatabase::addDatabase("QPSQL");
	db.setHostName(settings->value("psql/host").toString());
	db.setUserName(settings->value("psql/user").toString());
	db.setPassword(settings->value("psql/pass").toString());
	db.setPort(settings->value("psql/port").toInt());
	db.setDatabaseName(settings->value("psql/db").toString());
	if (!db.open()) {
		QSqlDatabase::removeDatabase(db.userName());
		init_error = db.lastError().text();
		return false;
	}
	return true;
}

QSettings *RegalisNewsletter::getSettings() {
	return settings;
}

QString RegalisNewsletter::initDatabaseError() {
	return init_error;
}

RegalisNewsletter::~RegalisNewsletter() {
	delete settings;
	if (wizard != NULL)
		delete wizard;
}

