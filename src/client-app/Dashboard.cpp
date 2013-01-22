#include <QLabel>
#include <QString>

#include "Dashboard.hpp"
#include "version.hpp"

Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
	vbox = new QVBoxLayout(this);
	QLabel *hello_message = new QLabel(QString("Welcome in Regalis Newsletter v%1").arg(REGALIS_NEWSLETTER_VERSION));
	vbox->addWidget(hello_message, 0, Qt::AlignHCenter);
	setLayout(vbox);
}
