# What will be stored in Mariadb?
# 1) Website title
# 2) Administrator and user info
# 3) Articles and pages
# 4) Comments
# 5) Site configuration
# 6) Plugins and theme config

FROM debian:bookworm

RUN apt-get update && \
	apt-get upgrade -y && \
	apt-get install -y \
	mariadb-server \
	mariadb-client && \
	rm -rf /var/lib/apt/lists/* && \
	rm -rf /var/lib/mysql/* && \
	mkdir -p /var/lib/mysql && \
	chown -R mysql:mysql /var/lib/mysql

COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY ./tools/script.sh /usr/local/bin/script.sh

RUN chmod +x /usr/local/bin/script.sh

EXPOSE 3306

CMD ["/usr/local/bin/script.sh"]
