#берем все файлы с расширением .c
FUNC = $(wildcard ./functions/*.c) 
#преобразуем их в объектные файлы
OBJ = $(patsubst ./functions/%.c, ./objects/%.o, $(FUNC))

#берем все файлы с расширением .c
TEST = $(wildcard ./tests/*.c) 
#преобразуем их в объeктные файлы
OBJ_TEST = $(patsubst ./tests/%.c, ./tests_objects/%.o, $(TEST))

GCOV_DIR = ./gcov_report
GCOV_OBJ_DIR = $(GCOV_DIR)/gcov_objects
GCOV_OBJ = $(addprefix $(GCOV_OBJ_DIR)/, $(notdir $(FUNC:.c=.o)))

UNAME_S = $(shell uname -s)

#нужно для линковки библиотеки и тестов
# для MAC OS
ifeq ($(UNAME_S),Darwin) 
	TEST_LIBS = -lcheck -lm 
endif

# для LINUX
ifeq ($(UNAME_S),Linux)
	TEST_LIBS = -lcheck -lm -lsubunit
endif

#флаги для компиляции 
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Wpedantic -I. 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -g -O0

all: s21_matrix.a test

#создание статической библиотеки s21_matrix.a (архив объектных файлов)
s21_matrix.a: $(OBJ)
	ar rcs s21_matrix.a $(OBJ)
	ranlib s21_matrix.a

#компилируем необходимые объектные файлы для библиотеки 
./objects/%.o : ./functions/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#линковка объектных тестовых файлов и нашей библиотеки в исполняемый файл с тестами
test: $(OBJ_TEST) s21_matrix.a
	$(CC) $(OBJ_TEST) $(TEST_LIBS) -L. s21_matrix.a -o test.out
	./test.out

#компилируем необходимые объектные файлы для test_s21_matrix.h
./tests_objects/%.o : ./tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

gcov_report: $(GCOV_OBJ) $(OBJ_TEST)
	$(CC) $(GCOV_FLAGS) $(GCOV_OBJ) $(OBJ_TEST)  \
		-o $(GCOV_DIR)/test_coverage $(TEST_LIBS)
	./$(GCOV_DIR)/test_coverage;
	gcov $(GCOV_OBJ_DIR)/*.gcno;
	@mv *.gcov $(GCOV_OBJ_DIR);
	lcov -c -t "s21_matrix" -o $(GCOV_DIR)/report.info -d $(GCOV_OBJ_DIR) \
		--rc lcov_branch_coverage=1;
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/report.info --rc lcov_branch_coverage=1

$(GCOV_OBJ_DIR)/%.o: ./functions/%.c 
	mkdir -p $(GCOV_OBJ_DIR)
	$(CC) $(CFLAGS) $(GCOV_FLAGS)  -c $< -o $@

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./*/*.o ./*/*.a ./*/*.gcno ./*/*.gcda ./*/*.info ./*/*.out ./*/*.gcov
	rm -rf ./gcov_report

format:
	-mv ../materials/linters/.clang-format ./
	clang-format -n ./*/*.c ./*/*.h ./*.h
	clang-format -i ./*/*.c ./*/*.h ./*.h
	clang-format -n ./*/*.c ./*/*.h ./*.h
	-mv ./.clang-format ../materials/linters/

rebuild: clean all

.PHONY: all test gcov_report
