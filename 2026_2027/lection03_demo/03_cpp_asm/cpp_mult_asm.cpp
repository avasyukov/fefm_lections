#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>

namespace py = pybind11;

// The matrix multiply is implemented in asm_mult.S (x86-64 assembly).
// "extern "C"" gives it plain C linkage, so the symbol the linker sees
// is exactly "asm_mult" -- no C++ name mangling.
//
// The assembly receives the raw double* pointers the same way any C
// function would, per the System V AMD64 calling convention:
// rdi = c, rsi = a, rdx = b, rcx = n (the size).
extern "C" void asm_mult(double* c, const double* a, const double* b,
                         unsigned long n);

void mult(py::array_t<double>& _c, py::array_t<double>& _a, py::array_t<double>& _b) {

    py::buffer_info buf_a = _a.request();
    py::buffer_info buf_b = _b.request();
    py::buffer_info buf_c = _c.request();

    double* a = (double*)buf_a.ptr;
    double* b = (double*)buf_b.ptr;
    double* c = (double*)buf_c.ptr;

    unsigned long size = buf_a.shape[0];

    std::cout << "Matrix size: " << size << std::endl;

    // The triple loop that used to live here now lives in assembly.
    // The whole chain is: Python (numpy) -> C++ (pybind11) -> asm_mult.
    asm_mult(c, a, b, size);
};


PYBIND11_MODULE(cpp_mult_asm, m) {
    m.def("mult", &mult, "A function that multiplies two matrices (core loop in hand-written assembly)");
}
