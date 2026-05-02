# User Documentation

## Overview

This document explains how to use the Inception stack as an end user or administrator.

## Provided services

The stack provides three main services:

- `nginx`: the public HTTPS entry point on port `443`
- `wordpress`: the website application running with `php-fpm`
- `mariadb`: the database used by WordPress

## Start and stop the project

From the repository root, use:

- `make` to build and start the project
- `make stop` to stop running containers
- `make start` to start existing containers again
- `make down` to stop and remove the containers
- `make restart` to restart the infrastructure

## Access the website and the admin panel

Use the configured domain in your browser:

- `https://luxu.42.fr`
- `https://luxu.42.fr/wp-admin`

For local testing, the host machine may need an `/etc/hosts` entry such as:

`127.0.0.1 luxu.42.fr`

## Credentials and secrets

The project uses local secret files for sensitive passwords.
These files must be created locally inside the `secrets/` directory and must not be committed to the Git repository.

Example local secret files:

- `secrets/credentials.txt`
- `secrets/db_password.txt`
- `secrets/db_root_password.txt`
- `secrets/user_password.txt`

## Check that the services are running correctly

Use the following commands from the repository root:

- `make ps` to check container status
- `make logs` to display container logs

If the infrastructure is working correctly, the website should open through HTTPS and the WordPress admin page should be reachable at `/wp-admin`.