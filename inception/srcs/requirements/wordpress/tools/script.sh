#!/bin/bash

# the whole script will exit if one command fails
set -e

WP_PATH=/var/www/html
DB_PASSWORD=$(cat /run/secrets/db_password)
WP_ADMIN_PASSWORD=$(cat /run/secrets/credentials)
WP_USER_PASSWORD=$(cat /run/secrets/user_password)

mkdir -p ${WP_PATH}
cd ${WP_PATH}

# if the services has already been initialized
if [ ! -f "${WP_PATH}/wp-load.php" ]; then
	echo "WordPress not found. Initializing WordPress files..."
	
# wp-cli is the WordPress command line tool
	curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	mv wp-cli.phar /usr/local/bin/wp

	wp core download --allow-root
	echo ">>Success<< WordPress downloaded."
else
	echo "WordPress already exists. Skipping download."
fi

# Create wp-config.php only if it does not already exist.
# wp-config.php contains the database settings required by WordPress.
# These values come from environment variables passed to the container.
# dbname - The name of the database to connect (e.g. wordpress)
# dbuser - The mariaDB username during connection
# dbpass - The password of this user
# dbhost - The host address of the database server (mariaDB in this case)
if [ ! -f "${WP_PATH}/wp-config.php" ]; then
	echo "wp-config.php not found. Creating wp-config.php..."

	wp config create \
		--allow-root \
		--path=${WP_PATH} \
		--dbname=${WORDPRESS_DB_NAME} \
		--dbuser=${WORDPRESS_DB_USER} \
		--dbpass=${DB_PASSWORD} \
		--dbhost=${WORDPRESS_DB_HOST} \
		--skip-check

	echo ">>Success<< wp-config.php created."
else
	echo "wp-config.php already exists. Skipping creation."
fi

# Wait for WP to connect to mariaDB
# -h: define host
# -u: specify the database user
# -p: define password
# -e "SELECT 1" >/dev/null 2>&1 : connect to the real mysql server and execute a simple command
# until...do: keep retrying until the commands succeeds
echo "Waiting for MariaDB to be ready..."

until mariadb \
	-h"${WORDPRESS_DB_HOST}" \
	-u"${WORDPRESS_DB_USER}" \
	-p"${DB_PASSWORD}" \
	-e "SELECT 1" >/dev/null 2>&1
do
	echo "MariaDB is not ready yet or credentials are invalid.  Waiting..."
	sleep 5
done

echo "MariaDB is ready."

# The corresponding env keys can be found in the .env file
if ! wp core is-installed --allow-root --path=${WP_PATH}; then
	echo "WordPress is not installed yet. Installing..."

	wp core install \
		--allow-root \
		--path=${WP_PATH} \
		--url=${WORDPRESS_URL} \
		--title="${WORDPRESS_TITLE}" \
		--admin_user=${WORDPRESS_ADMIN_USER} \
		--admin_password=${WP_ADMIN_PASSWORD} \
		--admin_email=${WORDPRESS_ADMIN_EMAIL}

	echo ">>Success<< WordPress core installed."
else
	echo "WordPress core already installed. Skipping installation."
fi

if ! wp user get ${WORDPRESS_USER} --allow-root --path=${WP_PATH} >/dev/null 2>&1; then
	echo "WordPress user does not exist yet. Creating..."

	wp user create \
		${WORDPRESS_USER} \
		${WORDPRESS_USER_EMAIL} \
		--user_pass=${WP_USER_PASSWORD} \
		--role=${WORDPRESS_USER_ROLE} \
		--allow-root \
		--path=${WP_PATH}

	echo ">>Success<< WordPress user created."
else
	echo "WordPress user already exists. Skipping creation."
fi

echo "Starting php-fpm..."

# exec - replace the current shell process with php-fpm process
# -F means to run in foreground
exec /usr/sbin/php-fpm8.2 -F
