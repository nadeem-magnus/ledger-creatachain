TESTS_JS_PACKAGE = "creatachain-js"
TESTS_JS_DIR = $(CURDIR)/js

ifeq ($(BOLOS_SDK),)
PRODUCTION_BUILD ?= 1
include $(CURDIR)/deps/ledger-zxlib/dockerized_build.mk
else
default:
	$(MAKE) -C app
%:
	$(info "Calling app Makefile for target $@")
	COIN=$(COIN) $(MAKE) -C app $@
endif

test_all:
	make zemu_install
	make
	make zemu_test
