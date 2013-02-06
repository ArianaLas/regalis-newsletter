#include <QIcon>
#include <QActionGroup>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

#include "MainWindow.hpp"
#include "Subscribers.hpp"
#include "Dashboard.hpp"
#include "Preferences.hpp"
#include "version.hpp"

MainWindow::MainWindow() : QMainWindow(0) {
	setWindowTitle(QString("Regalis Newsletter v%1").arg(REGALIS_NEWSLETTER_VERSION));
	setMinimumSize(800, 500);
	buildMenu();
	preferences = new Preferences();
	initCentralWidget();
	buildToolbar();
}

void MainWindow::buildMenu() {

	quit = new QAction(QIcon::fromTheme("application-exit"), tr("&Quit"), this);
	quit->setIconVisibleInMenu(true);

	new_newsletter = new QAction(QIcon::fromTheme("document-new"), tr("&New newsletter"), this);
	new_newsletter->setIconVisibleInMenu(true);

	show_preferences = new QAction(QIcon::fromTheme("preferences-other"), tr("&Preferences"), this);
	show_preferences->setIconVisibleInMenu(true);
	connect(show_preferences, SIGNAL(triggered()), this, SLOT(showPreferences()));

	QActionGroup *view_group = new QActionGroup(this);
	view_group->setExclusive(true);
	show_dashboard = view_group->addAction(QIcon::fromTheme("go-home"), tr("&Dashboard"));
	show_dashboard->setCheckable(true);
	show_dashboard->setIconVisibleInMenu(true);
	show_dashboard->setChecked(true);
	connect(show_dashboard, SIGNAL(toggled(bool)), this, SLOT(showDashboard(bool)));

	show_subscribers = view_group->addAction(QIcon::fromTheme("x-office-address-book"), tr("&Subscribers"));
	show_subscribers->setCheckable(true);
	show_subscribers->setIconVisibleInMenu(true);
	connect(show_subscribers, SIGNAL(toggled(bool)), this, SLOT(showSubscribers(bool)));

	show_newsletters_history = view_group->addAction(QIcon::fromTheme("document-open-recent"), tr("Newsletters &history"));
	show_newsletters_history->setCheckable(true);
	show_newsletters_history->setIconVisibleInMenu(true);
	connect(show_newsletters_history, SIGNAL(toggled(bool)), this, SLOT(showNewslettersHistory(bool)));

	about = new QAction(QIcon::fromTheme("help-about"), tr("&About"), this);

	QMenu *file_menu = menuBar()->addMenu(tr("&File"));
	QMenu *edit_menu = menuBar()->addMenu(tr("&Edit"));
	QMenu *view_menu = menuBar()->addMenu(tr("&View"));
	QMenu *help_menu = menuBar()->addMenu(tr("&Help"));
	
	file_menu->addAction(new_newsletter);
	file_menu->addSeparator();
	file_menu->addAction(quit);

	edit_menu->addAction(show_preferences);

	view_menu->addAction(show_dashboard);
	view_menu->addAction(show_subscribers);
	view_menu->addAction(show_newsletters_history);

	help_menu->addAction(about);

}

void MainWindow::buildToolbar() {
	QToolBar *toolbar = addToolBar(tr("Main toolbar"));	
	toolbar->addAction(new_newsletter);
	toolbar->addSeparator();
	toolbar->addAction(show_dashboard);
	toolbar->addAction(show_subscribers);
	toolbar->addAction(show_newsletters_history);
	toolbar->setMovable(false);

	stacked_tool_bar = new QStackedWidget(toolbar);
	stacked_tool_bar->addWidget(dashboard->getToolBar());
	stacked_tool_bar->addWidget(subscribers->getToolBar());
	toolbar->addWidget(stacked_tool_bar);
}

void MainWindow::initCentralWidget() {
	central_widget = new QStackedWidget(this);
	subscribers = new Subscribers(this);
	dashboard = new Dashboard(this);
	central_widget->addWidget(dashboard);
	central_widget->addWidget(subscribers);
	setCentralWidget(central_widget);
}

void MainWindow::showDashboard(bool checked) {	
	if (checked) {
		central_widget->setCurrentWidget(dashboard);
		stacked_tool_bar->setCurrentWidget(dashboard->getToolBar());
	}
}

void MainWindow::showSubscribers(bool checked) {
	if (checked) {
		central_widget->setCurrentWidget(subscribers);
		stacked_tool_bar->setCurrentWidget(subscribers->getToolBar());
	}
}

void MainWindow::showNewslettersHistory(bool checked) {
}

void MainWindow::showPreferences() {
	preferences->show();
}

MainWindow::~MainWindow() {
	delete quit;
	delete new_newsletter;
	delete show_dashboard;
	delete dashboard;
	delete show_subscribers;
	delete show_newsletters_history;
	delete show_preferences;
	delete preferences;
	delete about;
	delete central_widget;
	delete subscribers;
}

