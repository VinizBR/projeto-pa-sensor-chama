
#include "SensorChama.h"
#include <fstream>

/**
 * @brief Inicializa o caminho do arquivo de leitura.
 * @param caminho Caminho do arquivo IIO.
 */
SensorChama::SensorChama(const std::string& caminho)
    : caminhoLeitura(caminho) {
}

/**
 * @brief Le o valor bruto do canal configurado.
 * @param valor Referencia onde o resultado sera armazenado.
 * @return true se o arquivo puder ser lido corretamente.
 */
bool SensorChama::lerValorBruto(int& valor) const {
    std::ifstream arquivo(caminhoLeitura);

    if (!arquivo.is_open()) {
        return false;
    }

    int leitura;

    if (!(arquivo >> leitura)) {
        return false;
    }

    valor = leitura;
    return true;
}
