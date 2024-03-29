# tcgaAnalyses

Scripts to analyze TCGA cancer genomic data.

## Script 1 

vga_makeBoxPlotRsem.sh - compare RNA-Seq gene expression between tumor and matched normal.

* Synopsis: vga_makeBoxPlotRsem.sh generates a high-quality png box plot with the mRNA expression data of a given gene for 15 TCGA tumor and normal matched controls suitable for publication upon minimal editing. The number of tumor/normal pairs is limited to those cancer sets with at least 10 normal controls.

* Usage: vga_makeBoxPlotRsem.sh <GENE_NAME> - where <GENE_NAME> is an official gene name in capital letters.

Example: vga_makeBoxPlotRsem.sh ERCC1

* Notes: Edit lines 8-11 to load any module required for R and edit DIR0 on line 13 to point to the RNA gene expression files. These files were obtained using [TCGA-Assembler v.2.0](https://github.com/compgenome365/TCGA-Assembler-2) and a copy is available at [ResearchGate](https://www.researchgate.net/profile/Albino_Bacolla) under the project TCGA Analyses (see References). Box plots are drawn according to the list on lines 63-77; to change the ranking, such as plotting according to p-values, change the order on lines 63-77. vga_makeBoxPlotRsem.sh calls vga_pngBoxPlotRsem.R. Options in vga_pngBoxPlotRsem.R that control main aestetic features include y-axis range on line 52 (ylim), p-values (on, off) on line 53 (stats_compare_means), colors for the plots on line 73 (scale_fill_manual), the x-axis line (axis.line.x) on line 71, notch (true, false) on line 46. vga_makeBoxPlotRsem.sh can be scaled-up using vga_submitMpiJob, which is detailed in the directory submitMpi.
  
## Script 2

vga_survivalCurve.sh - make Kaplan-Meier survival curve.

* Synopsis: vga_survivalCurve.sh generates a png plot for a Kaplan-Meier survival curve for TCGA patients comparing between samples with high (above mean) versus samples with low (below mean) expression for a given gene.

* Usage: vga_survivalCurve.sh <TCGA_TUMOR> <GENE_NAME> - where TCGA_TUMOR is the TCGA tumor code and GENE_NAME an official gene name, both in capital letters.

Example: vga_survivalCurve.sh KIRC ERCC1

* Notes: Edit lines 8-11 to load any module required for R. Line 19 launches the vga_spotLight binary (see Script 3), specify its path; the --optFdat option points to the TCGA gene expression files, edit the path. Edit line 21 to point to the TCGA clinical data files. Line 32 calls vga_survival.R, verify its path. The example above will generate a graphic file named kirc_ercc1.png and a text file named survival_ercc1_kirc.out. vga_survivalCurve.sh can be scaled-up using vga_submitMpiJob, which is detailed in the directory submitMpi.

## Script 3 

vga_geneExprMain.cpp - general utility to process TCGA gene expression and mutation files.

* Synopsis: Option A is to find a correlation between gene expression of 2 genes
          Option B is to find a correlation between gene expression of 1 gene and all genes in the dataset
          Option C is to find a correlation between gene expression of 1 gene from dataset1 and mutations in dataset2
          Option D is to find correlations between gene expression of all genes in dataset1 and mutations in dataset2
          Option E is to find correlations between gene expression of all genes and mutations in all datasets
          Option F is to output gene expression data for one gene
          Option G is to get gene expression of 2 genes for survival curves (used by vga_survivalCurve.sh)
          
* Usage and Examples:

Option A:
   Example: ibrun -n 1 vga_spotLight --optAdat ACC__geneExprT.txt --optAgene1 GRB2 --optAgene2 FGFR2
   Output file will be 'ACC_GRB2_FGFR2_expr.txt'

Option B:
   Example: ibrun -n 1 vga_spotLight --optBdat ACC__geneExprT.txt --optBgene GRB2
   Output file will be 'GRB2_toAll_ACC_T.txt'

Option C:
   Example: ibrun -n 1 vga_spotLight --optCdat1 ACC__geneExpT.txt --optCdat2 ACC__somMutT_geneLevel.txt --optCgene GRB2
   Output file will be 'ACC_expr_mutsOne.txt'

Option D:
   Example: ibrun -n 1 vga_spotLight --optDdat1 ACC__geneExpT.txt --optDdat2 ACC__somMutT_geneLevel.txt --procs 16
   Output file will be 'ACC_expr_mutsAll.txt'

Option E:
   Example: ibrun -n x vga_spotLight --optE expMutAll
   Output files will be 'ACC_expr_mutsAll.txt ... BLCA_expr_mutsAll.txt ... etc.'

Option F:
   Example: ibrun -n 1 vga_spotLight --optFdat ACC__geneExprT.txt --optFgene GRB2
   Output file will be 'ACC_GRB2_exprOne.txt'

Option G:
   Example: ibrun -n 1 vga_spotLight --optGdat ACC__geneExprT.txt --optGgene1 GRB2 --optGgene2 FGFR2
   Output file will be 'ACC_GRB2_FGFR2_forKM.txt'
   
* Notes: Edit Makefile to point to the BOOST library and preload any module required for MPI. Edit lines 96 and 97 of vga_geneExprUsage.hpp to point to the directories containing the gene expression and mutation data. File testStart.sh may be used as a guide to test the vga_spotLight compiled binary.

## Notes

With R version 3.5.1 vga_makeBoxPlotRsem.sh may raise the following error: */opt/apps/intel18/impi18_0/Rstats/3.5.1/lib64/R/bin/BATCH: line 60: 78714 Segmentation fault      ${R_HOME}/bin/R -f ${in} ${opts} ${R_BATCH_OPTIONS} > ${out} 2>&1* caused by a bug in rlang. This can be fixed by loading a dev version of rlang.
``` r
install.packages("pak", repos = "https://r-lib.github.io/p/pak/dev/")
pak::pkg_install("r-lib/rlang")
```

## References

Bacolla A, Tainer JA. [Robust computational approaches to defining insights on the interface of DNA repair with replication and transcription in cancer](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC9377048/) *Methods Mol. Biol.* **2444**, 1-13, 2022. PMID: 35290628 PMCID: PMC9377048  DOI: 10.1007/978-1-0716-2063-2_1

Ye et al. [GRB2 enforces homology-directed repair initiation by MRE11](https://advances.sciencemag.org/content/7/32/eabe9254) *Sci. Adv.* **7**, eabe9254, 2021. PMID: 34348893 PMCID: PMC8336959  DOI: 10.1126/sciadv.abe9254

Hambarde et al. [EXO5-DNA structure and BLM interactions direct DNA resection critical for ATR-dependent replication restart](https://www.sciencedirect.com/science/article/pii/S1097276521004202?via%3Dihub) *Mol. Cell* **81**, 2989–3006, 2021. PMID: 34197737  PMCID: PMC8720176  DOI: 10.1016/j.molcel.2021.05.027

Lees-Miller et al. [Uncovering DNA-PKcs ancient phylogeny, unique sequence motifs and insights for human disease](https://www.sciencedirect.com/science/article/pii/S0079610720300973?via%3Dihub) *Prog. Biophys. Mol. Biol.* **163**, 87-108, 2021. PMID: 33035590  PMCID: PMC8021618  DOI: 10.1016/j.pbiomolbio.2020.09.010

Bacolla et al. [Heritable pattern of oxidized DNA base repair coincides with pre-targeting of repair complexes to open chromatin](https://academic.oup.com/nar/article/49/1/221/6029161) *Nucleic Acids Res.* **49**, 221-243, 2021. PMID: 33300026  PMCID: PMC7797072  DOI: 10.1093/nar/gkaa1120

Singh et al. [Histone acetyltransferase MOF orchestrates outcomes at the crossroad of oncogenesis, DNA damage response, proliferation, and stem cell development](https://mcb.asm.org/content/mcb/40/18/e00232-20.full.pdf) *Mol. Cell. Biol.* **40**, e00232-20, 2020. PMID: 32661120  PMCID: PMC7459263  DOI: 10.1128/MCB.00232-20

Eckelmann et al. [XRCC1 promotes replication restart, nascent fork degradation and mutagenic DNA repair in BRCA2-deficient cells](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7397735/) *NAR Cancer* **2**, zcaa013, 2020. PMID: 32776008  PMCID: PMC7397735  DOI: 10.1093/narcan/zcaa013

Bacolla et al. [Cancer mutational burden is shaped by G4 DNA, replication stress and mitochondrial dysfunction](https://www.sciencedirect.com/science/article/pii/S0079610718302426?via%3Dihub) *Prog. Biophys. Mol. Biol.* **147**, 47-61, 2019. PMID: 30880007  PMCID: PMC6745008  DOI: 10.1016/j.pbiomolbio.2019.03.004

Houl et al. [Selective small molecule PARG inhibitor causes replication fork stalling and cancer cell death](https://www.nature.com/articles/s41467-019-13508-4) *Nat. Commun.* **10**, 5654, 2019. PMID: 31827085  PMCID: PMC6906431  DOI: 10.1038/s41467-019-13508-4
