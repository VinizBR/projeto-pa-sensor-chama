# Protocolo de Comunicação UDP — Sensor de Chama

## Objetivo

Transmitir as leituras digitais de um sensor de chama conectado
à STM32MP1 para um servidor UDP executado em Linux.

## Configuração

- Transporte: UDP sobre IPv4
- Porta de destino: 5000
- Intervalo de transmissão: 200 ms
- Codificação: ASCII
- Sentido: STM32MP1 → Servidor
- Confirmação de recebimento: não implementada

## Formato da mensagem

Cada datagrama contém uma mensagem no formato:

CHAMA;1;SEQUENCIA;NIVEL

Os campos são separados por ponto e vírgula.

| Campo | Descrição |
|---|---|
| CHAMA | Identificador do sensor |
| 1 | Versão do protocolo |
| SEQUENCIA | Contador incremental de mensagens |
| NIVEL | Leitura digital do sensor |

## Valores do sensor

- 0: chama detectada
- 1: nenhuma chama detectada

## Exemplos

CHAMA;1;42;1

Indica que a mensagem 42 informa ausência de chama.

CHAMA;1;43;0

Indica que a mensagem 43 informa presença de chama.

## Funcionamento

1. A STM32MP1 realiza a leitura digital do sensor.
2. O programa constrói a mensagem conforme o protocolo.
3. A mensagem é transmitida via UDP ao servidor.
4. O servidor recebe o datagrama e apresenta seu conteúdo.

O processo se repete a cada 200 milissegundos.

## Limitações

O UDP não garante entrega, ordem ou ausência de duplicação.
O campo SEQUENCIA permite identificar lacunas e alterações
de ordem durante a análise das mensagens.

A implementação atual não utiliza confirmação de recebimento,
retransmissão ou autenticação.
