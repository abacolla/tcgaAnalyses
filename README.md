# tcgaAnalyses
Scripts to analyze TCGA cancer genomic data

Script 1 -- vga_makeBoxPlotRsem.sh - compare RNA-Seq gene expression between tumor and matched normal.

Synopsis: vga_makeBoxPlotRsem.sh generates a high-quality png box plot with the mRNA expression data of a given gene for 15 TCGA tumor and normal matched controls suitable for publication upon minimal editing. The number of tumor/normal pairs is limited to those cancer sets with at least 10 normal controls.

Usage: vga_makeBoxPlotRsem.sh <GENE_NAME> - where <GENE_NAME> is an official gene name in capital letters.

Example: vga_makeBoxPlotRsem.sh ERCC1.

Notes: Edit lines 8-11 to load any module required for R and edit DIR0 on line 13 to point to the RNA gene expression files. These are found in directory tcgaGeneExpression and were obtained using TCGA-Assembler v.2.0 (https://github.com/compgenome365/TCGA-Assembler-2). Box plots are drawn according to the list on lines 63-77; to change the ranking, such as plotting according to p-values, change the order on lines 63-77. vga_makeBoxPlotRsem.sh calls vga_pngBoxPlotRsem.R. Options in vga_pngBoxPlotRsem.R that control main aestetic features include y-axis range on line 52 (ylim), p-values (on, off) on line 53 (stats_compare_means), colors for the plots on line 73 (scale_fill_manual), the x-axis line (axis.line.x) on line 71, notch (true, false) on line 46. vga_makeBoxPlotRsem.sh can be scaled-up using vga_submitMpiJob, which is detailed in directory submitMpi.
  
Script 2 -- vga_survivalCurve.sh - make Kaplan-Meier survival curve.

Synopsis: vga_survivalCurve.sh generates a png plot for a Kaplan-Meier survival curve for TCGA patients comparing between samples with high (above mean) versus those with low (below mean) expression for a given gene.

Usage: vga_survivalCurve.sh <TCGA_TUMOR> <GENE_NAME> - where TCGA_TUMOR is the TCGA tumor code and GENE_NAME an official gene name, both in capital letters.

Example: vga_survivalCurve.sh KIRC ERCC1.

Notes: Edit lines 8-11 to load any module required for R. Line 19 launches the vga_SpotLight binary, specify its path; the --optFdat option points to the TCGA gene expression files, edit the path. Edit line 21 to point to the TCGA clinical data files. Line 32 calls vga_survival.R, verify its path. The example above will generate a graphic file named kirc_ercc1.png and a text file named survival_ercc1_kirc.out. vga_survivalCurve.sh can be scaled-up using vga_submitMpiJob, which is detailed in directory submitMpi.
