#ifndef __PREFERENCES_HPP_
#define __PREFERENCES_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

class Preferences : public QWidget {
	public:
		Preferences(QWidget *parent = 0);
		void show();

	protected:
		void init();
		int getRowFromName(const QString &name) const;
		
		QSqlTableModel *form_model;
		QDataWidgetMapper *form_mapper;

		QVBoxLayout *vbox;
};
#endif
