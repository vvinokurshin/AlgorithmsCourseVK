/*
Инвертируйте значение бита в числе N по его номеру K.
Формат входных данных. Число N, номер бита K.
Формат выходных данных. Число с инвертированным битом в десятичном виде.
*/

#include <iostream>

void InvertBit(std::istream &input, std::ostream &output) {
    unsigned int num, k;

    input >> num;
    input >> k;

    num ^= (1u << k);

    output << num << std::endl;
}

int main(void) {
    InvertBit(std::cin, std::cout);
    return 0;
}