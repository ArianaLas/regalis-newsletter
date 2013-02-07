#include <QVBoxLayout>
#include <QSqlQuery>
#include <QModelIndex>
#include <QVariant>
#include <QAction>
#include <QMenu>
#include <QHeaderView>
#include <QPoint>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlError>
#include <QStringList>
#include <QDebug>
#include <QToolButton>
#include <QSignalMapper>

#include "Subscribers.hpp"

Subscribers::Subscribers(QWidget *parent) : QWidget(parent) {
	model = new TableModel();
	model->setTable("subscribers");
	model->setEditStrategy(QSqlTableModel::OnFieldChange);
	sort_order = Qt::AscendingOrder;
	sort_column = 0;
	updateSort();

	column_names << tr("#id") << tr("Name") << tr("Surname") << tr("E-mail");
	column_names << tr("Country") << tr("Province") << tr("City") << tr("Address");
	column_names << tr("Sex") << tr("Birthday") << tr("Register date");
	column_names << tr("Confirmation date");

	for (int i = 0; i < column_names.size(); ++i) {
		model->setHeaderData(i, Qt::Horizontal, column_names.at(i));
	}

	table_view = new QTableView(this);
	table_view->setModel(model);
	table_view->resizeColumnsToContents();
	table_view->setContextMenuPolicy(Qt::CustomContextMenu);
	table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	table_view->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(table_view, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(tableContextMenu(const QPoint&)));

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(table_view);
	setLayout(layout);

	tool_bar = NULL;
}

QToolBar *Subscribers::getToolBar() {
	if (tool_bar == NULL) {
		buildToolBar();
	}
	return tool_bar;
}

void Subscribers::buildToolBar() {
		tool_bar = new QToolBar(tr("Subscribers toolbar"));
		tool_bar->setMovable(false);
		tool_bar->addAction(tr("Groups"));
		tool_bar->addAction(tr("Campaigns"));
		tool_bar->setStyleSheet("QToolBar { border: 0px; }");

		QToolButton *sort_button = new QToolButton();
		QAction *sort_action = new QAction("Sort", 0);
		connect(sort_action, SIGNAL(triggered()), sort_button, SLOT(showMenu()));
		sort_button->setDefaultAction(sort_action);
		sort_button->setPopupMode(QToolButton::MenuButtonPopup);
		sort_menu = new QMenu(tr("Sort menu"));
		sort_button->setMenu(sort_menu);
		sort_group = new QActionGroup(sort_menu);
		sort_group->setExclusive(true);
		QSignalMapper *sort_mapper = new QSignalMapper(sort_menu);
		for (int i = 0; i < column_names.size(); ++i) {
			QAction *action = sort_group->addAction(column_names.at(i));
			action->setCheckable(true);
			if (i == 0)
				action->setChecked(true);
			sort_menu->addAction(action);
			connect(action, SIGNAL(triggered()), sort_mapper, SLOT(map()));
			sort_mapper->setMapping(action, i);
		}
		connect(sort_mapper, SIGNAL(mapped(int)), this, SLOT(updateSort(int)));
		connect(table_view->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(updateSort(int)));

		sort_order_group = new QActionGroup(tool_bar);
		QSignalMapper *sort_order_mapper = new QSignalMapper(sort_order_group);
		QAction *sort_as = sort_order_group->addAction(QIcon::fromTheme("view-sort-ascending"), tr("Sort ascending"));
		sort_as->setCheckable(true);
		sort_as->setChecked(true);
		QAction *sort_de = sort_order_group->addAction(QIcon::fromTheme("view-sort-descending"), tr("Sort descending"));
		sort_de->setCheckable(true);
		sort_order_group->setExclusive(true);

		connect(sort_as, SIGNAL(triggered()), sort_order_mapper, SLOT(map()));
		connect(sort_de, SIGNAL(triggered()), sort_order_mapper, SLOT(map()));
		sort_order_mapper->setMapping(sort_as, 0);
		sort_order_mapper->setMapping(sort_de, 1);
		connect(sort_order_mapper, SIGNAL(mapped(int)), this, SLOT(updateSortOrder(int)));

		tool_bar->addWidget(sort_button);
		tool_bar->addSeparator();
		tool_bar->addAction(sort_as);
		tool_bar->addAction(sort_de);
}

void Subscribers::updateSort() {
	model->setSort(sort_column, sort_order);
	model->select();
}

void Subscribers::updateSort(int column_index) {
	if (sort_column == column_index) {
		updateSortOrder((sort_order == 0 ? 1 : 0));
	} else {
		sort_column = column_index;
		sort_group->actions().at(column_index)->setChecked(true);
		updateSort();
	}
}

void Subscribers::updateSortOrder(int order) {
	sort_order = (Qt::SortOrder)order;
	sort_order_group->actions().at(order)->setChecked(true);
	updateSort();
}

void Subscribers::tableContextMenu(const QPoint &pos) {
	// TODO: allow multiple selection
	QPoint globalPos = table_view->viewport()->mapToGlobal(pos);
	int selected_row = table_view->indexAt(pos).row();
	int model_id = model->record(selected_row).value("id").toInt();
	table_view->selectRow(selected_row);
	QMenu menu;

	QAction *remove = menu.addAction(QIcon::fromTheme("list-remove"), tr("Remove this row"));
	remove->setIconVisibleInMenu(true);

	QSqlQuery query(QString("select id, name, (select count(*) from group_members where subscriber_id=%1 and group_id=id) as is_member from groups order by name;").arg(model_id));
	QMenu *groups_menu = 0;
	if (query.size() > 0) {
		groups_menu = menu.addMenu(tr("Groups"));
		while (query.next()) {
			QAction* group_action = groups_menu->addAction(query.value(1).toString());
			group_action->setCheckable(true);
			group_action->setData(query.value(0));
			if (query.value(2).toInt() != 0)
				group_action->setChecked(true);
		}
	}

	query.exec(QString("select id, name, (select count(*) from campaigns_members where subscriber_id=%1 and campaign_id=id) from campaigns;").arg(model_id));
	QMenu *campaigns_menu = 0;
	if (query.size() > 0) {
		campaigns_menu = menu.addMenu(tr("Campaigns"));
		while (query.next()) {
			QAction* campaign_action = campaigns_menu->addAction(query.value(1).toString());
			campaign_action->setCheckable(true);
			campaign_action->setData(query.value(0));
			if (query.value(2).toInt() != 0)
				campaign_action->setChecked(true);
		}
	}

	QAction *action = menu.exec(globalPos);

	if (action == 0)
		return;

	if (action == remove) {
		QString email = model->record(selected_row).value("email").toString();
		QMessageBox::StandardButton answer = QMessageBox::question(this, tr("Need confirmation"), QString(tr("Are you sure you want to remove #%1 (%2)?")).arg(QString::number(model_id)).arg(email), QMessageBox::Yes | QMessageBox::No);
		if (answer == QMessageBox::Yes) {
			if (!model->removeRows(selected_row, 1)) {
				QMessageBox::critical(this, tr("Unable to remove row..."), QString(tr("Unable to remove this row. Error message: %1")).arg(model->lastError().text()));
			}
		}
	} else {
		if (action->parentWidget() == groups_menu) {
			QSqlQuery q;
			if (action->isChecked()) {
				q.prepare("insert into group_members (group_id, subscriber_id) values (:gid, :sid)");
			} else {
				q.prepare("delete from group_members where group_id = :gid and subscriber_id = :sid");
			}
			q.bindValue(":gid", action->data().toInt());
			q.bindValue(":sid", model_id);
			q.exec();
			return;
		}
		if (action->parentWidget() == campaigns_menu) {
			QSqlQuery q;
			if (action->isChecked()) {
				q.prepare("insert into campaigns_members (campaign_id, subscriber_id) values (:cid, :sid)");
			} else {
				q.prepare("delete from campaigns_members where campaign_id = :cid and subscriber_id = :sid");
			}
			q.bindValue(":cid", action->data().toInt());
			q.bindValue(":sid", model_id);
			q.exec();
			return;
		}
	}
}

Subscribers::TableModel::TableModel() : QSqlTableModel() {}

QString Subscribers::TableModel::selectStatement() const {
	QString sql = QString("select id, name, surname, email, country, province, city, address, sex, birthday, registered, confirmed from %1 ").arg(tableName());
	if (!filter().isEmpty())
		sql += QString("where %1 ").arg(filter());
	sql += orderByClause();
	return sql;
}

