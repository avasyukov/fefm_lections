#include <torch/torch.h>
#include <torch/script.h>
#include <torch/cuda.h>

#include <chrono>
#include <iostream>

#define SIZE 1024

int main()
{
    const bool cuda_is_available = torch::cuda::is_available();
    torch::DeviceType device = cuda_is_available ? torch::kCUDA : torch::kCPU;

    std::string device_name = cuda_is_available ? "CUDA" : "CPU";
    std::cout << "Running on " << device_name << std::endl;
    std::cout << "Building grads: " << std::boolalpha << torch::GradMode::is_enabled() << std::endl;

    torch::Tensor a = torch::rand({SIZE, SIZE}).to(device);
    torch::Tensor b = torch::rand({SIZE, SIZE}).to(device);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    torch::Tensor c = a.matmul(b);
    std::cout << c.pow(2).sum().sqrt() << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " µs" << std::endl;

    return 0;
}