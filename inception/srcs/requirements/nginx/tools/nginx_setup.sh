#!/bin/bash
# shebang -- tells the system that this script is to be executed by /bin/bash

mkdir -p /etc/nginx/ssl

openssl req -x509 -nodes -days 365 \
    -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/inception.key \
    -out /etc/nginx/ssl/inception.crt \
    -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=42/CN=luxu.42.fr"

# start Nginx, making it running on front desk.
# without "daemon off", Nginx will by default become a daemon process
nginx -g "daemon off;"
