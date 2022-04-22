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

run: 
	./bin/autopark

