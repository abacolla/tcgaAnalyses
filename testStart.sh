#!/bin/bash

# test file to test vga_spotLight -- edit the paths to point to the correct files and test if ibrun is the correct command on your system

# Option A - example
# ibrun -n 1 vga_spotLight  --optAdat /work/02076/abacolla/stampede2/rnaSeq_tcga_18/acc/Part2_BasicDataProcessing/ACC__geneExpT.txt --optAgene1 GRB2 --optAgene2 FGFR2

# Option B - example
# ibrun -n 1 vga_spotLight  --optBdat /work/02076/abacolla/stampede2/rnaSeq_tcga_18/chol/Part2_BasicDataProcessing/CHOL__geneExpT.txt --optBgene GRB2

# Option C
# ibrun -n 1 vga_spotLight  --optCdat1 /work/02076/abacolla/stampede2/rnaSeq_tcga_18/kich/Part2_BasicDataProcessing/KICH__geneExpT.txt --optCdat2 /work/02076/abacolla/stampede2/somMut_tcga_18/kich/Part2_BasicDataProcessing/KICH__somMutT_geneLevel.txt --optCgene GRB2

# Option D - takes time
# ibrun -n 1 vga_spotLight  --optDdat1 /work/02076/abacolla/stampede2/rnaSeq_tcga_18/dlbc/Part2_BasicDataProcessing/DLBC__geneExpT.txt --optDdat2 /work/02076/abacolla/stampede2/somMut_tcga_18/dlbc/Part2_BasicDataProcessing/DLBC__somMutT_geneLevel.txt --procs 16

# Option E
# --

# Option F
#ibrun -n 1 vga_spotLight  --optFdat /work/02076/abacolla/stampede2/rnaSeq_tcga_18/dlbc/Part2_BasicDataProcessing/DLBC__geneExpT.txt --optFgene EXO5

# Option G - only used to make Kaplan-Meier curve with "vga_survivalCurve.sh"
# ibrun -n 1 vga_spotLight  --optGdat /work/02076/abacolla/stampede2/rnaSeq_tcga_18/acc/Part2_BasicDataProcessing/ACC__geneExpT.txt --optGgene1 GRB2 --optGgene2 FGFR2 
