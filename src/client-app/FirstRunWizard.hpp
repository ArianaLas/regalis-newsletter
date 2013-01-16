#ifndef __FIRST_RUN_WIZZARD_
#define __FIRST_RUN_WIZZARD_

#include <QWizard>
#include <QWizardPage>
#include <QLineEdit>


class FirstRunWizard : public QWizard {
	public:
		FirstRunWizard();
		~FirstRunWizard();
	protected:
		QWizardPage *createWelcomePage() const;
		QWizardPage *createDatabasePage() const;
		class DatabasePage;
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

#endif
