.PHONY: ci lint format update release debug test coverage clean

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

test:
	blade test -p debug --bundle debug

coverage: clean
	env -u DISTCC_HOSTS DISABLE_DISTCCD=1 COVERAGE=1 blade test -p debug --bundle debug
	find build64_debug/ ../build64_debug/ -name '*.gcda' | xargs gcov -m -n -r

clean:
	blade clean . -p debug || blade clean || echo "done"
	find build64_debug/ ../build64_debug/ -name '*.gcda' | xargs rm -f
