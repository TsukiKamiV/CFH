NAME = inception

COMPOSE_FILE = ./srcs/docker-compose.yml
ENV_FILE = ./srcs/.env

DC = docker compose -f $(COMPOSE_FILE) --env-file $(ENV_FILE)

SECRET_DIR = ./secrets
ADMIN_SECRET = $(SECRET_DIR)/credentials.txt
DB_SECRET = $(SECRET_DIR)/db_password.txt
DB_ROOT_SECRET = $(SECRET_DIR)/db_root_password.txt
USER_SECRET = $(SECRET_DIR)/user_password.txt

all:	up

check:
	@if [ ! -f $(ENV_FILE) ]; then \
		echo ".env file not found: $(ENV_FILE)"; \
		exit 1; \
	fi
	@if [ ! -f $(ADMIN_SECRET) ]; then \
		echo "Missing secret file: $(ADMIN_SECRET)"; \
		exit 1; \
	fi
	@if [ ! -f $(DB_SECRET) ]; then \
		echo "Missing secret file: $(DB_SECRET)"; \
		exit 1; \
	fi
	@if [ ! -f $(DB_ROOT_SECRET) ]; then \
		echo "Missing secret file: $(DB_ROOT_SECRET)"; \
		exit 1; \
	fi
	@if [ ! -f ${USER_SECRET} ]; then \
		echo "Missing secret file: $(USER_SECRET)"; \
		exit 1; \
	fi

build: check
	$(DC) build

up: check
	$(DC) up -d --build

down:
	$(DC) down

start:
	$(DC) start

stop:
	$(DC) stop

restart: down up

logs:
	$(DC) logs -f

ps:
	$(DC) ps

clean:
	$(DC) down --rmi all

fclean:
	$(DC) down -v --rmi all

re: fclean up

.PHONY: all check build up down start stop restart logs ps clean fclean re
