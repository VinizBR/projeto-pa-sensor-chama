#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // 1. Criar socket UDP
    int servidor = socket(AF_INET, SOCK_DGRAM, 0);

    if (servidor < 0) {
        std::cerr << "Erro ao criar socket.\n";
        return 1;
    }

    // 2. Configurar endereco do servidor
    sockaddr_in endereco{};
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(5000);
    endereco.sin_addr.s_addr = INADDR_ANY;

    // 3. Associar socket a porta 5000
    if (bind(servidor,
             reinterpret_cast<sockaddr*>(&endereco),
             sizeof(endereco)) < 0) {

        std::cerr << "Erro ao executar bind.\n";
        close(servidor);
        return 1;
    }

    std::cout << "Servidor UDP iniciado na porta 5000.\n";
    std::cout << "Aguardando dados da STM32...\n";

    // 4. Receber mensagens continuamente
    while (true) {
        char buffer[256] = {};

        sockaddr_in cliente{};
        socklen_t tamanhoCliente = sizeof(cliente);

        ssize_t bytes = recvfrom(
            servidor,
            buffer,
            sizeof(buffer) - 1,
            0,
            reinterpret_cast<sockaddr*>(&cliente),
            &tamanhoCliente
        );

        if (bytes < 0) {
            std::cerr << "Erro ao receber dados.\n";
            continue;
        }

        buffer[bytes] = '\0';

        std::cout << "[UDP] "
                  << inet_ntoa(cliente.sin_addr)
                  << " -> "
                  << buffer
                  << std::endl;
    }

    close(servidor);
    return 0;
}
