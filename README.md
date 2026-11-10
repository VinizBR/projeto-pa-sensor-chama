# Projeto de Programação Aplicada
## Sistema de Detecção de Chama — STM32MP1

### 1. Objetivo

Desenvolver uma aplicação em C++ para monitoramento de um sensor
de chama utilizando Linux embarcado na placa STM32MP157C-DK2.

O programa realiza a leitura digital do sensor através de um GPIO
e identifica mudanças no estado de detecção de chama.

### 2. Hardware utilizado

- Placa STM32MP157C-DK2
- Sensor de chama com saída digital (DO)
- Cabos de conexão
- Computador com Ubuntu para compilação cruzada

### 3. Conexões

| Sensor | STM32MP1 |
|--------|----------|
| VCC    | 3,3 V    |
| GND    | GND      |
| DO     | D2 (PE1) |

O pino D2 corresponde ao GPIO PE1 da STM32MP1.

Na configuração Linux utilizada:

- Controlador: `/dev/gpiochip4`
- Linha GPIO: `1`
- Direção: entrada digital

A numeração dos dispositivos GPIO pode variar conforme
a configuração do sistema operacional.

### 4. Funcionamento

O sensor apresenta uma saída digital com dois estados:

- `0`: chama detectada
- `1`: nenhuma chama detectada

Esses estados foram confirmados experimentalmente.

A aplicação monitora continuamente o sensor, realizando
leituras a cada 200 milissegundos.

As mensagens são exibidas somente quando ocorre uma
mudança no estado de detecção.

Exemplo de execução:

    Monitoramento iniciado.
    [INFO] Nenhuma chama detectada.
    [ALERTA] CHAMA DETECTADA!
    [INFO] Nenhuma chama detectada.

### 5. Estrutura do projeto

- `SensorChama.h`: declaração e documentação da classe.
- `SensorChama.cpp`: implementação da leitura GPIO.
- `main.cpp`: aplicação de monitoramento contínuo.
- `Doxyfile`: configuração da documentação Doxygen.
- `docs/`: arquivos de documentação do projeto.

### 6. Compilação cruzada

O programa é desenvolvido no Ubuntu e compilado para
a arquitetura ARM Cortex-A7 da STM32MP1.

É necessário possuir um SDK compatível com a placa.

Ativar o SDK utilizado no desenvolvimento:

```bash
source ~/stm32mp1-sdk/environment-setup-cortexa7t2hf-neon-vfpv4-ostl-linux-gnueabi
```

Compilar:

```bash
$CXX -std=c++17 -O2 -Wall -Wextra -pthread main.cpp SensorChama.cpp -o sensor_chama
```

O executável gerado é destinado à arquitetura ARM.

### 7. Transferência para a STM32MP1

Com a placa conectada à rede e o SSH habilitado:

```bash
scp -O sensor_chama root@192.168.42.2:/root/
```

O endereço IP apresentado corresponde à configuração
utilizada durante os testes e pode ser diferente em
outras instalações.

### 8. Execução

Acessar a STM32MP1:

```bash
ssh root@192.168.42.2
```

Executar:

```bash
/root/sensor_chama
```

O programa permanece em execução até ser interrompido
com `Ctrl+C`.

### 9. Implementação

A aplicação utiliza a interface GPIO Character Device v2
do kernel Linux.

A comunicação com o GPIO é realizada através de chamadas
`ioctl()`, utilizando a interface disponibilizada em
`linux/gpio.h`.

Essa abordagem permite a leitura do sensor sem depender
diretamente da biblioteca libgpiod.

### 10. Documentação Doxygen

A classe `SensorChama` possui documentação de seus
atributos, métodos e valores de retorno.

Para gerar a documentação:

```bash
doxygen Doxyfile
```

### 11. Testes realizados

O programa foi compilado cruzadamente no Ubuntu e
executado na STM32MP1 com Linux embarcado.

Os testes confirmaram:

- Comunicação funcional com o GPIO PE1.
- Detecção da presença de chama.
- Identificação da ausência de chama.
- Monitoramento contínuo.
- Exibição de mensagens quando o estado é alterado.

### 12. Limitações

O sensor fornece apenas uma saída digital, não permitindo
obter diretamente valores contínuos de intensidade luminosa.

A detecção depende da sensibilidade do módulo e das
condições do ambiente.

O projeto possui finalidade acadêmica e não substitui
sistemas certificados de detecção e prevenção de incêndios.

## Entrega 3 — Comunicação UDP

O projeto permite transmitir as leituras do sensor de chama
da STM32MP1 para um servidor UDP executado no Ubuntu.

### Arquivos

- `SensorChama.h`: interface da classe do sensor.
- `SensorChama.cpp`: implementação da leitura GPIO.
- `main.cpp`: monitoramento e transmissão UDP.
- `servidor_udp.cpp`: servidor receptor UDP.
- `PROTOCOLO_UDP.md`: especificação do protocolo.

### Topologia utilizada nos testes

- STM32MP1: 192.168.42.2
- Servidor Ubuntu: 192.168.42.10
- Porta UDP: 5000

Os endereços são exemplos da rede utilizada nos testes.

### Compilação do servidor no Ubuntu

```bash
g++ -std=c++17 -O2 -Wall -Wextra servidor_udp.cpp -o servidor_udp
