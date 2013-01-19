#ifndef __SUBSCRIBERS_HPP_
#define __SUBSCRIBERS_HPP_

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>

class Subscribers : public QWidget {
	public:
		Subscribers(QWidget *parent);
		static bool setName(int id, const QString &name);
		static bool setSurname(int id, const QString &surname);
		static bool setEmail(int id, const QString &email);
		static bool setCountry(int id, const QString &country);
		static bool setProvince(int id, const QString &province);
		static bool setCity(int id, const QString &city);
		static bool setAddress(int id, const QString &address);
		static bool setSex(int id, const QString &sex);
		static bool setBirthday(int id, const QString &birthday);
	protected:
		QSqlTableModel *model;
		QTableView *table_view;
};

#endif
