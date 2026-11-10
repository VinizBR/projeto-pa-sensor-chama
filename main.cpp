#include "SensorChama.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <exception>
#include <string>

// Bibliotecas para comunicacao UDP
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Uso: " << argv[0]
                  << " <IP_SERVIDOR>\n";
        return 1;
    }

    try {
        SensorChama sensor;

        // Cria socket UDP
        int udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (udp < 0) {
            std::cerr << "Erro ao criar socket UDP.\n";
            return 1;
        }

        // Configura o destino
        sockaddr_in destino{};
        destino.sin_family = AF_INET;
        destino.sin_port = htons(5000);

        if (inet_pton(AF_INET, argv[1],
                      &destino.sin_addr) != 1) {
            std::cerr << "Endereco IP invalido.\n";
            close(udp);
            return 1;
        }

        int estadoAnterior = -1;
        unsigned long sequencia = 0;

        std::cout << "Monitoramento iniciado.\n";
        std::cout << "Enviando UDP para "
                  << argv[1] << ":5000\n";

        while (true) {
            int nivel;

            if (!sensor.lerNivel(nivel)) {
                std::cerr << "Erro ao ler o sensor.\n";
                close(udp);
                return 1;
            }

            // Mantem a deteccao de chama da Entrega 2
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

            // Monta mensagem do protocolo
            std::string mensagem =
                "CHAMA;1;" +
                std::to_string(sequencia++) + ";" +
                std::to_string(nivel);

            // Envia datagrama UDP
            ssize_t enviados = sendto(
                udp,
                mensagem.data(),
                mensagem.size(),
                0,
                reinterpret_cast<sockaddr*>(&destino),
                sizeof(destino)
            );

            if (enviados !=
                static_cast<ssize_t>(mensagem.size())) {
                std::cerr << "Falha no envio UDP.\n";
            }

            std::this_thread::sleep_for(
                std::chrono::milliseconds(200)
            );
        }

        close(udp);

    } catch (const std::exception& erro) {
        std::cerr << erro.what() << std::endl;
        return 1;
    }

    return 0;
}
