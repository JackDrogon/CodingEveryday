
BUILD_DIR ?= _build

.PHONY: ci lint format update release debug test coverage clean

.PHONY: build
build:
	@cmake -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Release . 
	@cmake --build $(BUILD_DIR) --config Release -- -j$(nproc -c)

ci: update lint test

lint:
	git ls-files | egrep '.*\.(h|cc)' | xargs python dev-tools/cpplint.py
	git ls-files | egrep '.*\.(h|cc)' | xargs python3 dev-tools/check-style.py

format:
	git ls-files | egrep '.*\.(h|cc)' | xargs clang-format -style=file -i

update:
	blade build --update-deps -p debug --bundle debug

release:
	blade build --update-deps -p release

debug:
	blade build -p debug --bundle debug

# dep build, ignore it for build dummy output
test:
	@ctest --test-dir $(BUILD_DIR)

# force-test: build
# 	@ctest --test-dir $(BUILD_DIR)


# format
# cpplint, clang, gcc
# cppcheck flint
# clang-tidy, clang-analyzer
# cover
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
# TODO
# 项目管理

# doc: doxygen
# pass to ninja

ctags:
	@ctags -R .

gtags:
	@global -u

coverage: clean
	env -u DISTCC_HOSTS DISABLE_DISTCCD=1 COVERAGE=1 blade test -p debug --bundle debug
	find build64_debug/ ../build64_debug/ -name '*.gcda' | xargs gcov -m -n -r

clean:
	@cmake --build $(BUILD_DIR) --target clean
	# blade clean . -p debug || blade clean || echo "done"
	# find build64_debug/ ../build64_debug/ -name '*.gcda' | xargs rm -f
