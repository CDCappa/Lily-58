#!/usr/bin/env python3
"""
Script para parsear keymap.c y mostrar la matriz visual.
Uso: python show_keymap.py [layer_number]
"""

import re
import sys

KEYMAP_FILE = "../keymaps/ergomech_custom/keymap.c"

# Mapeo de keycodes QMK a nombres cortos
KEYCODE_MAP = {
    "KC_NO": "_",
    "XXXXXXX": "_",
    "_______": "vvv",
    "KC_TRNS": "vvv",
    "KC_A": "A", "KC_B": "B", "KC_C": "C", "KC_D": "D", "KC_E": "E",
    "KC_F": "F", "KC_G": "G", "KC_H": "H", "KC_I": "I", "KC_J": "J",
    "KC_K": "K", "KC_L": "L", "KC_M": "M", "KC_N": "N", "KC_O": "O",
    "KC_P": "P", "KC_Q": "Q", "KC_R": "R", "KC_S": "S", "KC_T": "T",
    "KC_U": "U", "KC_V": "V", "KC_W": "W", "KC_X": "X", "KC_Y": "Y",
    "KC_Z": "Z",
    "KC_1": "1", "KC_2": "2", "KC_3": "3", "KC_4": "4", "KC_5": "5",
    "KC_6": "6", "KC_7": "7", "KC_8": "8", "KC_9": "9", "KC_0": "0",
    "KC_TAB": "TAB", "KC_ESC": "ESC", "KC_SPC": "SPC", "KC_ENT": "ENT",
    "KC_BSPC": "BSP", "KC_DEL": "DEL",
    "KC_LCTL": "CTL", "KC_RCTL": "CTL", "KC_LSFT": "SFT", "KC_RSFT": "SFT",
    "KC_LALT": "ALT", "KC_RALT": "ALT", "KC_LGUI": "WIN", "KC_RGUI": "WIN",
    "KC_COMM": ",", "KC_DOT": ".", "KC_SLSH": "/", "KC_SCLN": ";",
    "KC_QUOT": "'", "KC_GRV": "`", "KC_MINS": "-", "KC_EQL": "=",
    "KC_LBRC": "[", "KC_RBRC": "]", "KC_BSLS": "\\",
    "KC_F1": "F1", "KC_F2": "F2", "KC_F3": "F3", "KC_F4": "F4",
    "KC_F5": "F5", "KC_F6": "F6", "KC_F7": "F7", "KC_F8": "F8",
    "KC_F9": "F9", "KC_F10": "F10", "KC_F11": "F11", "KC_F12": "F12",
    "KC_LEFT": "<-", "KC_DOWN": "DN", "KC_UP": "UP", "KC_RGHT": "->",
    "KC_VOLD": "V-", "KC_VOLU": "V+", "KC_MUTE": "MUT",
    "KC_MPRV": "|<", "KC_MPLY": ">||", "KC_MNXT": ">|",
    "QK_BOOT": "RST",
    "MC_ENE": "ene", "MC_ENEM": "ENE",
    "MO(1)": "MO1", "MO(2)": "FN",
    "S(KC_1)": "!", "S(KC_2)": "@", "S(KC_3)": "#", "S(KC_4)": "$",
    "S(KC_5)": "%", "S(KC_6)": "^", "S(KC_7)": "&", "S(KC_8)": "*",
    "S(KC_9)": "(", "S(KC_0)": ")",
    "S(KC_BSLS)": "|", "S(KC_EQL)": "+",
}

def short_name(keycode):
    """Convierte un keycode QMK a nombre corto."""
    keycode = keycode.strip()
    if keycode in KEYCODE_MAP:
        return KEYCODE_MAP[keycode]
    # Intentar parsear MO(), TG(), etc.
    if keycode.startswith("MO("):
        return f"MO{keycode[3:-1]}"
    if keycode.startswith("TG("):
        return f"TG{keycode[3:-1]}"
    return keycode[:5]  # Truncar si no se reconoce

def parse_keymap(filepath):
    """Parsea keymap.c y extrae los layers."""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()

    # Buscar todos los LAYOUT() - buscar hasta \),$ (cierre de LAYOUT en fin de linea)
    layers = []
    # Pattern mas robusto: desde LAYOUT( hasta una linea que termine en ), o )
    pattern = r'\[_\w+\]\s*=\s*LAYOUT\(([\s\S]*?)\n\),?'
    matches = re.findall(pattern, content)

    for match in matches:
        # Limpiar y separar keycodes
        # Busca: S(KC_X), KC_XXX, MO(X), MC_XXX, QK_BOOT, _______  etc.
        keys = re.findall(r'S\([^)]+\)|[A-Z][A-Z0-9_]+(?:\([^)]+\))?|_______', match)
        layers.append(keys)

    return layers

def print_layer(keys, layer_num, layer_name=""):
    """Imprime un layer en formato visual."""
    if len(keys) < 58:
        print(f"Error: Layer {layer_num} tiene {len(keys)} teclas, se esperaban 58")
        return

    # Convertir a nombres cortos
    k = [short_name(key) for key in keys]

    # Formato de matriz (ASCII compatible)
    print(f"\n[LAYER_{layer_num} - {layer_name}]")
    print("+-----+-----+-----+-----+-----+-----+             +-----+-----+-----+-----+-----+-----+")
    print(f"|{k[0]:^5}|{k[1]:^5}|{k[2]:^5}|{k[3]:^5}|{k[4]:^5}|{k[5]:^5}|             |{k[6]:^5}|{k[7]:^5}|{k[8]:^5}|{k[9]:^5}|{k[10]:^5}|{k[11]:^5}|")
    print("+-----+-----+-----+-----+-----+-----+             +-----+-----+-----+-----+-----+-----+")
    print(f"|{k[12]:^5}|{k[13]:^5}|{k[14]:^5}|{k[15]:^5}|{k[16]:^5}|{k[17]:^5}|             |{k[18]:^5}|{k[19]:^5}|{k[20]:^5}|{k[21]:^5}|{k[22]:^5}|{k[23]:^5}|")
    print("+-----+-----+-----+-----+-----+-----+             +-----+-----+-----+-----+-----+-----+")
    print(f"|{k[24]:^5}|{k[25]:^5}|{k[26]:^5}|{k[27]:^5}|{k[28]:^5}|{k[29]:^5}|             |{k[30]:^5}|{k[31]:^5}|{k[32]:^5}|{k[33]:^5}|{k[34]:^5}|{k[35]:^5}|")
    print("+-----+-----+-----+-----+-----+-----+-----+ +-----+-----+-----+-----+-----+-----+-----+")
    print(f"|{k[36]:^5}|{k[37]:^5}|{k[38]:^5}|{k[39]:^5}|{k[40]:^5}|{k[41]:^5}|{k[42]:^5}| |{k[43]:^5}|{k[44]:^5}|{k[45]:^5}|{k[46]:^5}|{k[47]:^5}|{k[48]:^5}|{k[49]:^5}|")
    print("+-----+-----+-----+-----+-----+-----+-----+ +-----+-----+-----+-----+-----+-----+-----+")
    print(f"                  |{k[50]:^5}|{k[51]:^5}|{k[52]:^5}|{k[53]:^5}| |{k[54]:^5}|{k[55]:^5}|{k[56]:^5}|{k[57]:^5}|")
    print("                  +-----+-----+-----+-----+ +-----+-----+-----+-----+")

def main():
    layer_names = ["BASE", "SYMBOLS", "FN/NAV", "ADJUST"]

    try:
        layers = parse_keymap(KEYMAP_FILE)
    except FileNotFoundError:
        print(f"Error: No se encontró {KEYMAP_FILE}")
        sys.exit(1)

    if len(sys.argv) > 1:
        # Mostrar layer específico
        layer_num = int(sys.argv[1])
        if layer_num < len(layers):
            name = layer_names[layer_num] if layer_num < len(layer_names) else ""
            print_layer(layers[layer_num], layer_num, name)
        else:
            print(f"Error: Layer {layer_num} no existe")
    else:
        # Mostrar todos los layers
        for i, layer in enumerate(layers):
            name = layer_names[i] if i < len(layer_names) else ""
            print_layer(layer, i, name)

if __name__ == "__main__":
    main()
