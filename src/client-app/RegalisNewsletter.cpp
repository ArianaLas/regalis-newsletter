#include <iostream>

#include <QSqlDatabase>

#include "RegalisNewsletter.hpp"
#include "FirstRunWizard.hpp"
using namespace std;

RegalisNewsletter::RegalisNewsletter() {
	settings = new QSettings("Regalis", "regalis-newsletter");
	QSqlDatabase::addDatabase("QMYSQL");
}

RegalisNewsletter *RegalisNewsletter::get() {
	static RegalisNewsletter *instance = new RegalisNewsletter();
	return instance;
}

bool RegalisNewsletter::isFirstRun() const {
	return !(settings->contains("mysql/host") &&
			settings->contains("mysql/port") &&
			settings->contains("mysql/user") &&
			settings->contains("mysql/pass") &&
			settings->contains("mysql/db"));
}

void RegalisNewsletter::exec() {
	if (isFirstRun()) {
		cerr << "First run!" << endl;
		FirstRunWizard *wizard = new FirstRunWizard();
		wizard->show();
		cerr << "After first run..." << endl;
	} else {
		cerr << "Second(++) run..." << endl;
	}
}

RegalisNewsletter::~RegalisNewsletter() {
	delete settings;
}

