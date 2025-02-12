# 🎮 Controle de Servo Motor com Raspberry Pi Pico  

Projeto para controle de um servo motor usando sinais PWM. O servo se move entre posições pré-definidas (0°, 90°, 180°) e realiza um movimento contínuo suave.  

---

## 🔧 **Hardware**  
- **Microcontrolador**: Raspberry Pi Pico W  
- **Componentes Principais**:  
  - Servo Motor  
- **Conexões**:  
  - Cabo Micro-USB  
  - Jumpers  

### 📍 **Mapeamento de Pinos**  
```  
Sinal do Servo -> GPIO 22  
VCC do Servo   -> 5V do Pico  
GND do Servo   -> GND do Pico  
```  

---

## 💻 **Software Necessário**  
- **SDK**: Raspberry Pi Pico SDK (v2.1.0)  
- **Ferramentas**: CMake (v3.13+), VS Code  
- **Compilador**: GCC para ARM  
- **Controle de Versão**: Git  

---

## 📁 **Estrutura do Projeto**  
```  
.  
├── .vscode/          # Configurações da IDE  
├── build/            # Diretório de compilação  
├── Controle_servo_PWM.c  # Código principal (lógica PWM)     
├── diagram.json      # Diagrama de simulação no Wokwi  
├── wokwi.toml        # Configuração da simulação no Wokwi  
├── CMakeLists.txt    # Configuração de build  
├── pico_sdk_import.cmake  
└── README.md  
```  

---

## ⚡ **Como Executar**  

### **Clone o Repositório**  
```bash  
git clone https://github.com/seu-usuario/hello_pwm.git  
cd hello_pwm  
```  

### **Compilação (Hardware Físico)**  
```bash  
mkdir build  
cd build  
cmake ..  
make  
```  

### **Gravação no Pico**  
1. Pressione o botão **BOOTSEL** no Pico e conecte-o ao computador.  
2. Copie o arquivo `hello_pwm.uf2` (gerado em `build/`) para a unidade do Pico.  

### **Simulação no Wokwi**  
1. Acesse [Wokwi](https://wokwi.com/) e importe os arquivos `diagram.json` e `wokwi.toml`.  
2. Execute a simulação para testar o comportamento do servo virtualmente.  

---

## 🚀 **Funcionalidades**  
- Movimento para posições fixas (0°, 90°, 180°) com intervalo de 5 segundos.  
- Varredura contínua suave entre 0° e 180° após as posições fixas.  
- Parâmetros PWM ajustáveis (período, largura de pulso).  

---

## 📊 **Arquitetura do Código**  
1. **Controle_servo_PWM.c**:  
   - **Inicialização**: Configura o PWM no GPIO 22 (`pwm_set_clkdiv`, `pwm_set_wrap`).  
   - **Posições Fixas**: Define pulsos para 0° (500µs), 90° (1470µs) e 180° (2400µs).  
   - **Loop Contínuo**: Incrementa/decrementa o pulso para movimento suave (`PASSO_US`).  

---

## 🐛 **Depuração**  
- **Conexões**: Verifique se o sinal do servo está no GPIO 22.  
- **Serial**: Adicione `printf` para debug (requer configuração UART).  
- **Simulação**: Use o Wokwi para testar sem hardware físico.  

---

##💡 Observações com LED
Ao adaptar o código PWM do servo para controlar um LED, foi possível observar o efeito de dimming (variação de intensidade) do LED. A mudança gradual do duty cycle do PWM, originalmente pensada para posicionar o servo, resultou em uma transição suave entre o LED menos brilhoso e seu brilho máximo, demonstrando a versatilidade da técnica PWM para diferentes aplicações.

## 🔗 **Diagrama do Circuito**  
![image](https://github.com/user-attachments/assets/d078c59a-b1fb-48fc-b1d7-5c9188d98cac)


---

## 🔗 **Vídeo de Funcionamento**

https://drive.google.com/file/d/1OE3Y2QQZCGZQfpEu8YwBZPsydoBFrp4q/view?usp=sharing

## 📞 **Contato**  
- 👤 **Autor**: Jonas Souza 
- 📧 **E-mail**: jonassouza871@hotmail.com 

---  
