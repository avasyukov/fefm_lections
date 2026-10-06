all:
	g++ -O2 -Wall -Werror -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` -I . cpp_mult_asm.cpp asm_mult.S -o cpp_mult_asm`python3-config --extension-suffix`
clean:
	rm *.so
