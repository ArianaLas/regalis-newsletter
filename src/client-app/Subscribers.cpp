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
#include <QDebug>

#include "Subscribers.hpp"

Subscribers::Subscribers(QWidget *parent) : QWidget(parent) {
	model = new TableModel();
	model->setTable("subscribers");
	model->setEditStrategy(QSqlTableModel::OnFieldChange);
	model->setSort(0, Qt::AscendingOrder);
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
	table_view->setContextMenuPolicy(Qt::CustomContextMenu);
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
		tool_bar->addAction(tr("Sort"));
}

void Subscribers::tableContextMenu(const QPoint &pos) {
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
	QString sql = QString("select id, name, surname, email, country, province, city, address, sex, birthday from %1 ").arg(tableName());
	if (!filter().isEmpty())
		sql += QString("where %1 ").arg(filter());
	sql += orderByClause();
	return sql;
}

