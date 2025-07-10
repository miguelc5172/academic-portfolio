DATA_DIR=data
LOGS_DIR=logs

.PHONY: help setup up down clean rebuild

help:
	@echo "Available commands:"
	@echo "  make setup     - Create necessary folders for mounting (data/, logs/)"
	@echo "  make up        - Build the docker image and start the container"
	@echo "  make down      - Stop and remove the containers"
	@echo "  make clean     - Remove containers, volumes, and folders"
	@echo "  make rebuild   - Clean everything and rebuild from scratch"

setup:
	@mkdir -p $(DATA_DIR)
	@mkdir -p $(LOGS_DIR)

up: setup
	docker-compose up --build

down:
	docker-compose down

clean: down
	@rm -rf $(DATA_DIR) $(LOGS_DIR)

rebuild: clean 
	docker-compose build