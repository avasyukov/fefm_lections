#include <iostream>

// Внимание! Не надо так писать!
// Делать include на .cpp - плохая идея.
// Но мы ещё не разбирали, как надо.
// Поэтому пока что будет так.
#include "utils.cpp"

#define MY_VALUE 10

int main() {
    // Здесь сознательно забыта точка с запятой в конце строки
    int x = 5
    int result = add(MY_VALUE, x);
    std::cout << "Result: " << result << std::endl;
    return 0;
}