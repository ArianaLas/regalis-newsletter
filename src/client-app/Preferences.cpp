#include <QLabel>
#include <QString>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <iostream>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>

#include "Preferences.hpp"

Preferences::Preferences(QWidget *parent) : QWidget(parent) {
	setWindowTitle(tr("Preferences"));
	vbox = new QVBoxLayout(this);
	setLayout(vbox);
	form_model = new QSqlTableModel();
	form_model->setTable("settings");
	form_model->setFilter("name like 'register\_form\_%'");
	form_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

	form_mapper = new QDataWidgetMapper();
	form_mapper->setModel(form_model);
	form_mapper->setOrientation(Qt::Vertical);
}

void Preferences::show() {
	if (form_model->select()) {
		form_mapper->setCurrentIndex(3);
	std::cout << "_______________________________________" << std::endl;
	std::cout << form_model->rowCount() << std::endl;
		for (int i = 0; i < form_model->rowCount(); ++i) {
			std::cout << form_model->record(i).value("name").toString().toUtf8().constData() << std::endl;
		}
	std::cout << "_______________________________________" << std::endl;
		init();
		QWidget::show();
	} else {
		QMessageBox::critical(0, tr("Unable to load configuration"), QString(tr("Unable to get configuration from database: %1")).arg(form_model->lastError().text()));
	}
}

int Preferences::getRowFromName(const QString &name) const {
	for (int i = 0; i < form_model->rowCount(); ++i) {
	//	std::cout << form_model->record(i).value("name").toString().toUtf8().constData() << std::endl;
		if (name == form_model->record(i).value("name").toString()) {
	//		std::cout << "id: " << i << std::endl;

			return i;
		}
	}
	return -1;
}

void Preferences::init() {

	QGroupBox *core_box = new QGroupBox(tr("Core settings"));
	QGroupBox *form_box = new QGroupBox(tr("Form settings"));

	QGridLayout *core_layout = new QGridLayout();
	QGridLayout *form_layout = new QGridLayout();

	QCheckBox *enable_email_confirmation = new QCheckBox(tr("Email confirmation"));
	QCheckBox *enable_auto_email_confirmation = new QCheckBox(tr("Auto email confirmation"));

	QComboBox *auto_email_confirmation_template = new QComboBox();
	QComboBox *email_unregister_template = new QComboBox();
	QComboBox *auto_email_confirmation_account = new QComboBox();

	QCheckBox *enable_email_mx_verification = new QCheckBox(tr("Email MX verification"));
	QCheckBox *register_form_name_required = new QCheckBox(tr("Name"));
	QCheckBox *register_form_surname_required = new QCheckBox(tr("Surname"));
	QCheckBox *register_form_city_required = new QCheckBox(tr("City"));
	QCheckBox *register_form_province_required = new QCheckBox(tr("Province"));
	QCheckBox *register_form_country_required = new QCheckBox(tr("Country"));
	QCheckBox *register_form_birthday_required = new QCheckBox(tr("Birthday"));
	QCheckBox *register_form_language_required = new QCheckBox("Language");
	QCheckBox *register_form_sex_required = new QCheckBox("Sex");
	QCheckBox *register_form_use_campaigns = new QCheckBox("Use campaigns");
	QCheckBox *register_form_save_user_agent = new QCheckBox("Save user agent");

	form_mapper->addMapping(register_form_name_required, getRowFromName("register_form_name_required"));
	std::cout << form_mapper->mappedSection(register_form_name_required) << std::endl;
	form_mapper->addMapping(register_form_surname_required, getRowFromName("register_form_surname_required"));
	form_mapper->addMapping(register_form_city_required, getRowFromName("register_form_city_required"));
	form_mapper->addMapping(register_form_province_required, getRowFromName("register_form_province_required"));
	form_mapper->addMapping(register_form_country_required, getRowFromName("register_form_country_required"));
	form_mapper->addMapping(register_form_birthday_required, getRowFromName("register_form_birthday_required"));
	form_mapper->addMapping(register_form_language_required, getRowFromName("register_form_language_required"));
	form_mapper->addMapping(register_form_sex_required, getRowFromName("register_form_sex_required"));
	form_mapper->addMapping(register_form_use_campaigns, getRowFromName("register_form_use_campaigns"));
	form_mapper->addMapping(register_form_save_user_agent, getRowFromName("register_form_save_user_agent"));
	
	QLabel *auto_email_confirmation_template_label = new QLabel(tr("Auto email confirmation template"));
	QLabel *email_unregister_template_label = new QLabel(tr("Email unregister template"));
	QLabel *auto_email_confirmation_account_label = new QLabel(tr("Auto email confirmation account"));

	auto_email_confirmation_template_label->setBuddy(auto_email_confirmation_template);
	email_unregister_template_label->setBuddy(email_unregister_template);
	auto_email_confirmation_account_label->setBuddy(auto_email_confirmation_account);

	core_layout->addWidget(enable_email_confirmation, 0, 0);
	core_layout->addWidget(enable_auto_email_confirmation, 1, 0);
	core_layout->addWidget(auto_email_confirmation_template, 2, 0);
	core_layout->addWidget(email_unregister_template, 3, 0);
	core_layout->addWidget(auto_email_confirmation_account, 4, 0);
	core_layout->addWidget(enable_email_mx_verification, 5, 0);

	QLabel *form_label = new QLabel(tr("Select fields below if required in registration form"));
	form_layout->addWidget(form_label, 0, 0, 1, 2);
	form_layout->addWidget(register_form_name_required,1, 0);
	form_layout->addWidget(register_form_surname_required, 1, 1);
	form_layout->addWidget(register_form_city_required, 2, 0);
	form_layout->addWidget(register_form_province_required, 2, 1);
	form_layout->addWidget(register_form_country_required, 3, 0);
	form_layout->addWidget(register_form_birthday_required, 3, 1);
	form_layout->addWidget(register_form_language_required, 4, 0);
	form_layout->addWidget(register_form_sex_required, 4, 1);
	form_layout->addWidget(register_form_use_campaigns, 5, 0);
	form_layout->addWidget(register_form_save_user_agent, 5, 1);

	core_box->setLayout(core_layout);
	form_box->setLayout(form_layout);

	vbox->addWidget(core_box);
	vbox->addWidget(form_box);

	QPushButton *cancel = new QPushButton("Cancel");
	QPushButton *ok = new QPushButton("Ok");

	QHBoxLayout *hbox = new QHBoxLayout();

	hbox->addStretch();
	hbox->addWidget(cancel);
	hbox->addWidget(ok);

	vbox->addLayout(hbox);
}
