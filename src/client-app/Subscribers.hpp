#ifndef __SUBSCRIBERS_HPP_
#define __SUBSCRIBERS_HPP_

#include <QWidget>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QVariant>
#include <QTableView>

class Subscribers : public QWidget {
	public:
		Subscribers(QWidget *parent);
	protected:
		class SqlModel;
		SqlModel *model;
		QTableView *table_view;
};

class Subscribers::SqlModel : public QSqlQueryModel {
	public:
		SqlModel();
		Qt::ItemFlags flags(const QModelIndex &index) const;
		bool setData(const QModelIndex &index, const QVariant &value, int role);
};

#endif
