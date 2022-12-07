default:
	@echo "Please use make 01, make 02..."

01: 01.cpp 01.txt
	g++ -o 01 01.cpp

02: 02.cpp 02.txt
	g++ -o 02 02.cpp

03: 03.cpp 03.txt
	g++ -o 03 03.cpp

04: 04.cpp 04.txt
	g++ -o 04 04.cpp

05: 05.cpp 05.txt
	g++ -o 05 05.cpp

06: 06.cpp 06.txt
	g++ -o 06 06.cpp

07: 07.cpp 07.txt
	g++ -o 07 07.cpp
