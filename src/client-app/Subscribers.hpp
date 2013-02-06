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
		void buildToolBar();
		TableModel *model;
		QTableView *table_view;
		QToolBar *tool_bar;
		QMenu *sort_menu;
		QString groups_filter;
		QString campaigns_filter;
		QStringList column_names;
		Qt::SortOrder sort_order;
		int sort_column;
		void updateSort();
	protected slots:
		void tableContextMenu(const QPoint &pos);
		void updateSort(int column_index);
		void updateSortOrder(int order);
};

class Subscribers::TableModel : public QSqlTableModel {
	public:
		TableModel();
	protected:
		QString selectStatement() const;
};

#endif
