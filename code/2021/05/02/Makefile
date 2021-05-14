BUILD_DIR ?= _build

# TODO(Drogon): Document makefile

define run_build
	@# env $1
	$(1) cmake --build $(BUILD_DIR) --config Release -- -j $(shell nproc)
endef

.PHONY: build
build:
	@# -DCMAKE_LINK_WHAT_YOU_USE=TRUE; OSX ld: unknown option: --no-as-needed
	@cmake -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Release .
	$(call run_build, LINTERS=ALL)

.PHONY: build_offlint
build_offlint:
	$(call run_build, LINT=OFF)


.PHONY: ci
ci: update lint test

.PHONY: lint
lint: cpplint

.PHONY: cpplint
cpplint:
	git ls-files include src | egrep '.*\.(h|cc)' | xargs cpplint

.PHONY: spell
spell:
	@#find . -type f -not -path "./vendor/*" -print0 | xargs -0 misspell
	find . -type f -not -path "./_build/*" -print0 -not -path "tags" | xargs -0 misspell

# check-style:
# git ls-files include src | egrep '.*\.(h|cc)' | xargs python3 dev-tools/check-style.py

.PHONY: format
format:
	git ls-files | egrep '.*\.(h|cc)' | xargs clang-format -style=file -i

.PHONY: update
update:
	blade build --update-deps -p debug --bundle debug

.PHONY: release
release:
	blade build --update-deps -p release

.PHONY: debug
debug:
	blade build -p debug --bundle debug

.PHONY: test
# dep build, ignore it for build dummy output
test: build
	@ctest --test-dir $(BUILD_DIR)

.PHONY: devtools
# install devtools
devtools:
	@dev-tools/install.sh

# force-test: build
# 	@ctest --test-dir $(BUILD_DIR)

# spell: misspell
# align golang tools

# format
# cpplint, clang, gcc
# cppcheck flint
# clang-tidy, clang-analyzer
# coverity
# perf
# flamegraph
# bundle
# facebook anyalzer
# 公司的那个软件
# 那个SLDC的 gnu

# 增量编译 增量lint 增量link
# 思考如果修改了头文件 如何增量lint
# 如何能知道一个头文件有哪些依赖

# ctest, cpack
# TODO, FIXME
# 项目管理

# doc: doxygen
# pass to ninja

.PHONY: ctags
ctags:
	@ctags -R .

.PHONY: gtags
# TODO(Drogon): first run by gtags -c
gtags:
	@global -u

.PHONY: todo
todo:
	@rg TODO

.PHONY: coverage
coverage: clean
	env -u DISTCC_HOSTS DISABLE_DISTCCD=1 COVERAGE=1 blade test -p debug --bundle debug
	find build64_debug/ ../build64_debug/ -name '*.gcda' | xargs gcov -m -n -r

.PHONY: clean
clean:
	@cmake --build $(BUILD_DIR) --target clean
	# blade clean . -p debug || blade clean || echo "done"
	# find build64_debug/ ../build64_debug/ -name '*.gcda' | xargs rm -f
