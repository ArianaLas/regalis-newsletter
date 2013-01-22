#include <QLabel>
#include <QString>

#include "Dashboard.hpp"
#include "version.hpp"

Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
	QLabel *hello_message = new QLabel(QString("Welcome in Regalis Newsletter v%1").arg(REGALIS_NEWSLETTER_VERSION));
}
