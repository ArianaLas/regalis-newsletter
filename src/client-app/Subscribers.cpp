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
}

void Subscribers::tableContextMenu(const QPoint &pos) {
	QPoint globalPos = table_view->viewport()->mapToGlobal(pos);
	int selected_row = table_view->indexAt(pos).row();
	table_view->selectRow(selected_row);
	QMenu menu;
	QAction *remove = menu.addAction(QIcon::fromTheme("list-remove"), tr("Remove this row"));
	remove->setIconVisibleInMenu(true);
	menu.addAction(tr("Do something with this row..."));
	QAction *action = menu.exec(globalPos);
	if (action == remove) {
		int id_to_delete = model->record(selected_row).value("id").toInt();
		QString email = model->record(selected_row).value("email").toString();
		QMessageBox::StandardButton answer = QMessageBox::question(this, tr("Need confirmation"), QString(tr("Are you sure you want to remove #%1 (%2)?")).arg(QString::number(id_to_delete)).arg(email), QMessageBox::Yes | QMessageBox::No);
		if (answer == QMessageBox::Yes) {
			if (!model->removeRows(selected_row, 1)) {
				QMessageBox::critical(this, tr("Unable to remove row..."), QString(tr("Unable to remove this row. Error message: %1")).arg(model->lastError().text()));
			}
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

