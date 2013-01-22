#ifndef __DASHBOARD_HPP_
#define __DASHBOARD_HPP_

#include <QWidget>
#include <QVBoxLayout>

class Dashboard : public QWidget {
	public:
		Dashboard(QWidget *parent);
	protected:
		QVBoxLayout *vbox;
};
#endif
