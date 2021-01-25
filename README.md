# tcgaAnalyses
Scripts to analyze TCGA cancer genomic data

Script 1 -- vga_makeBoxPlotRsem.sh
vga_makeBoxPlotRsem.sh is a script that generates a high-quality png box plot with the mRNA expression of a given gene for 15 TCGA tumor and normal matched controls suitable for publication in a scientific journal. The number of tumor/normal pairs is limited to those cancer sets with at least 10 normal controls.
Usage: vga_makeBoxPlotRsem.sh <geneName> - where <geneName> is an official gene name in capital letters.
Example: vga_makeBoxPlotRsem.sh POLB
Notes: Edit lines 8-11 to load any module required for R and edit DIR0 on line 13 to point to the RNA gene expression files. These are found in rnaSeqTcga.tar.gz and were obtained using TCGA-Assembler v.2.0 (https://github.com/compgenome365/TCGA-Assembler-2). Box plots are drawn according to the list on lines 63-77; to change their ranking, such as plotting according to p-values, change the rank on lines 63-77. 

