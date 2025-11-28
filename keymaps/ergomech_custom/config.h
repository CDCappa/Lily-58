#pragma once

// ============================================
// CONFIGURACION LILY58 - ERGOMECH
// ============================================

// Lado master: el que se conecta por USB
// Opciones:
//   - No definir nada: izquierdo es master (default)
//   - MASTER_RIGHT: derecho es master
//   - EE_HANDS: detecta automaticamente segun EEPROM

#define MASTER_RIGHT  // Conecta el USB al lado DERECHO

// Si prefieres conectar por cualquier lado, comenta MASTER_RIGHT
// y descomenta EE_HANDS (requiere flashear cada mitad una vez)
// #define EE_HANDS

// Comunicacion entre mitades (importante para RP2040)
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

// Tapping term para teclas dual-function (tap vs hold)
#define TAPPING_TERM 200

// Permiso para usar SEND_STRING con caracteres especiales
#define MACRO_TIMER 5
