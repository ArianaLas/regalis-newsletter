#ifndef __DASHBOARD_HPP_
#define __DASHBOARD_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>

class Dashboard : public QWidget {
	public:
		Dashboard(QWidget *parent);
		QToolBar *getToolBar();
	protected:
		QVBoxLayout *vbox;
		QToolBar *tool_bar;
};
#endif
