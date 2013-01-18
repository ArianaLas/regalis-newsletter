#ifndef __MAIN_WINDOW_HPP_
#define __MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QObject>
#include <QAction>
#include <QStackedWidget>

class Subscribers;

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
		QAction *new_newsletter;
		QAction *show_dashboard;
		QAction *show_subscribers;
		QAction *show_newsletters_history;
		QAction *about;
		QStackedWidget *central_widget;
		Subscribers *subscribers;
};

#endif
