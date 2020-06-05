MAKE_DIR = $(PWD)

COMMON_DIR := $(MAKE_DIR)/Common
SERVER_DIR := $(MAKE_DIR)/Server
CLIENT_DIR := $(MAKE_DIR)/Client




all:

    $(MAKE) -C Common
    $(MAKE) -C Server
    $(MAKE) -C Client


