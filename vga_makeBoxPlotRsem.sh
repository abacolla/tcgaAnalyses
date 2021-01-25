#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo -e "\nUsage: vga_makeBoxPlotRsem.sh <geneName>\n"
    exit 1;
fi

module load intel/18.0.2  
module load impi/18.0.2
module load Rstats/3.5.1
module load RstatsPackages/3.5.1

DIR0="/work/02076/abacolla/stampede2/rnaSeq_tcga_18"

DIR1="$DIR0/hnsc/Part2_BasicDataProcessing"
DIR2="$DIR0/lusc/Part2_BasicDataProcessing"
DIR3="$DIR0/prad/Part2_BasicDataProcessing"
DIR4="$DIR0/kich/Part2_BasicDataProcessing"
DIR5="$DIR0/brca/Part2_BasicDataProcessing"
DIR6="$DIR0/stad/Part2_BasicDataProcessing"
DIR7="$DIR0/esca/Part2_BasicDataProcessing"
DIR8="$DIR0/coad/Part2_BasicDataProcessing"
DIR9="$DIR0/kirc/Part2_BasicDataProcessing"
DIR10="$DIR0/lihc/Part2_BasicDataProcessing"
DIR11="$DIR0/blca/Part2_BasicDataProcessing"
DIR12="$DIR0/ucec/Part2_BasicDataProcessing"
DIR13="$DIR0/thca/Part2_BasicDataProcessing"
DIR14="$DIR0/luad/Part2_BasicDataProcessing"
DIR15="$DIR0/kirp/Part2_BasicDataProcessing"

grep -w "$1" ${DIR1}/HNSC__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "HNSC" "\t" "Normal" }' > ${1}_hnscN.txt
grep -w "$1" ${DIR1}/HNSC__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "HNSC" "\t" "Tumor" }' > ${1}_hnscT.txt
grep -w "$1" ${DIR2}/LUSC__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "LUSC" "\t" "Normal" }' > ${1}_luscN.txt
grep -w "$1" ${DIR2}/LUSC__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "LUSC" "\t" "Tumor" }' > ${1}_luscT.txt
grep -w "$1" ${DIR3}/PRAD__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "PRAD" "\t" "Normal" }' > ${1}_pradN.txt
grep -w "$1" ${DIR3}/PRAD__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "PRAD" "\t" "Tumor" }' > ${1}_pradT.txt
grep -w "$1" ${DIR4}/KICH__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "KICH" "\t" "Normal" }' > ${1}_kichN.txt
grep -w "$1" ${DIR4}/KICH__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "KICH" "\t" "Tumor" }' > ${1}_kichT.txt
grep -w "$1" ${DIR5}/BRCA__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "BRCA" "\t" "Normal" }' > ${1}_brcaN.txt
grep -w "$1" ${DIR5}/BRCA__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "BRCA" "\t" "Tumor" }' > ${1}_brcaT.txt
grep -w "$1" ${DIR6}/STAD__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "STAD" "\t" "Normal" }' > ${1}_stadN.txt
grep -w "$1" ${DIR6}/STAD__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "STAD" "\t" "Tumor" }' > ${1}_stadT.txt
grep -w "$1" ${DIR7}/ESCA__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "ESCA" "\t" "Normal" }' > ${1}_escaN.txt
grep -w "$1" ${DIR7}/ESCA__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "ESCA" "\t" "Tumor" }' > ${1}_escaT.txt
grep -w "$1" ${DIR8}/COAD__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "COAD" "\t" "Normal" }' > ${1}_coadN.txt
grep -w "$1" ${DIR8}/COAD__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "COAD" "\t" "Tumor" }' > ${1}_coadT.txt
grep -w "$1" ${DIR9}/KIRC__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "KIRC" "\t" "Normal" }' > ${1}_kircN.txt
grep -w "$1" ${DIR9}/KIRC__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "KIRC" "\t" "Tumor" }' > ${1}_kircT.txt
grep -w "$1" ${DIR10}/LIHC__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "LIHC" "\t" "Normal" }' > ${1}_lihcN.txt
grep -w "$1" ${DIR10}/LIHC__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "LIHC" "\t" "Tumor" }' > ${1}_lihcT.txt
grep -w "$1" ${DIR11}/BLCA__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "BLCA" "\t" "Normal" }' > ${1}_blcaN.txt
grep -w "$1" ${DIR11}/BLCA__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "BLCA" "\t" "Tumor" }' > ${1}_blcaT.txt
grep -w "$1" ${DIR12}/UCEC__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "UCEC" "\t" "Normal" }' > ${1}_ucecN.txt
grep -w "$1" ${DIR12}/UCEC__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "UCEC" "\t" "Tumor" }' > ${1}_ucecT.txt
grep -w "$1" ${DIR13}/THCA__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "THCA" "\t" "Normal" }' > ${1}_thcaN.txt
grep -w "$1" ${DIR13}/THCA__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "THCA" "\t" "Tumor" }' > ${1}_thcaT.txt
grep -w "$1" ${DIR14}/LUAD__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "LUAD" "\t" "Normal" }' > ${1}_luadN.txt
grep -w "$1" ${DIR14}/LUAD__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "LUAD" "\t" "Tumor" }' > ${1}_luadT.txt
grep -w "$1" ${DIR15}/KIRP__geneExpN.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "KIRP" "\t" "Normal" }' > ${1}_kirpN.txt
grep -w "$1" ${DIR15}/KIRP__geneExpT.txt | tr '\t' '\n' | sed -n '3,$p' | awk '{ print log($1 + 1)/log(2) "\t" "KIRP" "\t" "Tumor" }' > ${1}_kirpT.txt

cat \
${1}_kircN.txt ${1}_kircT.txt \
${1}_luscN.txt ${1}_luscT.txt \
${1}_thcaN.txt ${1}_thcaT.txt \
${1}_pradN.txt ${1}_pradT.txt \
${1}_luadN.txt ${1}_luadT.txt \
${1}_brcaN.txt ${1}_brcaT.txt \
${1}_coadN.txt ${1}_coadT.txt \
${1}_kichN.txt ${1}_kichT.txt \
${1}_blcaN.txt ${1}_blcaT.txt \
${1}_lihcN.txt ${1}_lihcT.txt \
${1}_ucecN.txt ${1}_ucecT.txt \
${1}_hnscN.txt ${1}_hnscT.txt \
${1}_kirpN.txt ${1}_kirpT.txt \
${1}_escaN.txt ${1}_escaT.txt \
${1}_stadN.txt ${1}_stadT.txt \
> all${1}.txt

R CMD BATCH --no-save --no-restore "--args $1 `pwd`" ./vga_pngBoxPlotRsem.R pngBoxPlot${1}.out

rm ${1}_brcaN.txt ${1}_escaN.txt ${1}_kichN.txt \
${1}_kirpN.txt ${1}_luadN.txt ${1}_stadT.txt ${1}_ucecT.txt ${1}_blcaN.txt \
${1}_brcaT.txt ${1}_escaT.txt ${1}_kichT.txt ${1}_kirpT.txt ${1}_luadT.txt \
${1}_pradN.txt ${1}_thcaN.txt ${1}_blcaT.txt ${1}_coadN.txt ${1}_hnscN.txt \
${1}_kircN.txt ${1}_lihcN.txt ${1}_luscN.txt ${1}_pradT.txt ${1}_thcaT.txt \
${1}_coadT.txt ${1}_hnscT.txt ${1}_kircT.txt ${1}_lihcT.txt ${1}_luscT.txt \
${1}_stadN.txt ${1}_ucecN.txt all${1}.txt
