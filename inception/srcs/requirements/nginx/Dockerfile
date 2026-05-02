FROM debian:bookworm

RUN apt update && \
		apt install -y nginx openssl &&\
		apt clean && \
		rm -rf /var/lib/apt/lists/*

COPY ./conf/nginx.conf /etc/nginx/conf.d/nginx.conf

COPY ./tools/nginx_setup.sh /usr/local/bin/nginx_setup.sh

RUN chmod +x /usr/local/bin/nginx_setup.sh

EXPOSE 443

CMD ["/usr/local/bin/nginx_setup.sh"]
