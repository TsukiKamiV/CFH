#!/bin/bash

set -e

DB_PATH=/var/lib/mysql
DB_PASSWORD=$(cat /run/secrets/db_password)
DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)

mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld
chown -R mysql:mysql ${DB_PATH}

if [ ! -d "${DB_PATH}/mysql" ]; then
	echo "MariaDB data directory not found. Initializing database..."

	mariadb-install-db --user=mysql --datadir=${DB_PATH}
	echo "Starting temporary MariaDB server..."
	mysqld_safe --datadir=${DB_PATH} &

	echo "Waiting for temporary MariaDB server to be ready..."
	while ! mariadb-admin ping --silent
	do
		sleep 2
	done

	echo "Creating database and user..."
	mariadb -u root << EOF

-- Create the WordPress database if it does not already exist.
CREATE DATABASE IF NOT EXISTS ${MARIADB_DATABASE};

-- Create a database user for WordPress if it does not already exist.
-- '%' means this user can connect from any host, which is useful for
-- container-to-container communication in Docker.
CREATE USER IF NOT EXISTS '${MARIADB_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';

-- Give this user all privilieges on the WordPress database only.
-- This allows WordPress to read, write, update, and manage its own tables.
GRANT ALL PRIVILEGES ON ${MARIADB_DATABASE}.* TO '${MARIADB_USER}'@'%';

-- Set or update the password for the local MariaDB root account
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASSWORD}';

-- Reload the priviliege tables so that all user and permission changes
-- are applied immediately.
FLUSH PRIVILEGES;

EOF

	echo "Stopping temporary MariaDB server..."
	mysqladmin -u root -p${DB_ROOT_PASSWORD} shutdown

	echo ">>Success<< MariaDB initialized."
else
	echo "MariaDB already initialized. Skipping setup."
fi


echo "Starting MariaDB server..."
exec mysqld --user=mysql --console
