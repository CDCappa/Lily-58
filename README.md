# Lily58 Ergomech Custom Firmware

Firmware personalizado QMK para Lily58 con RP2040 de Ergomech Store.

## Características

- **Tecla Ñ**: Macro `MC_ENE` que envía `AltGr+N` (funciona con layout English International)
- **Tecla Ñ mayúscula**: `MC_ENEM` en layer LOWER
- **Macro Email**: Configurable en `keymap.c`
- **Master derecho**: El cable USB se conecta al lado derecho
- **4 Layers**: QWERTY, LOWER, RAISE, ADJUST

## Layers

### Layer 0 - QWERTY (Base)
```
,-----------------------------------------.                    ,-----------------------------------------.
| ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
|------+------+------+------+------+------|                    |------+------+------+------+------+------|
| Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
|------+------+------+------+------+------|                    |------+------+------+------+------+------|
| Ctrl |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
|------+------+------+------+------+------|   [   |    |   ]   |------+------+------+------+------+------|
|Shift |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |Enter |
`-----------------------------------------/       /     \      \-----------------------------------------'
                  | GUI  |LOWER | Alt  | /Space  /       \Bkspc \  |RAISE | DEL  | ENE  |
                  |      |      |      |/       /         \      \ |      |      |      |
                  `----------------------------'           '------''--------------------'
```

### Layer 1 - LOWER (Símbolos y F-keys)
- F1-F12
- Símbolos: `! @ # $ % ^ & * ( )`
- Números en home row
- `MC_ENE` (ñ) y `MC_ENEM` (Ñ)

### Layer 2 - RAISE (Navegación)
- Flechas: ← ↓ ↑ →
- PgUp, PgDn, Home, End
- Más símbolos: `_ + { } [ ]`

### Layer 3 - ADJUST (LOWER + RAISE)
- `QK_BOOT`: Reset para flashear
- Control de volumen
- Control de media (Play, Prev, Next)
- Macro de email

## Compilar y Flashear

### Automático (GitHub Actions)
1. Hacer push a este repositorio
2. Ir a Actions → Build QMK Firmware
3. Descargar el artifact `lily58-firmware`
4. El archivo `lily58_ergomech_rp2040.uf2` está listo

### Flashear el RP2040
1. Desconectar el teclado
2. Mantener presionado **BOOTSEL/RESET** mientras conectas el USB
3. Aparece como unidad USB `RPI-RP2`
4. Arrastrar el archivo `.uf2` a esa unidad
5. Se reinicia automáticamente

## Personalización

Editar `keymaps/ergomech_custom/keymap.c`:

- **Cambiar email**: Buscar `SEND_STRING("tuemail@ejemplo.com")` y cambiar
- **Agregar macros**: Agregar en el `enum custom_keycodes` y en `process_record_user`
- **Cambiar teclas**: Modificar los arrays `LAYOUT()` de cada layer

## Configuración

En `config.h`:
- `MASTER_RIGHT`: El lado derecho es el master (donde va el USB)
- Cambiar a `MASTER_LEFT` o `EE_HANDS` según preferencia
