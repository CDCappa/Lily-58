# Protocolo de Mapeo de Teclas - Lily58

## Regla Principal
**SIEMPRE que se trabaje con mapeos, mostrar la matriz completa del estado actual antes y después de cambios.**

## Formato de Matriz

```
[LAYER_X - NOMBRE]
┌───────┬───────┬───────┬───────┬───────┬───────┐             ┌───────┬───────┬───────┬───────┬───────┬───────┐
│  F1   │  F2   │  F3   │  F4   │  F5   │  F6   │             │  F6   │  F5   │  F4   │  F3   │  F2   │  F1   │
├───────┼───────┼───────┼───────┼───────┼───────┤             ├───────┼───────┼───────┼───────┼───────┼───────┤
│  F1   │  F2   │  F3   │  F4   │  F5   │  F6   │             │  F6   │  F5   │  F4   │  F3   │  F2   │  F1   │
├───────┼───────┼───────┼───────┼───────┼───────┤             ├───────┼───────┼───────┼───────┼───────┼───────┤
│  F1   │  F2   │  F3   │  F4   │  F5   │  F6   │             │  F6   │  F5   │  F4   │  F3   │  F2   │  F1   │
├───────┼───────┼───────┼───────┼───────┼───────┼─────┐ ┌─────┼───────┼───────┼───────┼───────┼───────┼───────┤
│  F1   │  F2   │  F3   │  F4   │  F5   │  F6   │ X1  │ │ X2  │  F6   │  F5   │  F4   │  F3   │  F2   │  F1   │
└───────┴───────┴───────┼───────┼───────┼───────┼─────┤ ├─────┼───────┼───────┼───────┼───────┴───────┴───────┘
                        │  T1   │  T2   │  T3   │ T4  │ │ T5  │  T6   │  T7   │  T8   │
                        └───────┴───────┴───────┴─────┘ └─────┴───────┴───────┴───────┘
```

## Nomenclatura de Teclas

| Símbolo | Significado |
|---------|-------------|
| `_` | Nada (KC_NO) |
| `▼` | Transparente (usa layer inferior) |
| `Ñ` | Macro ñ minúscula |
| `Ñ!` | Macro Ñ mayúscula |
| `FN` | MO(2) - Momentary layer 2 |
| `MO1` | MO(1) - Momentary layer 1 |
| `TG1` | Toggle layer 1 |
| `WIN` | Tecla Windows/GUI |
| `SPC` | Espacio |
| `ENT` | Enter |
| `BSP` | Backspace |
| `ESC` | Escape |
| `TAB` | Tab |
| `CTL` | Control |
| `SFT` | Shift |
| `ALT` | Alt |
| `DEL` | Delete |
| `RST` | Reset/Bootloader |

## Formato para Solicitar Cambios

```
L[layer] F[fila] [posición] → [nueva tecla]
```

Ejemplos:
- `L0 F2 3 → Y` (Layer 0, Fila 2, posición 3, cambiar a Y)
- `L0 T5 → CTRL` (Layer 0, Thumb 5, cambiar a CTRL)
- `L1 X1 → ESC` (Layer 1, tecla extra izq, cambiar a ESC)

## Posiciones

**Filas (F1-F4):** 1-6 izquierda, 7-12 derecha
**Extras (X):** X1 = inner izq, X2 = inner der
**Thumbs (T):** T1-T4 izquierda, T5-T8 derecha

## Workflow

1. Usuario pide cambio de mapeo
2. Claude muestra matriz ACTUAL
3. Usuario confirma cambios con formato `L# F# # → tecla`
4. Claude aplica cambios
5. Claude muestra matriz NUEVA
6. Claude hace push a GitHub
7. Usuario descarga .uf2 y flashea
