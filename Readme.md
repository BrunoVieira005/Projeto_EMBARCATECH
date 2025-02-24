# 🔔 Sistema de Alarme com Detecção de Som para Pessoas com Deficiência Auditiva  

Este projeto simula um **sistema de alarme com detecção de som**, utilizando um **Raspberry Pi Pico**, um **display OLED**, **LEDs RGB** e um **buzzer**.  

O objetivo principal é tornar o sistema acessível, combinando **alertas visuais e sonoros** para garantir que pessoas com deficiência auditiva, ou não, possam perceber o alarme.  

---

## 📌 Funcionalidades  

✅ **Monitoramento do sistema:** Exibe o status no display OLED (`"Sistema Ativo"` ou `"Som Detectado!"`).  
✅ **Alertas visuais:** LEDs RGB piscam para indicar o estado do sistema (verde para ativo, vermelho para alarme).  
✅ **Sinal sonoro:** O buzzer emite sinais intermitentes quando o alarme está ativo.  
✅ **Desativação manual:** Um botão permite desligar o alarme e retornar ao estado inicial.  

---

## 🛠️ Componentes Necessários  

- **Microcontrolador:** Raspberry Pi Pico  
- **Display:** OLED 128x64 (I2C)  
- **Saída sonora:** Buzzer  
- **Entradas:** 2 botões  
- **Sinalização visual:** 3 LEDs RGB (verde, azul e vermelho)  
- **Componentes adicionais:**  
  - Resistores (220Ω para LEDs, 1kΩ para transistor do buzzer)  
  - Transistor NPN  
  - Protoboard e jumpers  
  - Fonte de alimentação 5V  

---

## 🚀 Instruções para Testar o Projeto  

### 1️⃣ Conectar o Raspberry Pi Pico ao PC  

1. **Coloque o Raspberry Pi Pico em modo Bootloader:**  
   - Segure o botão **BOOTSEL** no Pico.  
   - Conecte o Pico ao computador via USB.  
   - Solte o botão **BOOTSEL**.  
   - O Pico aparecerá como um **dispositivo de armazenamento**.  

---

### 2️⃣ Configurar o Ambiente de Desenvolvimento  

#### 🔹 Instalar a Extensão do Raspberry Pi Pico  
- Se estiver usando o **Visual Studio Code**, instale a extensão **Raspberry Pi Pico**.  
- Caso use outra IDE, **configure o ambiente** para suportar o Raspberry Pi Pico.  

#### 🔹 Instalar o Zadig (Para Windows)  
1. Baixe e instale o **Zadig** [aqui](https://zadig.akeo.ie/).  
2. Conecte o Pico ao PC e **abra o Zadig**.  
3. Selecione o dispositivo correspondente ao Pico e **instale o driver WinUSB**.  

---

### 3️⃣ Clonar o Repositório  

Abra o terminal e execute os seguintes comandos:  

```bash
git clone https://github.com/seu-usuario/nome-do-repositorio.git
cd nome-do-repositorio
```

---

### 4️⃣ Compilar e Carregar o Código  

1. **Abra o projeto na sua IDE.**  
2. **Compile o código.**  
3. **Carregue o arquivo `.uf2` gerado para o Raspberry Pi Pico:**  
   - Arraste e solte o arquivo `.uf2` para a **unidade do Pico** que apareceu no modo Bootloader.  

---

### 5️⃣ Executar o Projeto  

- Após carregar o código, o Pico **reiniciará automaticamente** e executará o projeto.  
- O display OLED exibirá `"Sistema Ativo"`, e o **LED verde piscará**.  

#### 🎤 **Simulando a detecção de som**  
🔹 Pressione o botão **A** para simular a detecção de som:  
  - O **alarme será ativado**.  
  - O display exibirá **"Som Detectado!"**.  
  - O **LED vermelho piscará**.  
  - O **buzzer emitirá sons intermitentes**.  

#### 🔕 **Desativando o alarme**  
🔹 Pressione o botão **B** para **desligar o alarme** e retornar ao estado inicial.  

---

## 📩 Contato  

Caso tenha dúvidas ou sugestões, entre em contato:  
📧 **brunorv2005@gmail.com**  
🔗 **[GitHub](https://github.com/BrunoVieira005)**  

---
