# Projeto IoT – Medição de Temperatura em Leitos Hospitalares

Autora: Giovanna Teixeira da França

Orientação: Leandro Carlos Fernandes

Instituição: Universidade Presbiteriana Mackenzie – UPM

## 1. Descrição do Projeto

Este repositório contém um protótipo IoT desenvolvido para monitorar temperatura e umidade em leitos hospitalares, garantindo maior segurança e conforto ao paciente.
O sistema utiliza:

ESP32

Sensor DHT22

Display LCD 16×2 I2C

Relé + Ventilador (simulado)

MQTT (Mosquitto)

Node-RED Dashboard

O objetivo é manter a temperatura ambiente entre 20°C e 24°C, acionando automaticamente o ventilador quando a temperatura ultrapassa 25°C.

Este projeto cumpre os requisitos da disciplina, incluindo documentação de hardware, software e comunicação via TCP/IP + MQTT.

## 2. Funcionamento do sistema

O ESP32 lê temperatura e umidade usando o DHT22.

Os dados são enviados via MQTT para o broker público Mosquitto.

O Node-RED recebe esses valores, exibe no dashboard e monitora a segurança.

Quando a temperatura ultrapassa 25°C, o ESP32 liga automaticamente o ventilador.

Quando retorna para ≤ 24°C, o ventilador desliga automaticamente.

O Node-RED também permite comandar ON/OFF manualmente pelo dashboard.

## 3. Como Reproduzir o Projeto

No repositório está contido todos os códigos de implementação utilizados.
Permitindo que o projeto possa ser reproduzido por outras pessoas.

#### Sendo necessário:
Node-RED instalado

Acesso ao Wokwi

Acesso ao broker público: test.mosquitto.org:1883

## 4. Hardware Utilizado
#### ESP32

Motivo da escolha:

Wi-FI integrado

Compatível com MQTT sem módulos extras

Suporte excelente em simulações do Wokwi

#### Sensor DHT22

Precisão elevada

Ideal para ambientes hospitalares

Mede temperatura (±0.5°C) e umidade (±2%)

#### LCD 16×2 I2C

Exibe temperatura e umidade

Comunicação I2C (2 fios apenas)

#### Módulo Relé + Ventilador

O relé aciona o ventilador quando a temperatura supera 25°C

No Wokwi não há ventoinha, então foi usado um motor DC simulado

## 5. Protocolos, Interfaces e Comunicação
#### MQTT – Protocolo principal

O projeto utiliza o broker:

Broker: test.mosquitto.org
Porta: 1883

#### Node-RED - Visualização e controle do protótipo
O Node-RED interpreta os valores e envia ON/OFF via MQTT.

## 6. Resultados

O protótipo funcionou corretamente no Wokwi.

O Node-RED exibiu temperatura e status do ventilador em tempo real.

O ventilador simulou com sucesso o resfriamento automático do leito hospitalar.

O sistema atendeu aos limites de 20°C–24°C como solicitado.

### Vídeo de demonstração

👉 https://youtu.be/F-PHNVCLOu4

## 7. Conclusões

O projeto atingiu seus objetivos, comprovando:

funcionamento do sensor

envio correto dos dados

controle automático via atuador

integração total via MQTT

visualização via Node-RED

Apesar de limitações de simulação, o sistema é totalmente aplicável a um leito hospitalar real, bastando substituir o ventilador simulado por um equipamento real e realizar ajustes de execução.

<img width="674" height="585" alt="ModeloMontagem" src="https://github.com/user-attachments/assets/8ea40994-b3f0-45e3-860d-bcf20732d6db" />

