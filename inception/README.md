*This project has been created as part of the 42 curriculum by luxu.*

# Inception

## Description
The 42 Inception project focuses on learning system administration using Docker in a virtual machine.
Its goal is to build a small web infrastructure composed by separate Docker containers (Nginx, WordPress with php-fpm and MariaDB).

### Docker, Docker images, Docker containers
- Docker is a platform used to package and run applications in isolated environments. 
- A Docker image is a read-only template that contains everything needed to launch a service, such as the operating system base, installed packages, configuration files, and startup commands. 
- A Docker container is a running instance of an image. In this project, Docker is used to separate NGINX, WordPress with php-fpm, and MariaDB into different containers, making the infrastructure more modular, reproducible, and easier to manage.

#### What's the difference between virtual machines and Docker containers?
- They both provide isolated environments with different working method
- A virtual machine includes a full guest operating system and runs on top of a hypervisor, which makes it heavier in terms of storage.
- Docker containers do not include a full operating system. They share the host kernel while keeping applications isolated through containerization.

### NGINX
Nginx is the web server of this project and the only public entry point to the infrastructure.
It listens on port 443 and handles HTTPS requests using TLSv1.2 or TLSv1.3.
In this project, NGINX serves the WordPress website and forwards PHP requests to WordPress through php-fpm.

### WordPress, FastCGI and php-fpm
- WordPress is the content management system used to build and manage the website.
- FastCGI is a protocol that allows NGINX to communicate with an external application for dynamic content processing.
- php-fpm (PHP FastCGI Process Manager) is the service that executes PHP code and works as the backend of WordPress in this project.

### MariaDB
MariaDB is the relational database service used by WordPress.
It stores persistent website data such as users, posts, pages, comments as well as websites.

### Docker networks
A Docker container network is the communication layer that allows containers to reach each other while remaining isolated from unrelated services.
Its connection logic is described in the docker compose file.

#### Docker network vs Host network
- A Docker network keeps containers isolated from the host and from unrelated containers while keeping the communication between the services within the project.
- A host network removes the isolation and makes the container share the host networking stack directly.
- In *Inception* project, the Docker network is essential because the infrastructure is separated into several containers. And the only acces exposed to the host is NGINX, demanded by the subject.

#### Secrets and environment variables
- Secrets and environment variables are both used to pass configuration values to containers, but they are not meant to pass the same type of data.
- Environment variables are used to pass non-sensitive values such as domain name, database name, username, site titles, etc. 
- Secrets can be useful for confidential values such as passwords, because they should not be stored directly inside the Git repository.
- In *Inception* project, the .env file has regular config variables required by docker compose. All the passwords are stored locally on the VM and mounted as Docker secrets at runtime.

#### Docker volumes and bind mounts
- Docker volumes and bind mounts are both used to persist data outside a container, but they are different in how they are managed:
    - A docker volume is managed by Docker itself and is generally the recommanded solution for persistent container data, because it is more portable, more isolated from the host system, easier to maintain.
    - A bind mount directly connects a container to a specific directory on the host machine, which makes the container more dependent on the host system structure, which risks losing the advantage of its portable nature.
    - In *Inception* project, Docker volumes are preferred because WordPress and MariaDB need persistent storage that remains independent from the internal container life cycle.

## Instructions
This project contains a Makefile to build, start, stop, restart, monitor and clean up the Docker infrastructure.
- To build and start the project: `make`
- To build the images only: `make build`
- To start existing containers: `make start`
- To stop the containers: `make stop`
- To stop and remove the containers: `make down`
- To restart the containers: `make restart`
- To view the logs: `make logs` 
- To display the status of the containers: `make ps`
- To remove containers and images:  `make clean`
- To remove containers, images and volumes: `make fclean`

## Resources
Following are the documents/articles/tutorials reference:
- The introduction of the project: https://medium.com/@imyzf/inception-3979046d90a0
- Docker basic knowledge of Docker: https://docs.docker.com
- Nginx service: https://nginx.org/en/docs/beginners_guide.html
- WordPress service/Fast CGI/php-fpm: https://github.com/Forstman1/inception-42
- MariaDB service: https://mariadb.com/docs/server/mariadb-quickstart-guides
- Volumes managing: https://docs.docker.com/engine/storage/bind-mounts/

### AI usage in this project:
- Typo checks in documentation
- Analysing error messages during the image/container build and exec checking inside the container

### Secrets and configuration
- Non-sensitive configuration is stored in srcs/.env
- Sensitive passwords are stored in local files inside secrets/
- Docker Compose mounts these files as Docker secrets at runtime

### Domain configuration

The final project domain is luxu.42.fr.
For local testing, the host machine may require an /etc/hosts entry such as:
```text
127.0.0.1 luxu.42.fr
```