#include <stdio.h>
#include <stdint.h>

// Función para calcular checksum de 16 bits
uint16_t calcular_checksum(uint16_t *datos, size_t longitud) {
    uint32_t suma = 0;

    for (size_t i = 0; i < longitud; i++) {
        suma += datos[i];
        // End-around carry para mantener 16 bits
        if (suma > 0xFFFF) {
            suma = (suma & 0xFFFF) + 1;
        }
    }

    // Complemento a uno
    return ~suma & 0xFFFF;
}

// Función para verificar mensaje con checksum incluido
int verificar_checksum(uint16_t *datos, size_t longitud) {
    uint32_t suma = 0;

    for (size_t i = 0; i < longitud; i++) {
        suma += datos[i];
        if (suma > 0xFFFF) {
            suma = (suma & 0xFFFF) + 1;
        }
    }

    // Si la suma final es 0xFFFF (todo 1s), el mensaje es válido
    return (suma == 0xFFFF);
}

int main() {
    // Ejemplo de datos de entrada
    uint16_t mensaje[] = {0x1234, 0xABCD, 0x0F0F};
    size_t longitud = sizeof(mensaje) / sizeof(mensaje[0]);

    // Calcular checksum
    uint16_t checksum = calcular_checksum(mensaje, longitud);
    printf("Checksum calculado: 0x%04X\n", checksum);

    // Crear mensaje con checksum anexado
    uint16_t mensaje_con_checksum[longitud + 1];
    for (size_t i = 0; i < longitud; i++) {
        mensaje_con_checksum[i] = mensaje[i];
    }
    mensaje_con_checksum[longitud] = checksum;

    // Verificar mensaje
    if (verificar_checksum(mensaje_con_checksum, longitud + 1)) {
        printf("Mensaje recibido correctamente.\n");
    } else {
        printf("Error detectado en el mensaje.\n");
    }

    return 0;
}
