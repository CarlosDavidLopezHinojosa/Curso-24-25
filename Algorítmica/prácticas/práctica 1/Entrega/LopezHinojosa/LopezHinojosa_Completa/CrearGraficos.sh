#!/bin/bash

Burbuja="OrdenacionBurbuja"
MultiplicacionMatrices="MultiplicacionMatrices"
DeterminanteRecursivo="DeterminanteRecursivo"


for nombre in "$Burbuja" "$MultiplicacionMatrices" "$DeterminanteRecursivo"
do
    if [ -e "datos$nombre.txt" ]
    then

        cat << _end_ | gnuplot
        set terminal postscript eps color
        set output "$nombre.jpg"
        set key right bottom
        set xlabel "N "
        set ylabel "Tiempo en milisegundos"
        plot 'datos$nombre.txt' using 1:2 t "Tiempos Reales", \
             'datos$nombre.txt' using 1:3 t "Tiempos Estimados" w l
_end_
    fi
done