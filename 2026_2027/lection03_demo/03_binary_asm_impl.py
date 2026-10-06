from random import random
import numpy as np
import time

import cpp_mult_asm

# Возьмём NumPy-ные массивы для хранения данных.
# Все операции выполняются "руками".
# Но теперь они написаны с использованием C++ + asm.

N = 400

if __name__ == '__main__':
    a = np.random.rand(N, N)
    b = np.random.rand(N, N)
    c = np.zeros((N, N))

    start_time = time.time()
    cpp_mult_asm.mult(c, a, b)
    elapsed_time = time.time() - start_time

    print("C++ + asm:", elapsed_time)
