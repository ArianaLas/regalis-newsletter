# Regalis Newsletter

Simple centralized newsletter system.

**Warning**, this project is under heavy development. Checkout the **develop** branch to see current stage.

# About

Regalis Newsletter is complete project enabling mass correspondence intended for small and medium companies and organizations.

# Features

* subscribers managenent
	* subscribers view with manual changes posibility 
	* campaigns: 
		* subscribers are signing into campaign theirselves
		* several group can receive emails connected with separate topics
	* groups: 
		* owner can divide subscribers himself
		* sending emails to company employees
* emails
	* templates (for example header, footer, constant information)
	* sending emails to groups, campaigns or non standard for example to people from Cracow
	* dynamic per user variables
	* static variables defined by owner
* signing into newsletter
	* subscriber form generator
	* form settings in client app panel
* accounts
	* sending emails from several email addresses
* attachments
	* enable to send email with attachments
* language
	* GUI application and subscriber form are multi-language
	* subscriber can choose language in which emails will be sended
* statiscics
* installation
	* step by step instalation with configuration

## Database tables diagram

## Database scheme

## Indexes

## Views

Mostly used in dashboard statistics

* amount of all subscribers
* amount of subscribers signed into several groups
* amount of subscribers signed into several campaigns
* amount of sended newsletters
* amount of days which elapsed from sending last newsletter
* amount of subscribers who signed to newsletter from date of last sended newsletter
* amount of emails in several groups
* amount of emails in several campaigns
* amount of subscribers who signed out from newsletter
* amount of subscribers who signed out from newsletter in several campaigns

## Procedures

Used in PHP code 

* add new subscriber
* delete subscriber

## Triggers

* if subscriber signed out from newsletter, field signed\_out in settings table is increasing
* automaticly adding new subscriber to email which is already written

## Script creating database

look at -> `database-init.sh`

## Typical queries

## Used technology

* database:
	* PosgreSQL
* client app:
	* C++
	* QT
* server app:
	* PHP5
	* HTML5
	* CSS3
* auxiliary:
	* GIT
	* MySQL Workbench
	* VIM

## Authors

* Patryk Jaworski \<regalis@regalis.com.pl\>
* Ariana Las \<ariana.las@gmail.com\>

# License

GNU/GPLv3
