compile:
	clear
	clang++ -g -std=c++17 ./Code/*.cpp -o output
	./output
	python3 Code/data_visualization.py &