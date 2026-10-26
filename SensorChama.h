
#ifndef SENSOR_CHAMA_H
#define SENSOR_CHAMA_H

#include <string>

/**
 * @file SensorChama.h
 * @brief Declaracao da classe de leitura do sensor de chama.
 */

/**
 * @class SensorChama
 * @brief Le o valor bruto de uma entrada do subsistema IIO do Linux.
 *
 * O valor lido e uma amostra bruta do ADC.
 * A interpretacao como deteccao de chama exige validacao
 * do canal utilizado e do comportamento do sensor.
 */
class SensorChama {
private:
    std::string caminhoLeitura;

public:
    /**
     * @brief Constroi o leitor do sensor.
     * @param caminho Caminho do arquivo IIO que sera lido.
     */
    explicit SensorChama(
        const std::string& caminho =
        "/sys/bus/iio/devices/iio:device1/in_voltage2_raw"
    );

    /**
     * @brief Le o valor bruto disponibilizado pelo Linux.
     * @param valor Variavel que recebera o valor lido.
     * @return true se a leitura funcionar; false em caso de erro.
     */
    bool lerValorBruto(int& valor) const;
};

#endif
