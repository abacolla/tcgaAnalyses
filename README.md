# tcgaAnalyses
Scripts to analyze TCGA cancer genomic data

Script 1 -- vga_makeBoxPlotRsem.sh
Synopsis: vga_makeBoxPlotRsem.sh is a script that generates a high-quality png box plot with the mRNA expression of a given gene for 15 TCGA tumor and normal matched controls suitable for publication. The number of tumor/normal pairs is limited to those cancer sets with at least 10 normal controls.
Usage: vga_makeBoxPlotRsem.sh <geneName> - where <geneName> is an official gene name in capital letters.
Example: vga_makeBoxPlotRsem.sh POLB
Notes: Edit lines 8-11 to load any module required for R and edit DIR0 on line 13 to point to the RNA gene expression files. These are found in directory tcgaGeneExpression and were obtained using TCGA-Assembler v.2.0 (https://github.com/compgenome365/TCGA-Assembler-2). Box plots are drawn according to the list on lines 63-77, to change the ranking, such as plotting according to p-values, change the order on lines 63-77. vga_makeBoxPlotRsem.sh calls vga_pngBoxPlotRsem.R automatically. Options in vga_pngBoxPlotRsem.R that can be modified to control aestetics include p-values on line 53 (stats_compare_means), colors for the plots on line 73 (scale_fill_manual) and the x-axis line (axis.line.x) on line 71. The script can be scaled-up using vga_submitMpiJob, detailed in directory submitMpi.
  

