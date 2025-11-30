# Lily58 Ergomech Custom Firmware

Firmware personalizado QMK para Lily58 con RP2040 de Ergomech Store.

## Características

- **Tap Dance en paréntesis**: TD( y TD) con comportamiento triple:
  - Tap = `(` / `)`
  - Doble tap = `{` / `}`
  - Hold = `[` / `]`
- **Tecla Ñ**: Macro `MC_ENE` que envía `AltGr+N` (layout English International)
- **Shift+Enter**: Macro `MC_SENT` para soft line breaks (Slack, Discord, etc.)
- **RALT (Compose)**: Para usar con WinCompose y escribir caracteres especiales
- **Master derecho**: El cable USB se conecta al lado derecho
- **OLED**: Muestra el layer activo

## Layers

### Layer 0 - BASE
```
+-----+-----+-----+-----+-----+-----+             +-----+-----+-----+-----+-----+-----+
|  @  |  %  | TD( | TD) |  '  |  |  |             |  .  |  ;  | F5  | F4  | F2  |  `  |
+-----+-----+-----+-----+-----+-----+             +-----+-----+-----+-----+-----+-----+
| TAB |  Q  |  W  |  E  |  R  |  T  |             |  Y  |  U  |  I  |  O  |  P  |  -  |
+-----+-----+-----+-----+-----+-----+             +-----+-----+-----+-----+-----+-----+
| CTL |  A  |  S  |  D  |  F  |  G  |             |  H  |  J  |  K  |  L  |  ,  |  =  |
+-----+-----+-----+-----+-----+-----+-----+ +-----+-----+-----+-----+-----+-----+-----+
| SFT |  Z  |  X  |  C  |  V  |  B  | ENT | | ESC |  N  |  M  |  Ñ  |  &  | MO1 |  *  |
+-----+-----+-----+-----+-----+-----+-----+ +-----+-----+-----+-----+-----+-----+-----+
                  | WIN |RALT | ALT | SPC | | BSP |  /  |  !  |  #  |
                  +-----+-----+-----+-----+ +-----+-----+-----+-----+
```

### Layer 1 - SYMBOLS (MO1)
```
+-----+-----+-----+-----+-----+-----+             +-----+-----+-----+-----+-----+-----+
| F1  | F2  | F3  | F4  | F5  | F6  |             | F7  | F8  | F9  | F10 | F11 | F12 |
+-----+-----+-----+-----+-----+-----+             +-----+-----+-----+-----+-----+-----+
| TAB |     | UP  |     |     |     |             |  &  |  ^  |     |     |     |     |
+-----+-----+-----+-----+-----+-----+             +-----+-----+-----+-----+-----+-----+
| CTL |  <- | DN  | ->  |     |     |             |     |     |     |     |     |     |
+-----+-----+-----+-----+-----+-----+-----+ +-----+-----+-----+-----+-----+-----+-----+
| SFT |     |     |     |     |     |S+EN | | ESC |     |     |     |     |     |     |
+-----+-----+-----+-----+-----+-----+-----+ +-----+-----+-----+-----+-----+-----+-----+
                  |     |RALT | ALT | SPC | | DEL |     |     |     |
                  +-----+-----+-----+-----+ +-----+-----+-----+-----+
```

### Layers 2-3
Vacíos, disponibles para personalización futura.

## Compilar y Flashear

### Automático (GitHub Actions)
1. Hacer push a este repositorio
2. Ir a Actions → Build QMK Firmware
3. Descargar de Releases el archivo `.uf2`

### Flashear el RP2040
1. Desconectar el teclado
2. Mantener presionado **BOOTSEL/RESET** mientras conectas el USB
3. Aparece como unidad USB `RPI-RP2`
4. Arrastrar el archivo `.uf2` a esa unidad
5. Se reinicia automáticamente

## Archivos

- `keymaps/ergomech_custom/keymap.c` - Keymap principal
- `keymaps/ergomech_custom/rules.mk` - Habilita OLED, Tap Dance, LTO
- `keymap-editor.html` - Editor visual (abrir en navegador)

## Personalización

Editar `keymaps/ergomech_custom/keymap.c`:

- **Agregar macros**: En `enum custom_keycodes` y `process_record_user`
- **Cambiar teclas**: Modificar los arrays `LAYOUT()` de cada layer
- **Tap Dance**: Modificar `td_lprn_finished` y `td_rprn_finished`

## Configuración

En `config.h`:
- `MASTER_RIGHT`: El lado derecho es el master (donde va el USB)
