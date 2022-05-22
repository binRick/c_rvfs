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
##########################################################
GC=$(GIT) clone --recurse-submodules
GET_COMMIT=$(GIT) log -q |grep '^commit '|head -n1|cut -d' ' -f2
##########################################################
TEST_TITLE=$(BLINE) -a bold:underline:italic:yellow
HELP_STYLE=$(BLINE) -H -a ff00ff
##########################################################
DEV_MAKE_TARGETS = \
					clean \
                	build \
					test
DEV_TEST_TARGETS = \
				   test-rvfs_e
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
uncrustify:
	@uncrustify -c etc/uncrustify.cfg --replace bins/*.c
	@shfmt -w scripts/*.sh
fix-dbg:
	@gsed 's|, % s);|, %s);|g' -i bins/*.c
	@gsed 's|, % lu);|, %lu);|g' -i bins/*.c
	@gsed 's|, % d);|, %d);|g' -i bins/*.c
	@gsed 's|, % zu);|, %zu);|g' -i bins/*.c
uncrustify-clean:   
	@find . -type f -name "*unc-back*"|xargs -I % unlink %
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
	@make _build || { make clean && make _build; }
##//##//##//##//##//##//##//##//##//##//##//##	
all: build
setup: clibs-install submodules-install tools
install:
	@echo Install OK
do-bins: make-bins
##//##//##//##//##//##//##//##//##//##//##//##	
dev: 
	@$(PASSH) -L .nodemon.log $(NODEMON) -I -V -w 'include/*.h' -w meson -w meson.build -w bins -w src -w Makefile -i $(BUILD_DIR) -i submodules -i deps -e build,sh,c,h,Makefile -x env -- bash -c 'make $(DEV_MAKE_TARGETS) $(DEV_TEST_TARGETS)||true'
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
