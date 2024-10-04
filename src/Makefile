ifeq ($(shell uname), Linux)
 CHECKFLAGS = -lm -lpthread -lrt -pthread -lsubunit -lgtest -lgtest_main
else
 CHECKFLAGS = -lm -lpthread -lgtest -lgtest_main
endif

all: test

test: clean
	g++ -Wall -Werror -Wextra -g -std=c++17 tests/test_*.cc $(CHECKFLAGS) -o test
	./test

style_check: 
	clang-format -style=Google -n *.h
	clang-format -style=Google -n tests/*.cc tests/*.h
	clang-format -style=Google -n s21_containers/list/*.h
	clang-format -style=Google -n s21_containers/map/*.h
	clang-format -style=Google -n s21_containers/queue/*.h
	clang-format -style=Google -n s21_containers/set/*.h
	clang-format -style=Google -n s21_containers/stack/*.h
	clang-format -style=Google -n s21_containers/vector/*.h
	clang-format -style=Google -n s21_containersplus/array/*.h
	clang-format -style=Google -n s21_containersplus/multiset/*.h

clang-format:
	clang-format -style=Google -i *.h
	clang-format -style=Google -i tests/*.cc tests/*.h
	clang-format -style=Google -i s21_containers/list/*.h
	clang-format -style=Google -i s21_containers/map/*.h
	clang-format -style=Google -i s21_containers/queue/*.h
	clang-format -style=Google -i s21_containers/set/*.h
	clang-format -style=Google -i s21_containers/stack/*.h
	clang-format -style=Google -i s21_containers/vector/*.h
	clang-format -style=Google -i s21_containersplus/array/*.h
	clang-format -style=Google -i s21_containersplus/multiset/*.h


cppcheck:
	cppcheck --language=c++ --enable=all --suppress=missingIncludeSystem *.h tests/*.cc tests/*.h

clean:
	rm -rf test 
	rm -rf test.dSYM