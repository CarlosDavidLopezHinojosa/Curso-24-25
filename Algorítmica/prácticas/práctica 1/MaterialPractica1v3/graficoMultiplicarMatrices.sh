#!/bin/bash

#OJO: adaptar las leyendas a los nombres de las variables. En el eje Y se miden tiempos y en el eje X es el tamaño del ejemplar.
cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoMultiplicacionMatrices.eps"
set key right bottom
set xlabel "Etiqueta eje X"
set ylabel "Etiqueta Eje Y"
plot 'datosMultiplicacionMatrices.txt' using 1:2 t "Datos columna 2 frente a 1" w l, \
     'datosMultiplicacionMatrices.txt' using 3:4 t "Datos columna 4 frente a 3" w l
_end_
