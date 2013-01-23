#include <QLabel>
#include <QString>
#include <QGroupBox>
#include <QGridLayout>

#include "Preferences.hpp"

Preferences::Preferences(QWidget *parent) : QWidget(parent) {
	setWindowTitle(tr("Preferences"));
	vbox = new QVBoxLayout(this);
	init();
	setLayout(vbox);
}

void Preferences::init() {
	QGroupBox *core_box = new QGroupBox(tr("Core settings"));
	QGroupBox *form_box = new QGroupBox(tr("Form settings"));

	QGridLayout *core_layout = new QGridLayout();
	QGridLayout *form_layout = new QGridLayout();

	enable_email_confirmation = new QCheckBox(tr("Email confirmation"));
	enable_auto_email_confirmation = new QCheckBox(tr("Auto email confirmation"));

	auto_email_confirmation_template = new QComboBox();
	email_unregister_template = new QComboBox();
	auto_email_confirmation_account = new QComboBox();

	enable_email_mx_verification = new QCheckBox(tr("Email MX verification"));
	register_form_name_required = new QCheckBox(tr("Name"));
	register_form_surname_required = new QCheckBox(tr("Surname"));
	register_form_city_required = new QCheckBox(tr("City"));
	register_form_province_required = new QCheckBox(tr("province"));
	register_form_country_required = new QCheckBox(tr("Country"));
	register_form_birthday_required = new QCheckBox(tr("Birthday"));
	register_form_language_required = new QCheckBox("Language");

	


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

	QLabel *form_label = new QLabel(tr("Select fields below if required"));
	form_layout->addWidget(form_label, 0, 0, 1, 2);
	form_layout->addWidget(register_form_name_required,1, 0);
	form_layout->addWidget(register_form_surname_required, 1, 1);
	form_layout->addWidget(register_form_city_required, 2, 0);
	form_layout->addWidget(register_form_province_required, 2, 1);
	form_layout->addWidget(register_form_country_required, 3, 0);
	form_layout->addWidget(register_form_birthday_required, 3, 1);
	form_layout->addWidget(register_form_language_required, 4, 0);

	core_box->setLayout(core_layout);
	form_box->setLayout(form_layout);

	vbox->addWidget(core_box);
	vbox->addWidget(form_box);
}
