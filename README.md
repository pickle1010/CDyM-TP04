# TP4 Ejercicio Entregable

**UNLP - Facultad de Ingeniería**  
**Departamento de Electrotecnia**  
**Curso 2024 – 1er Cuatrimestre**  
**Circuitos Digitales y Microcontroladores (E305)**

## Control de un LED RGB

### Descripción del Proyecto

Este proyecto consiste en realizar un programa para controlar la intensidad y el color de un LED RGB utilizando la técnica de PWM (Modulación por Ancho de Pulsos). En el kit de clases, el LED RGB está conectado a los terminales PB5, PB2 y PB1 (RGB) a través de resistencias de limitación de 220 ohms y en configuración ánodo común. Para la simulación del modelo en Proteus se puede utilizar RGBLED-CA.

### Requerimientos detallados

1. **Generación de Señales PWM**: 
   - Genere en los tres terminales de conexión del LED tres señales PWM de frecuencia mayor o igual a 50 Hz y con una resolución de 8 bits cada una.

2. **Selección de Color**:
   - Seleccione la proporción de color de cada LED (de 0 a 255) para obtener un color resultante.

3. **Control por Interfaz Serie**:
   - Mediante un comando por la interfaz serie UART0, deberá activar cuál proporción de color desea modificar. Por ejemplo, envíe 'R' para modificar el rojo, 'G' para el verde y 'B' para el azul.

4. **Control de Brillo**:
   - Utilice el potenciómetro (resistencia variable) del kit conectado al terminal ADC3 para modificar el brillo del color seleccionado.

### Herramientas y Componentes Utilizados

- **Microcontrolador**
- **LED RGB**
- **Resistencias de 220 ohms**
- **Potenciómetro**
- **Proteus para simulación**

### Instrucciones de Uso

1. **Configuración del Hardware**:
   - Conectar el LED RGB a los terminales PB5, PB2 y PB1 con resistencias de 220 ohms.
   - Conectar el potenciómetro al terminal ADC3.

2. **Programación del Microcontrolador**:
   - Cargar el programa en el microcontrolador.
   - Configurar las señales PWM para cada color del LED.

3. **Interacción con el Sistema**:
   - Utilizar la interfaz serie UART0 para enviar comandos y seleccionar el color a modificar.
   - Ajustar el brillo del color seleccionado utilizando el potenciómetro.

### Simulación

Para la simulación en Proteus, se puede utilizar el modelo RGBLED-CA.

---

**Facultad de Ingeniería - Universidad Nacional de La Plata**
