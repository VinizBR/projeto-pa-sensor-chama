
#include "SensorChama.h"
#include <iostream>
#include <chrono>
#include <thread>

/**
 * @file main.cpp
 * @brief Programa de teste da classe SensorChama.
 */

int main() {
    SensorChama sensor;

    for (int i = 0; i < 20; ++i) {
        int valor = 0;

        if (sensor.lerValorBruto(valor)) {
            std::cout << "Leitura bruta: "
                      << valor << std::endl;
        } else {
            std::cerr << "Erro ao ler o canal IIO."
                      << std::endl;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }

    return 0;
}
