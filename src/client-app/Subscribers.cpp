#include <QVBoxLayout>
#include <QSqlQuery>
#include <QModelIndex>
#include <QVariant>

#include "Subscribers.hpp"

Subscribers::Subscribers(QWidget *parent) : QWidget(parent) {
	model = new QSqlTableModel();
	model->setTable("subscribers");
	model->setEditStrategy(QSqlTableModel::OnFieldChange);
	model->select();

	model->setHeaderData(0, Qt::Horizontal, tr("#id"));
	model->setHeaderData(1, Qt::Horizontal, tr("Name"));
	model->setHeaderData(2, Qt::Horizontal, tr("Surname"));
	model->setHeaderData(3, Qt::Horizontal, tr("E-mail"));
	model->setHeaderData(4, Qt::Horizontal, tr("Country"));
	model->setHeaderData(5, Qt::Horizontal, tr("Province"));
	model->setHeaderData(6, Qt::Horizontal, tr("City"));
	model->setHeaderData(7, Qt::Horizontal, tr("Address"));
	model->setHeaderData(8, Qt::Horizontal, tr("Sex"));
	model->setHeaderData(9, Qt::Horizontal, tr("Birthday"));

	table_view = new QTableView(this);
	table_view->setModel(model);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(table_view);
	setLayout(layout);
	
}

bool Subscribers::setName(int id, const QString &name) {
	QSqlQuery query;
	query.prepare("update subscribers set name=? where id=?");
	query.addBindValue(name);
	query.addBindValue(id);
	return query.exec();
}

bool Subscribers::setSurname(int id, const QString &surname) {
	QSqlQuery query;
	query.prepare("update subscribers set surname=? where id=?");
	query.addBindValue(surname);
	query.addBindValue(id);
	return query.exec();
}

bool Subscribers::setEmail(int id, const QString &email) {
	QSqlQuery query;
	query.prepare("update subscribers set email=? where id=?");
	query.addBindValue(email);
	query.addBindValue(id);
	return query.exec();
}

bool Subscribers::setCountry(int id, const QString &country) {
	QSqlQuery query;
	query.prepare("update subscribers set country=? where id=?");
	query.addBindValue(country);
	query.addBindValue(id);
	return query.exec();
}

bool Subscribers::setProvince(int id, const QString &province) {
	QSqlQuery query;
	query.prepare("update subscribers set province=? where id=?");
	query.addBindValue(province);
	query.addBindValue(id);
	return query.exec();
}

bool Subscribers::setCity(int id, const QString &city) {
	QSqlQuery query;
	query.prepare("update subscribers set city=? where id=?");
	query.addBindValue(city);
	query.addBindValue(id);
	return query.exec();
}

bool Subscribers::setAddress(int id, const QString &address) {
	QSqlQuery query;
	query.prepare("update subscribers set address=? where id=?");
	query.addBindValue(address);
	query.addBindValue(id);
	return query.exec();
}

bool Subscribers::setSex(int id, const QString &sex) {
	if (sex != "M" || sex != "F")
		return false;
	QSqlQuery query;
	query.prepare("update subscribers set sex=? where id=?");
	query.addBindValue(sex);
	query.addBindValue(id);
	return query.exec();
}

bool Subscribers::setBirthday(int id, const QString &birthday) {
	QSqlQuery query;
	query.prepare("update subscribers set birthday=? where id=?");
	query.addBindValue(birthday);
	query.addBindValue(id);
	return query.exec();
}
