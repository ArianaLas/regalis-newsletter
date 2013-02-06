#ifndef __FIRST_RUN_WIZZARD_HPP_
#define __FIRST_RUN_WIZZARD_HPP_

#include <QObject>
#include <QWizard>
#include <QWizardPage>
#include <QLineEdit>

#include "Accounts.hpp"

class FirstRunWizard : public QWizard {
	Q_OBJECT;

	public:
		FirstRunWizard();
		~FirstRunWizard();
	protected:
		QWizardPage *createWelcomePage() const;
		QWizardPage *createDatabasePage() const;
		QWizardPage *createNewAccountPage() const;
		QWizardPage *createLastPage() const;
		class DatabasePage;
		class AccountPage;
	protected slots:
		void finish();
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
