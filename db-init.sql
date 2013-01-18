/*
 * Regalis Newsletter
 * Database initialization scripts
 * Run as user with grant option
 */

create user 'rnewsletter'@'localhost' identified by 'regalis_newsletter';
create database regalis_newsletter;
grant create, select, insert, update, delete, alter, drop on regalis_newsletter.* to 'rnewsletter'@'localhost'
