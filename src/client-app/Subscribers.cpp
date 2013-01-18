#include <QVBoxLayout>

#include "Subscribers.hpp"

Subscribers::Subscribers(QWidget *parent) : QWidget(parent) {
	model = new SqlModel();
	table_view = new QTableView(this);
	table_view->setModel(model);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(table_view);
	setLayout(layout);
	
}

Subscribers::SqlModel::SqlModel() : QSqlQueryModel() {
	setQuery("select id, name, surname, email, country, province, city, address, sex, birthday from subscribers order by registered desc");	
	setHeaderData(0, Qt::Horizontal, QObject::tr("#id"));
	setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
	setHeaderData(2, Qt::Horizontal, QObject::tr("Surname"));
	setHeaderData(3, Qt::Horizontal, QObject::tr("E-mail"));
	setHeaderData(4, Qt::Horizontal, QObject::tr("Country"));
	setHeaderData(5, Qt::Horizontal, QObject::tr("Province"));
	setHeaderData(6, Qt::Horizontal, QObject::tr("City"));
	setHeaderData(7, Qt::Horizontal, QObject::tr("Address"));
	setHeaderData(8, Qt::Horizontal, QObject::tr("Sex"));
	setHeaderData(9, Qt::Horizontal, QObject::tr("Birthday"));
}

Qt::ItemFlags Subscribers::SqlModel::flags(const QModelIndex &index) const {
	return QSqlQueryModel::flags(index);	
}


bool Subscribers::SqlModel::setData(const QModelIndex &index, const QVariant &value, int role) {
	return false;
}
