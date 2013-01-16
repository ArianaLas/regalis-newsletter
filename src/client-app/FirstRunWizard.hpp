#ifndef __FIRST_RUN_WIZZARD_
#define __FIRST_RUN_WIZZARD_

#include <QWizard>
#include <QWizardPage>
#include <QLineEdit>

#include "Accounts.hpp"


class FirstRunWizard : public QWizard {
	public:
		FirstRunWizard();
		~FirstRunWizard();
	protected:
		QWizardPage *createWelcomePage() const;
		QWizardPage *createDatabasePage() const;
		QWizardPage *createNewAccountPage() const;
		class DatabasePage;
		class AccountPage;
};

class FirstRunWizard::DatabasePage : public QWizardPage {
	public:
		DatabasePage();
		bool validatePage();
	protected:
		QLineEdit *host;
		QLineEdit *port;
		QLineEdit *db;
		QLineEdit *user;
		QLineEdit *pass;
};

class FirstRunWizard::AccountPage : public QWizardPage {
	public:
		AccountPage();
		~AccountPage();
		bool validatePage();
	protected:
		Accounts::AccountForm *form;
};

#endif
