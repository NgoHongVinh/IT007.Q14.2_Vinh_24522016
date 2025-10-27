#!/bin/bash
set -e
for file in *.c; do
    [ -f "$file" ] && gcc "$file" -o "${file%.c}" -lrt
done
