#include <QApplication>
#include <QResource>

#include "RegalisNewsletter.hpp"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	RegalisNewsletter *newsletter = RegalisNewsletter::get();
	newsletter->exec();
	return app.exec();
}
