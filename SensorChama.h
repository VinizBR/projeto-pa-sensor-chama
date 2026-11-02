#ifndef SENSORCHAMA_H
#define SENSORCHAMA_H

/**
 * @file SensorChama.h
 * @brief Declaracao da classe responsavel pela leitura
 * digital de um sensor de chama.
 */

/**
 * @class SensorChama
 * @brief Interface C++ para um sensor de chama digital.
 *
 * @details
 * A classe realiza a comunicacao com o GPIO PE1 da
 * STM32MP1 atraves da interface GPIO do kernel Linux.
 *
 * O sensor apresenta nivel logico baixo (0) quando
 * detecta uma chama e nivel alto (1) quando nao detecta.
 */
class SensorChama {

private:

    /**
     * @brief Descritor da linha GPIO solicitada ao kernel.
     */
    int fdLinha;

public:

    /**
     * @brief Construtor da classe SensorChama.
     *
     * Abre o controlador GPIOE e configura a linha PE1
     * como entrada digital.
     *
     * @throws std::runtime_error Caso nao seja possivel
     * abrir ou configurar o GPIO.
     */
    SensorChama();

    /**
     * @brief Destrutor da classe.
     *
     * Libera o descritor da linha GPIO.
     */
    ~SensorChama();

    /**
     * @brief Realiza a leitura do nivel logico do sensor.
     *
     * @param[out] nivel Variavel que recebe o valor
     * digital lido (0 ou 1).
     *
     * @return true Caso a leitura seja realizada
     * com sucesso.
     *
     * @return false Caso ocorra um erro na leitura.
     */
    bool lerNivel(int& nivel) const;

    /**
     * @brief Impede a copia do objeto.
     *
     * Evita que dois objetos tentem gerenciar
     * o mesmo descritor GPIO.
     */
    SensorChama(const SensorChama&) = delete;

    /**
     * @brief Impede a atribuicao por copia.
     */
    SensorChama& operator=(const SensorChama&) = delete;
};

#endif
