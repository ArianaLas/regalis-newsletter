#include <QVBoxLayout>
#include <QSqlQuery>
#include <QModelIndex>
#include <QVariant>

#include "Subscribers.hpp"

Subscribers::Subscribers(QWidget *parent) : QWidget(parent) {
	model = new TableModel();
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
	table_view->resizeColumnsToContents();

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(table_view);
	setLayout(layout);
}

Subscribers::TableModel::TableModel() : QSqlTableModel() {}

QString Subscribers::TableModel::selectStatement() const {
	QString sql = QString("select id, name, surname, email, country, province, city, address, sex, birthday from %1").arg(tableName());
	if (!filter().isEmpty())
		sql += QString(" where %1");
	sql += orderByClause();
	return sql;
}

