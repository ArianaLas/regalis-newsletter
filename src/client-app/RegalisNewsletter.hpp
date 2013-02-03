#ifndef __REGALIS_NEWSLETTER_
#define __REGALIS_NEWSLETTER_

#include <QSettings>
#include <QObject>
#include <QSqlDatabase>

class MainWindow;
class FirstRunWizard;

class RegalisNewsletter : public QObject {
	public:
		
		/** Get RegalisNewsletter instance
		 * @return pointer to RegalisNewsletter (singleton)
		 */
		static RegalisNewsletter *get();

		/** Check if configuration is present
		 * @return true if local configuration is not present
		 * @return false if local configuration is present
		 */
		bool isFirstRun() const;
		
		/** Exec application, run first run wizzard or main window */
		void exec();

		/** Default destructor */
		~RegalisNewsletter();
	protected:
		RegalisNewsletter();
		void initMainWindow();
		bool initDatabase();
		MainWindow *main_window;
		FirstRunWizard *wizard;
		QSettings *settings;
};

#endif
