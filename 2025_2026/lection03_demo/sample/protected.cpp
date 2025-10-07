#include <iostream>
#include <fstream>

#define PATH "/tmp/password"

void do_great_work() {
}

int main() {
    std::string user_password;
    std::cout << "Input password:" << std::endl;
    std::cin >> user_password;

    std::string correct_password;
    std::ifstream ifs;
    ifs.open(PATH);
    ifs >> correct_password;
    ifs.close();

    if (user_password == correct_password) {
        std::cout << "Access granted" << std::endl;
        do_great_work();
    } else {
        std::cout << "Access denied" << std::endl;
        return -1;
    }

    return 0;
}