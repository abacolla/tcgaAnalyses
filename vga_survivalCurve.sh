#!/bin/bash

if [ "$#" -ne 2 ]; then
	    echo -e "\nUsage: vga_survivalCurve_s.sh <TCGA_TUMOR> <GENE_NAME>\nTCGA_TUMOR and GENE_NAME must be capital\n"
		    exit 1;
fi

module load intel/18.0.2
module load impi/18.0.2
module load Rstats/3.5.1
module load RstatsPackages/3.5.1

s1=`echo $1 | tr '[:upper:]' '[:lower:]'`
s2=$1
s3=$2
s4=`echo $2 | tr '[:upper:]' '[:lower:]'`

p1="$HOME/bin"
ibrun -n 1 ${p1}/vga_SpotLight --optFdat /work/02076/abacolla/stampede2/rnaSeq_tcga_18/$s1/Part2_BasicDataProcessing/${s2}__geneExpT.txt --optFgene $s3

cp /work/02076/abacolla/stampede2/cliDat_tcga_18/$s1/Part1_DownloadedData/${s1}_clinical_01 ./${s1}_${s4}_clinical_01
cut -f1 ${s1}_${s4}_clinical_01 > ${s1}_${s4}_cl_f1
cut -f1 ${s2}_${s3}_exprOne.txt > ${s1}_${s4}_f1
cat ${s1}_${s4}_cl_f1 ${s1}_${s4}_f1 | sort | uniq -d > ${s1}_${s4}_common
grep -f ${s1}_${s4}_common ${s1}_${s4}_clinical_01 > ${s1}_${s4}_clinical_good
grep -f ${s1}_${s4}_common ${s2}_${s3}_exprOne.txt | cut -f2 - > ${s1}_${s4}_good
echo "barcode	age	time	status	geneExp" > ${s1}_${s4}_head
paste ${s1}_${s4}_clinical_good ${s1}_${s4}_good | gawk '{ print $1 "\t" $2 "\t" $3/365 "\t" $4 "\t" $5 }'> ${s1}_${s4}_tmp1
cat ${s1}_${s4}_head ${s1}_${s4}_tmp1 > ${s1}_${s4}_survival

#R CMD BATCH survival_${s1}_${s4}.R
R CMD BATCH --no-save --no-restore "--args $s1 $s2 $s3 $s4 `pwd`" ./vga_survival.R survival_${s4}_${s1}.out

rm ${s1}_${s4}_cl_f1 \
${s1}_${s4}_clinical_01 \
${s1}_${s4}_clinical_good \
${s1}_${s4}_common \
${s2}_${s3}_exprOne.txt \
${s1}_${s4}_f1 \
${s1}_${s4}_good \
${s1}_${s4}_survival \
${s1}_${s4}_head \
${s1}_${s4}_tmp1
