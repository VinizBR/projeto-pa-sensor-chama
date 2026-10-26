
# Projeto de Programação Aplicada
## Sensor de Chama STM32MP1

### Objetivo
Desenvolver uma classe C++ para leitura de um sensor de chama
utilizando o ambiente Linux embarcado da placa STM32MP1 DK1.

### Arquivos
- `SensorChama.h`: declaração da classe e documentação Doxygen.
- `SensorChama.cpp`: implementação dos métodos de leitura.

### Documentação
Os comentários Doxygen descrevem a finalidade da classe,
seus métodos, parâmetros e valores de retorno.

### Estado atual
A implementação inicial realiza a leitura de um valor bruto
de um arquivo do subsistema IIO do Linux. A correspondência
entre o canal utilizado e a saída do sensor ainda precisa
ser validada experimentalmente.

### Compilação
A aplicação deverá ser compilada para a arquitetura ARM
utilizando a toolchain fornecida para o projeto.
