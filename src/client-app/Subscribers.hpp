#ifndef __SUBSCRIBERS_HPP_
#define __SUBSCRIBERS_HPP_

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QObject>
#include <QPoint>
#include <QToolBar>

class Subscribers : public QWidget {
	Q_OBJECT;

	public:
		Subscribers(QWidget *parent);
		QToolBar *getToolBar();
	protected:
		class TableModel;
		TableModel *model;
		QTableView *table_view;
		QToolBar *tool_bar;
	protected slots:
		void tableContextMenu(const QPoint &pos);
};

class Subscribers::TableModel : public QSqlTableModel {
	public:
		TableModel();
	protected:
		QString selectStatement() const;
};

#endif
