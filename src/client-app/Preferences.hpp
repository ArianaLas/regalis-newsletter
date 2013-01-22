#ifndef __PREFERENCES_HPP_
#define __PREFERENCES_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QComboBox>

class Preferences : public QWidget {
	public:
		Preferences(QWidget *parent = 0);

	protected:
		QVBoxLayout *vbox;
		void init();
		QCheckBox *enable_email_confirmation; 
		QCheckBox *enable_auto_email_confirmation;
		QComboBox *auto_email_confirmation_template;
		QComboBox *email_unregister_template;
		QComboBox *auto_email_confirmation_account;
		QCheckBox *enable_email_mx_verification;
		QCheckBox *register_form_name_required;
		QCheckBox *register_form_surname_required;
		QCheckBox *register_form_city_required;
		QCheckBox *register_form_province_required;
		QCheckBox *register_form_country_required;
		QCheckBox *register_form_birthday_required;
		QCheckBox *register_form_language_required;
};
#endif
