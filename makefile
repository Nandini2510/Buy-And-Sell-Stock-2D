# output: Stocks1.o Stocks2.o Stocks3a.o Stocks3b.o Stocks4.o Stocks5.o Stocks6a.o Stocks6b.o
# 	g++ Stocks1.o Stocks2.o Stocks3a.o Stocks3b.o Stocks4.o Stocks5.o Stocks6a.o Stocks6b.o -o output

# Stocks1.o: Stocks1.cpp
# 	g++ -c Stocks1.cpp
# Stocks2.o: Stocks2.cpp
# 	g++ -c Stocks2.cpp
# Stocks3a.o: Stocks3a.cpp
# 	g++ -c Stocks3a.cpp
# Stocks3b.o: Stocks3b.cpp
# 	g++ -c Stocks3b.cpp
# Stocks4.o: Stocks4.cpp
# 	g++ -c Stocks4.cpp
# Stocks5.o: Stocks5.cpp
# 	g++ -c Stocks5.cpp
# Stocks6a.o: Stocks6a.cpp
# 	g++ -c Stocks6a.cpp
# Stocks5.o: Stocks5.cpp
# 	g++ -c Stocks5.cpp
# Stocks6a.o: Stocks6a.cpp
# 	g++ -c Stocks6a.cpp
# Stocks6b.o: Stocks6b.cpp
# 	g++ -c Stocks6b.cpp


output: Stocks.o 
	g++ Stocks.o -o Stocks
Stocks.o: Stocks.cpp
	g++ -c Stocks.cpp 

clean: 
	rm *.o Stocks