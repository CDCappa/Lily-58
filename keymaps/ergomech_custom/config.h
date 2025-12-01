#pragma once

// Handedness se define via bootloader (uf2-split-left / uf2-split-right)
// que graba en EEPROM cual lado es cada modulo
#define EE_HANDS

// Tapping term para teclas dual-function
#define TAPPING_TERM 200

// Split keyboard sync - sincroniza estado entre las mitades
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_WPM_ENABLE
