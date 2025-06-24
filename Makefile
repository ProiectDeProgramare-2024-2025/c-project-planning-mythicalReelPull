all:
	g++ -std=c++17 main.cpp cli.cpp cart.cpp fileio.cpp -o foodapp.exe

clean:
	del foodapp.exe