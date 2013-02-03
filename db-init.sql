/*
 * Regalis Newsletter
 * Database initialization scripts
 * Run as privilaged user
 */

create role rnewslettercli with login password 'regalis_newsletter_client';
create database regalis_newsletter owner rnewslettercli;
grant all on database regalis_newsletter to rnewslettercli;
grant all on all tables in schema public to rnewslettercli;

create role rnewslettersrv with login password 'regalis_newsletter_server';
grant connect on database regalis_newsletter to rnewslettersrv;
grant insert, update(confirmed) on subscribers to rnewslettersrv;
