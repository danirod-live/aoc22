default:
	@echo "Please use make 01, make 02..."

01: 01.cpp 01.txt
	g++ -o 01 01.cpp

02: 02.cpp 02.txt
	g++ -o 02 02.cpp
