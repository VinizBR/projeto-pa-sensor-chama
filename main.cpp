#include "SensorChama.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <exception>

int main() {
    try {
        SensorChama sensor;

        int estadoAnterior = -1;

        std::cout << "Monitoramento iniciado.\n";

        while (true) {
            int nivel;

            if (!sensor.lerNivel(nivel)) {
                std::cerr << "Erro ao ler o sensor.\n";
                return 1;
            }

            if (nivel != estadoAnterior) {

                if (nivel == 0) {
                    std::cout << "[ALERTA] CHAMA DETECTADA!"
                              << std::endl;
                } else {
                    std::cout << "[INFO] Nenhuma chama detectada."
                              << std::endl;
                }

                estadoAnterior = nivel;
            }

            std::this_thread::sleep_for(
                std::chrono::milliseconds(200)
            );
        }

    } catch (const std::exception& erro) {
        std::cerr << erro.what() << std::endl;
        return 1;
    }

    return 0;
}
