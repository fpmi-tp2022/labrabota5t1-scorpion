# Makefile for Lab5 project

autopark: main.o autoparkDB.o autoparkUI.o
	mkdir -p bin
	g++ -o ./bin/autopark obj/main.o obj/autoparkDB.o obj/autoparkUI.o -l sqlite3

main.o: src/main.cpp include/autoparkUI.h include/autoparkDB.h
	mkdir -p obj
	g++ -c src/main.cpp -o obj/main.o 

autoparkDB.o: src/autoparkDB.cpp include/autoparkDB.h
	mkdir -p obj
	g++ -c src/autoparkDB.cpp -o obj/autoparkDB.o 

autoparkUI.o: src/autoparkUI.cpp include/autoparkUI.h
	mkdir -p obj
	g++ -c src/autoparkUI.cpp -o obj/autoparkUI.o 

clean:
	rm -f obj/*.o ./bin/autopark
	rm -f ./bin/autoparkDB_tests

run: 
	./bin/autopark

test:
	mkdir -p bin
	g++ -std=c++11 src/autoparkDB.cpp src/tests/autoparkDB_tests.cpp -l gtest -l gtest_main -pthread -l sqlite3 -o ./bin/autoparkDB_tests
	g++ -std=c++11 src/autoparkUI.cpp src/tests/autoparkUI_tests.cpp -l gtest -l gtest_main -pthread -l sqlite3 -o ./bin/autoparkUI_tests
	./bin/autoparkDB_tests
	./bin/autoparkUI_tests