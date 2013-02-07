
/* Data types */

create type sex_t as enum ('male', 'female');
create type access_t as enum ('public', 'private');

/* Tables */

create table if not exists subscribers (
	id serial primary key,
	name varchar(100),
	surname varchar(100),
	email varchar(150) not null,
	city varchar(100),
	province varchar(100),
	address varchar(100),
	country varchar(100),
	sex sex_t,
	birthday timestamp,
	user_agent varchar(255),
	registered timestamp not null,
	confirmed timestamp default null
);

create table if not exists languages (
	code varchar(20) primary key,
	name varchar(255) not null
);

create table if not exists subscribers_languages (
	subscriber_id integer not null references subscribers(id) on delete cascade,
	language_code varchar(20) not null references languages(code) on delete cascade,
	primary key(subscriber_id, language_code)
);

create table if not exists groups (
	id serial primary key,
	name varchar(255) not null,
	description text default null
);

create table if not exists group_members (
	subscriber_id integer not null references subscribers(id) on delete cascade,
	group_id integer not null references groups(id) on delete cascade,
	primary key(subscriber_id, group_id)
);

create table if not exists campaigns (
	id serial primary key,
	name varchar(255) not null,
	description text,
	type access_t not null default 'private'
);

create table if not exists campaigns_members (
	subscriber_id integer not null references subscribers(id) on delete cascade,
	campaign_id integer not null references campaigns(id) on delete cascade,
	primary key(subscriber_id, campaign_id)
);

create table if not exists templates (
	id serial primary key,
	name varchar(255) not null,
	content text not null
);

create table if not exists accounts (
	id serial primary key,
	name varchar(255) not null,
	email varchar(255) not null,
	header_from varchar(255),
	smtp_host varchar(255) not null,
	smtp_user varchar(255) not null,
	smtp_pass varchar(255) not null,
	smtp_port varchar(255) not null,
	description text
);

create table if not exists settings (
	name varchar(100) not null primary key,
	int_value integer default null,
	varchar_value varchar(255) default null,
	bool_value bool default null
);

create table if not exists newsletters (
	id serial primary key,
	name varchar(200) not null,
	account_id integer not null references accounts(id) on delete set null,
	subject varchar(255) not null,
	body text,
	body_sent text default null,
	sent timestamp default null
);

create table if not exists newsletters_campaigns (
	newsletter_id integer not null references newsletters(id) on delete cascade,
	campaign_id integer not null references campaigns(id) on delete cascade,
	primary key(newsletter_id, campaign_id)
);

create table if not exists newsletters_receivers (
	newsletter_id integer not null references newsletters(id) on delete cascade,
	subscriber_id integer not null references subscribers(id) on delete cascade,
	sent timestamp default null,
	description text default null,
	primary key(newsletter_id, subscriber_id)
);

create table if not exists newsletters_headers (
	newsletter_id integer not null references newsletters(id) on delete cascade,
	name varchar(255),
	value varchar(255),
	primary key(newsletter_id, name)
);

create table if not exists user_variables (
	name varchar(100) primary key,
	value varchar(255) not null
);

create table if not exists attachments (
	id serial primary key,
	file_name varchar(255) not null,
	mime varchar(255) not null default 'application/octet-stream',
	content bytea not null
);

create table if not exists attachments_newsletters (
	attachment_id integer not null references attachments(id) on delete cascade,
	newsletter_id integer not null references newsletters(id) on delete cascade,
	primary key(attachment_id, newsletter_id)
);

/* Default settings */

insert into settings(name, int_value) values ('database_version', 0);
insert into settings(name, bool_value) values ('enable_email_confirmation', '1');
insert into settings(name, bool_value) values ('enable_auto_email_confirmation', '1');
insert into settings(name, int_value) values ('auto_email_confirmation_template', -1);
insert into settings(name, int_value) values ('email_unregister_template', -1);
insert into settings(name, int_value) values ('auto_email_confirmation_account', -1);
insert into settings(name, bool_value) values ('enable_email_mx_verification', '1');
insert into settings(name, bool_value) values ('register_form_name_required', '0');
insert into settings(name, bool_value) values ('register_form_surname_required', '0');
insert into settings(name, bool_value) values ('register_form_city_required', '0');
insert into settings(name, bool_value) values ('register_form_province_required', '0');
insert into settings(name, bool_value) values ('register_form_country_required', '0');
insert into settings(name, bool_value) values ('register_form_birthday_required', '0');
insert into settings(name, bool_value) values ('register_form_language_required', '0');
insert into settings(name, bool_value) values ('register_form_sex_required', '0');
insert into settings(name, bool_value) values ('register_form_use_campaigns', '0');
insert into settings(name, bool_value) values ('register_form_save_user_agent', '0');
insert into settings(name, int_value) values ('amount_of_unregistered_subscribers', '0'); 
insert into settings(name, bool_value) values ('automatically_add_new_subscribers', '0');

create view subscribers_count as 
	select count(*) from subscribers;

create view subscribers_count_groups as 
	select id, name, count(*) from groups left join group_members on groups.id=group_members.group_id group by id order by name;

create view subscribers_count_campaigns as 
	select id, name, count(*) from campaigns left join campaigns_members on campaigns.id=campaigns_members.campaigns_id group by id order by name;

create view newsletters_count as 
	select count(*) from newsletter;
/*
create view days_since_last_newsletter as 
	select extract(day from timestamp (select max(sent) from newsletters) - current_timestamp);

create view new_subscribers_count as select count(*) from subscribers;

create view emails_count_groups as select count(*) from subscribers;

create view emails_count_campaigns as select count(*) from subscribers;

create view unregistered_count as select count(*) from subscribers;

create view unregistered_count_campaigns as select count(*) from subscribers;
*/
