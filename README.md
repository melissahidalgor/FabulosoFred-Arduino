# 🕹️ Proyecto: Fabuloso Fred (Juego de Secuencias Tipo Simon)

## Resumen del Proyecto

Este proyecto es una implementación del clásico juego de secuencias "Simon Dice" utilizando un microcontrolador Arduino Mega. El jugador debe memorizar y repetir una secuencia de luces generada aleatoriamente, la secuencia aumenta en cada nivel.

## 💻 Hardware y Componentes

| Componente | Cantidad | Función Principal |
| :--- | :---: | :--- |
| **Arduino Mega** | 1 | Microcontrolador |
| **LEDs (Azul, Rojo, Amarillo, Naranja, Verde)** | 5 | Mostrar la secuencia de la máquina |
| **Botones (Push Buttons)** | 5 | Capturar la secuencia del usuario |

**Configuración de Pines Clave:**
Se utilizan los pines 2 a 6 como salidas para los LEDs y los pines 7 a 11 como entradas (`INPUT_PULLUP`) para los botones. 

##  Funcionalidades Destacadas del Código

* **Selección de Dificultad:** El juego tiene dos modos de dificultad seleccionables a través del Monitor Seria:
    **Fácil (Opción 1):** La secuencia se genera una sola vez al inicio del juego y solo se extiende en cada nivel.
    **Difícil (Opción 2):** Se genera una **secuencia completamente nueva** en cada nivel.

* [cite_start]**Diagnóstico de Error:** Si la secuencia introducida es incorrecta, el Monitor Serial muestra la secuencia mostrada por el juego y la secuencia introducida por el usuario[cite: 2, 53].

## 🖼️ Montaje y Simulación

### Prototipo Físico

**Ver la conexión física:** [Link directo a Imagenes/Foto 2.jpg]

### Simulación Online
[cite_start]Puedes probar y ver el circuito en acción en Tinkercad[cite: 4]:
[https://www.tinkercad.com/embed/lwc8VqB2iYI?editbtn=1](https://www.tinkercad.com/embed/lwc8VqB2iYI?editbtn=1)

## 🚀 Instrucciones de Uso

1.  Compilar y cargar el código en el Arduino.
2.  [cite_start]Abrir el Monitor Serial a 9600 baudios[cite: 9, 50].
3.  [cite_start]Seleccionar la dificultad (`1` o `2`) e introducirla en el Monitor Serial[cite: 51].
4.  Presionar los botones en el orden de la secuencia mostrada por los LEDs.
5.  [cite_start]Para reiniciar el juego, presionar el botón de reinicio del Arduino[cite: 3, 54].

---

**Siguiente Paso:** Necesitas usar la herramienta **Git** (o la aplicación de escritorio de GitHub) para clonar el repositorio en tu computadora, crear estas carpetas, añadir los archivos, y subirlos (*push*) a GitHub.

Una vez que hayas subido los archivos, ¿te gustaría que te ayude a crear esa **página de perfil personalizada** para enlazar este y futuros proyectos?
