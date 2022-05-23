default: all
##########################################################
COLORS_QTY = 50
EMBEDDED0_VIEW_QTY = 10
NINJA_CONCURRENCY = 25
##########################################################
all: \
    build 
##########################################################
PWD=$(shell pwd)
ETC=$(PWD)/etc
BUILD_DIR=$(PWD)/build
INCLUDES_DIR=$(PWD)/include
##########################################################
PASSH=$(shell command -v passh)
GIT=$(shell command -v git)
SED=$(shell command -v gsed||command -v sed)
NODEMON=$(shell command -v nodemon)
FZF=$(shell command -v fzf)
BLINE=$(shell command -v bline)
ANSI=$(shell command -v ansi)
STAT=$(shell command -v stat)
##########################################################
GC=$(GIT) clone --recurse-submodules
GET_COMMIT=$(GIT) log -q |grep '^commit '|head -n1|cut -d' ' -f2
##########################################################
TEST_TITLE=$(BLINE) -a bold:underline:italic:yellow
HELP_STYLE=$(BLINE) -H -a ff00ff
RVFS1_STYLE=$(BLINE) -a bold:italic:blue
##########################################################
##//##//##//##//##//##//##//##//##//##//##//##	
DEV_MAKE_TARGETS = \
				    reset \
               		build
CLEAN_DEV_MAKE_TARGETS = \
					clean \
					$(DEV_MAKE_TARGETS)
DEV_TEST_TARGETS = \
				   test \
				   test-rvfs_e \
				   test-rvfs1
##//##//##//##//##//##//##//##//##//##//##//##	
NODEMON_CMD = $(PASSH) -L .nodemon.log $(NODEMON) -I -V -w 'include/*.h' -w meson_options.txt -w meson -w meson.build -w bins -w src -w Makefile -i $(BUILD_DIR) -i submodules -i deps -e build,sh,c,h,Makefile -x env -- bash -c
##//##//##//##//##//##//##//##//##//##//##//##	
reset:
	@reset
test-rvfs1:
	@if [[ -f /tmp/rvfs1-meson.rvfs ]]; then  unlink /tmp/rvfs1-meson.rvfs; fi
	@if [[ -d /tmp/rvfs1 ]]; then rm -rf /tmp/rvfs1; fi
	@$(PASSH) ./build/rvfs1 --help | $(TEST_TITLE)
	@$(PASSH) ./build/rvfs1 package ./bins /tmp/rvfs1-meson.rvfs
	@$(PASSH) ./build/rvfs1 show /tmp/rvfs1-meson.rvfs
	@$(PASSH) ./build/rvfs1 filesqty ////BAD-FILENAME || { $(ANSI) --green --bold -n "OK> " && $(ANSI) --red --bg-black --bold POSITIVE-FAILURE-CASE-0; }
	@$(PASSH) ./build/rvfs1 filesqty /tmp/rvfs1-meson.rvfs
	@$(PASSH) ./build/rvfs1 filenames /tmp/rvfs1-meson.rvfs
	@[[ -d /tmp/rvfs_e ]] || mkdir /tmp/rvfs1
	@$(PASSH) ./build/rvfs_e extract /tmp/rvfs1-meson.rvfs /tmp/rvfs1|$(RVFS1_STYLE)
	@{ find /tmp/rvfs1 -type f|xargs -I {} $(STAT) -c '%30n -> %sb' {}; } | $(BLINE) -a bold:yellow
	@if [[ -f /tmp/rvfs1-meson.rvfs ]]; then  unlink /tmp/rvfs1-meson.rvfs; fi
	@if [[ -d /tmp/rvfs1 ]]; then rm -rf /tmp/rvfs1; fi
	@$(ANSI) --green "test-rvfs1 Tests OK"
##########################################################
enabled-bins:
	@grep 'MESON_BIN_ENABLED=true' bins/*.c|cut -d: -f1|sort -u|xargs -I % basename % .c
make-setup:
	@[[ -d deps ]] || { mkdir -p deps && make setup; }
	@[[ -d submodules ]] || { mkdir -p submodules && make setup; }
tools:
	@command -v nodemon || npm i nodemon -g
	@command -v meson || pip install meson
##//##//##//##//##//##//##//##//##//##//##//##	
clean: uncrustify-clean
	@[[ -d $(BUILD_DIR) ]] && rm -rf $(BUILD_DIR) || true
tidy: uncrustify fix-dbg uncrustify-clean
##//##//##//##//##//##//##//##//##//##//##//##	
clib-update:
	@./update_commit.sh
clibs-cmds:
	@./scripts/clib-cmds.sh
clibs-install:
	@./scripts/clib-cmds.sh|env bash
##//##//##//##//##//##//##//##//##//##//##//##	
git-commit:
	@git commit -am 'automated git commit'
push: tidy git-commit
	git push
git-pull:
	@git pull
pull: git-pull clib build test
##//##//##//##//##//##//##//##//##//##//##//##	
submodules-cmds:
	@./scripts/submodules.sh
submodules-install:
	@./scripts/submodule-cmds.sh|env bash
##//##//##//##//##//##//##//##//##//##//##//##	
uncrustify: _uncrustify uncrustify-clean
_uncrustify:
	@uncrustify -c etc/uncrustify.cfg --replace bins/*.c src/*.c include/*.h
	@shfmt -w scripts/*.sh
fix-dbg:
	@gsed 's|, % s);|, %s);|g' -i bins/*.c
	@gsed 's|, % lu);|, %lu);|g' -i bins/*.c
	@gsed 's|, % d);|, %d);|g' -i bins/*.c
	@gsed 's|, % zu);|, %zu);|g' -i bins/*.c
uncrustify-clean:   
	@find . -type f -name "*unc-back*"|xargs -I % unlink % 2>/dev/null||true
##//##//##//##//##//##//##//##//##//##//##//##	
test: _test test-rvfs_e 
_test:
	@meson test -C $(BUILD_DIR) --verbose
_meson-build:
	@meson $(BUILD_DIR)
meson-build:
	@make _meson-build || { make meson-reconfigure || make meson-wipe || make _meson-build; }
	@true
meson-wipe:
	@meson $(BUILD_DIR) --wipe
meson-reconfigure:
	@{ meson $(BUILD_DIR) --reconfigure || { make meson-wipe && make meson-reconfigure; }; } || { make meson-wipe && make build; }
	@true
##//##//##//##//##//##//##//##//##//##//##//##	
ninja-build:
	@ninja -C build -j $(NINJA_CONCURRENCY)
_build: make-setup meson-build ninja-build
build:
	@make _build
#	|| { make clean && make _build; }
##//##//##//##//##//##//##//##//##//##//##//##	
all: build
setup: clibs-install submodules-install tools
install:
	@echo Install OK
do-bins: make-bins
##//##//##//##//##//##//##//##//##//##//##//##	
clean-dev: 
	@$(NODEMON_CMD) 'make $(CLEAN_DEV_MAKE_TARGETS) $(DEV_TEST_TARGETS)||true'
dev: 
	@$(NODEMON_CMD) 'make $(DEV_MAKE_TARGETS) $(DEV_TEST_TARGETS)||true'
nodemon:
	@$(PASSH) make
##//##//##//##//##//##//##//##//##//##//##//##	
test-rvfs_e:
	@./build/rvfs_e --help | $(TEST_TITLE)
	@./build/rvfs_e package ./src /tmp/rvfs_e-src.rvfs
	@./build/rvfs_e show /tmp/rvfs_e-src.rvfs
	@./build/rvfs_e find /tmp/rvfs_e-src.rvfs /rvfs.c
	@./build/rvfs_e find /tmp/rvfs_e-src.rvfs /includes.c
	@[[ -d /tmp/rvfs_e ]] || mkdir /tmp/rvfs_e
	@./build/rvfs_e extract /tmp/rvfs_e-src.rvfs /tmp/rvfs_e
	@find /tmp/rvfs_e
	@du --max-depth=1 -h /tmp/rvfs_e
	@unlink /tmp/rvfs_e-src.rvfs
	@rm -rf /tmp/rvfs_e
##//##//##//##//##//##//##//##//##//##//##//##	
