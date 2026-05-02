# Developer Documentation

## Overview

This document explains how to set up, build, run, and maintain the Inception project from a developer perspective.

## Project structure

```text
inception/
├── Makefile
├── README.md
├── USER_DOC.md
├── DEV_DOC.md
├── secrets/
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        ├── nginx/
        └── wordpress/
```

## Prerequisites
	•	Docker
	•	Docker Compose
	•	A local secrets/ directory with the required secret files
	•	A valid srcs/.env file

## Required local files

- The following files must exist before starting the project:
	-	srcs/.env
	-	secrets/credentials.txt
	-	secrets/db_password.txt
	-	secrets/db_root_password.txt
	-	secrets/user_password.txt

## Build and run
 From the repository root, run`make`. \
 This command checks the required files, builds the images, and start the containers.
 - Useful commands:
    - `make build`
    - `make up`
    - `make down`
    - `make start`
    - `make stop`
    - `make restart`
    - `make logs`
    - `make ps`
    - `make clean`
    - `make fclean`
    - `make re`

## Services
The project is composed of three main services:
-	nginx: the only public entry point, exposed on port 443
-	wordpress: runs WordPress with php-fpm
-	mariadb: stores persistent database data

Each service has its own Dockerfile, configuration files, and startup script inside `srcs/requirements/`.

## Data persistence

The project uses two named volumes:
- one for WordPress website files
- one for MariaDB data

These volumes preserve data beyond the lifecycle of individual containers.

## Domain configuration

The final project domain is luxu.42.fr.

For local testing, the host machine may require an `/etc/hosts` entry such as:
```text
127.0.0.1 luxu.42.fr
```

## Notes
- `make fclean` removes containers, images, and volumes
- After `make fclean`, the infrastructure is rebuilt from scratch on the next launch
- On the school VM, final volume storage must comply with the subject requirements