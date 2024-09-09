import re

# Función para convertir secuencias hexadecimales a ASCII
def hex_to_ascii(hex_string):
    hex_string = hex_string.replace("\\x", "")
    ascii_string = bytes.fromhex(hex_string).decode('utf-8', errors='ignore')
    return ascii_string

# Texto original del archivo
file_path = "obfuscated.c"

# Lectura del archivo
with open(file_path, 'r') as file:
    content = file.read()

# Uso de expresiones regulares para encontrar cadenas hexadecimales
hex_strings = re.findall(r'\\x[0-9A-Fa-f]{2}', content)
unique_hex_strings = set(hex_strings)

# Reemplazo de cada cadena hexadecimal por su equivalente ASCII
for hex_str in unique_hex_strings:
    ascii_str = hex_to_ascii(hex_str)
    content = content.replace(hex_str, ascii_str)

# Guardar el contenido traducido a un nuevo archivo
with open("translated_obfuscated.c", 'w') as translated_file:
    translated_file.write(content)

print("Traducción completada y guardada en 'translated_obfuscated.c'.")
