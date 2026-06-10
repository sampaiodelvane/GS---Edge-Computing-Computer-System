================================================================================
PROJETO TERRAVIS - MONITORAMENTO DE RISCO DE INCÊNDIO
================================================================================

1. DESCRIÇÃO DO PROJETO
--------------------------------------------------------------------------------
O TerraVis é um sistema de monitoramento ambiental baseado em Edge Computing, 
projetado para detectar condições propícias a incêndios florestais ou urbanos. 
O sistema utiliza um modelo matemático exponencial para calcular o risco de 
queimada em tempo real, fornecendo alertas visuais (LEDs), sonoros (Buzzer) 
e informativos (LCD I2C).

2. OBJETIVO DA SOLUÇÃO
--------------------------------------------------------------------------------
O objetivo principal é oferecer uma ferramenta de detecção precoce que correlaciona 
a temperatura ambiente com o risco estatístico de incêndio. Além disso, a solução 
permite a detecção direta de focos de incêndio ou presença de fumaça através de 
sensores analógicos, garantindo uma resposta imediata em situações de emergência.

3. COMPONENTES UTILIZADOS
--------------------------------------------------------------------------------
- 01 Arduino Uno R3
- 01 Display LCD 16x2 com Interface I2C
- 01 LED Vermelho (Risco Alto/Crítico ou Emergência)
- 01 LED Amarelo (Risco Médio)
- 01 LED Verde (Risco Baixo)
- 03 Resistores de 220 Ohms (para os LEDs)
- 01 Buzzer Ativo (Alerta sonoro)
- 02 Potenciômetros (Simulando Sensores de Fogo e Fumaça)
- Simulador de Temperatura dinâmico (-5°C a 50°C via software)

4. EXPLICAÇÃO DO FUNCIONAMENTO
--------------------------------------------------------------------------------
O sistema opera em um loop contínuo de monitoramento:

A) CÁLCULO DE RISCO: 
A temperatura varia dinamicamente entre -5°C e 50°C. O risco é calculado pela 
fórmula exponencial: Risco = e^(0.15 * (Temperatura - 25)).

B) CLASSIFICAÇÃO DE NÍVEIS:
- BAIXO: Temperatura <= 30°C (LED Verde aceso).
- MÉDIO: Temperatura entre 30.1°C e 35°C (LED Amarelo aceso + Alerta sonoro suave).
- ALTO: Temperatura entre 35.1°C e 40°C (LED Vermelho aceso + Alerta sonoro médio).
- CRÍTICO: Temperatura > 40°C (LED Vermelho aceso + Alerta sonoro persistente).

C) SENSORES DE EMERGÊNCIA:
Se os potenciômetros de Fogo ou Fumaça forem acionados (> 600), o sistema entra 
em modo de EMERGÊNCIA, priorizando o alerta no LCD e ativando o LED vermelho e 
o buzzer com frequência máxima.

5. ESTRUTURA DO CIRCUITO
--------------------------------------------------------------------------------
- LCD I2C: SDA -> A4 | SCL -> A5 | VCC -> 5V | GND -> GND
- LED VERMELHO: Pino Digital 8
- LED AMARELO: Pino Digital 9
- LED VERDE: Pino Digital 10
- BUZZER: Pino Digital 11
- SENSOR FOGO (Pot 1): Pino Analógico A0
- SENSOR FUMAÇA (Pot 2): Pino Analógico A1

6. INSTRUÇÕES DE EXECUÇÃO
--------------------------------------------------------------------------------
1. Acesse o projeto no Wokwi: https://wokwi.com/projects/466311298267433985
2. Certifique-se de que o arquivo "sketch.ino" contém o código C++ fornecido.
3. No "Library Manager" do Wokwi, verifique se a biblioteca "LiquidCrystal I2C" 
   está instalada.
4. Clique no botão "Play" (Iniciar Simulação).
5. Observe a temperatura variando no LCD e os LEDs alternando conforme os níveis.
6. Gire os potenciômetros no simulador para testar os alertas de EMERGÊNCIA.

--------------------------------------------------------------------------------
Desenvolvido para: Edge Computing & Computer Systems - Global Solution
Versão: 1.0
--------------------------------------------------------------------------------
