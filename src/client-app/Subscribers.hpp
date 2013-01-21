#ifndef __SUBSCRIBERS_HPP_
#define __SUBSCRIBERS_HPP_

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>

class Subscribers : public QWidget {
	public:
		Subscribers(QWidget *parent);
	protected:
		class TableModel;
		TableModel *model;
		QTableView *table_view;
};

class Subscribers::TableModel : public QSqlTableModel {
	public:
		TableModel();
	protected:
		QString selectStatement() const;
};

#endif
