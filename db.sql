create table if not exists subscribers {
	id int unsigned not null auto_increment primary key,
	name char(100),
	surname char(100),
	email char(150) not null,
	city char(100),
	province char(100),
	address char(100),
	country char(100),
	sex enum('M','F'),
	birthday date,
	user_agent char(255),
	registered date not null,
	confirmed date default null
};

create table if not exists languages {
	code char(20) not null primary key,
	name char(255) not null
};

create table if not exists subscribers_languages {
	subscriber_id int unsigned not null,
	language_code int unsigned not null
};

create table if not exists groups {
	id int unsigned not null auto_increment primary key,
	name char(255),
	description tinytext
};

create table if not exists group_members {
	subscriber_id int unsigned not null,
	group_id int unsigned not null
};

create table if not exists campaigns {
	id int unsigned not null auto_increment primary key,
	name char(255) not null,
	description tinytext,
	type enum('public', 'private')
};

create table if not exists campaigns_members {
	subscriber_id int unsigned not null,
	campaign_int unsigned not null
};

create table if not exists templates {
	id int unsigned not null auto_increment primary key,
	name char(255) not null,
	content text not null
};

create table if not exists accounts {
	id int unsigned not null auto_increment primary key,
	name char(255) not null,
	from char(255),
	host char(255) not null,
	user char(255) not null,
	pass char(255) not null,
	port char(255) not null,
	description tinytext
};

create table if not exists settings {
	key char(100) not null primary key,
	int_value int default null,
	char_value char(255) default null
};

create table if not exists newsletters {
	id int unsigned not null auto_increment primary key,
	name char(200) not null,
	account_id int unsigned not null,
	subject char(255) not null,
	body text,
	body_sent text default null,
	sent date default null
};

create table if not exists newsletters_campaigns {
	newsletter_id int unsigned not null,
	campaign_id int unsigned not null
};

create table if not exists newsletters_receivers {
	newsletter_id int unsigned not null,
	subscriber_id int unsigned not null
	sent date default null,
	comment tinytext default null,
};

create table if not exists newsletters_headers {
	newsletter_id int unsigned not null,
	name char(255),
	value char(255)
};

insert into settings(key, int_value) values ('enable_email_confirmation', 1);
insert into settings(key, int_value) values ('enable_auto_email_confirmation', 1);
insert into settings(key, char_value) values ('auto_email_confirmation_template', '');
insert into settings(key, char_value) values ('email_unregister_template', '');
insert into settings(key, int_value) values ('auto_email_confirmation_account', -1);
insert into settings(key, int_value) values ('enable_email_mx_verification', 1);
insert into settings(key, int_value) values ('register_form_name_required', 0);
insert into settings(key, int_value) values ('register_form_surname_required', 0);
insert into settings(key, int_value) values ('register_form_city_required', 0);
insert into settings(key, int_value) values ('register_form_povince_required', 0);
insert into settings(key, int_value) values ('register_form_country_required', 0);
insert into settings(key, int_value) values ('register_form_birthday_required', 0);
insert into settings(key, int_value) values ('register_form_language_required', 0);
insert into settings(key, int_value) values ('register_form_sex_required', 0);
insert into settings(key, int_value) values ('register_form_use_campaigns', 0);
insert into settings(key, int_value) values ('register_form_save_user_agent', 0);

