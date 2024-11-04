#!/bin/bash

# recebe dois arquivos, uma chave e um arquivo a ser encriptado
# encripta o arquivo com a chave
# salva o arquivo encriptado com o mesmo nome do arquivo original, mas com a extensão .ssl

# verifica se o número de argumentos é 2 ou 3
if [ $# -ne 2 -a $# -ne 3 ]; then
    echo "Número de argumentos inválido"
    exit 1
fi

# verifica se o arquivo de chave existe
if [ ! -f "$1" ]; then
    echo "Arquivo de chave não encontrado"
    exit 1
fi

# verifica se o arquivo a ser encriptado existe
if [ ! -f "$2" ]; then
    echo "Arquivo não encontrado"
    exit 1
fi

if [ $# -eq 3 -a ! -f "$3" ]; then
    echo "Arquivo de saída não encontrado"
    exit 1
fi
# se for passado um terceiro argumento, usa uma saída
if [ $# -eq 3 ]; then
    saida="$3"    
else
    saida="cifrado"  # Define um nome padrão para a saída
fi

# le a entrada
entrada="$1"
# pra ler a chave, é necessário converter o binario arquivo para hexadecimal
chave=$(cat "$2" | xxd -p)

# Verifica se a chave é hexadecimal e tem 32 caracteres
if [[ ! "$chave" =~ ^[0-9a-fA-F]+$ || ${#chave} -ne 32 ]]; then
    echo "A chave deve ser uma string hexadecimal de 16 bytes (32 caracteres)."
    echo "A fornecida tem ${#chave} caracteres."
    exit 1
fi

# encripta o arquivo
openssl enc -aes-128-ecb -K "$chave" -nosalt -in "$entrada" -out "$saida"

echo "Arquivo encriptado como $saida"
