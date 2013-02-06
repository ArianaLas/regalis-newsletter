#ifndef __MAIN_WINDOW_HPP_
#define __MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QObject>
#include <QAction>
#include <QStackedWidget>

class Subscribers;
class Dashboard;
class Preferences;

class MainWindow : public QMainWindow {
	Q_OBJECT;

	public:
		MainWindow();
		~MainWindow();
	protected:
		void buildMenu();
		void buildToolbar();
		void initCentralWidget();
		QAction *quit;
		QAction *show_preferences;
		QAction *new_newsletter;
		QAction *show_dashboard;
		QAction *show_subscribers;
		QAction *show_newsletters_history;
		QAction *about;
		QStackedWidget *central_widget;
		QStackedWidget *stacked_tool_bar;
		Subscribers *subscribers;
		Dashboard *dashboard;
		Preferences *preferences;
	
	protected slots:
		void showDashboard(bool checked);
		void showSubscribers(bool checked);
		void showNewslettersHistory(bool checked);
		void showPreferences();

};

#endif
