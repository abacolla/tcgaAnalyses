
# pragma once

#include <iostream>
#include <vector>
#include <string>
#include <utility>

void usage();
void usage()
{
std::cout << "\nUsage\n"
          << "-h, --help                       -    print this message and exit\n"
          << "--optAdat                        - A) gene expression dataset for option A\n"
          << "--optAgene1                      - A) gene 1 for option A\n"
          << "--optAgene2                      - A) gene 2 for option A\n" 
          << "--optBdat                        - B) gene expression dataset for option B\n"
          << "--optBgene                       - B) gene name for option B\n"
          << "--optCdat1                       - C) gene expression (dataset1) for option C\n"
          << "--optCgene                       - C) gene name for option C\n"
          << "--optCdat2                       - C) gene mutation (dataset2) for option C\n"
          << "--optDdat1                       - D) gene expression (dadaset1) for opton D\n"
          << "--optDdat2                       - D) mutation dataset2 for option D\n"
          << "--procs                          - D) filler - any number is fine\n"
		  << "--optE expMutAll                 - E) selects option E\n"
          << "--optFdat                        - F) gene expression dataset for option F\n"
          << "--optFgene                       - F) gene name for option F\n"
		  << "--optGdat                        - G) gene expression dataset for option G\n"
		  << "--optGgene1                      - G) gene 1 for option G\n"
		  << "--optGgene2                      - G) gene 2 for option G\n"
          << '\n'
          << "Option A is to find a correlation between gene expression of 2 genes\n"
          << "   Example: ibrun -n 1 vga_spotLight --optAdat ACC__geneExprT.txt --optAgene1 GRB2 --optAgene2 FGFR2\n"
          << "   Output file will be 'ACC_GRB2_FGFR2_expr.txt'\n"
          << '\n'
          << "Option B is to find a correlation between gene expression of 1 gene and all genes in dataset\n"
          << "   Example: ibrun -n 1 vga_spotLight --optBdat ACC__geneExprT.txt --optBgene GRB2\n"
          << "   Output file will be 'GRB2_toAll_ACC_T.txt'\n"
          << '\n'
          << "Option C is to find a correlation between gene expression of 1 gene from dataset1 and mutations in dataset2\n"
          << "   Example: ibrun -n 1 vga_spotLight --optCdat1 ACC__geneExpT.txt --optCdat2 ACC__somMutT_geneLevel.txt --optCgene GRB2\n"
          << "   Output file will be 'ACC_expr_mutsOne.txt' - NOTE 0=do_not_output_data; 1=output_data\n"
          << '\n'
          << "Option D is to find correlations between gene expression of all genes in dataset1 and mutations in dataset2\n"
          << "   Example: ibrun -n 1 vga_spotLight --optDdat1 ACC__geneExpT.txt --optDdat2 ACC__somMutT_geneLevel.txt --procs 16\n"
          << "   Output file will be 'ACC_expr_mutsAll.txt'\n"
          << '\n'
          << "Option E is to find correlations between gene expression of all genes and mutations in all datasets\n"
          << "   Example: inrun vga_spotLight --optE expMutAll\n"
          << "   Output files will be 'ACC_expr_mutsAll.txt ... BLCA_expr_mutsAll.txt ... etc.'\n"
          << '\n'
          << "Option F is to output gene expression data for one gene\n"
          << "   Example: ibrun -n 1 vga_spotLight --optFdat ACC__geneExprT.txt --optFgene GRB2\n"
          << "   Output file will be 'ACC_GRB2_exprOne.txt'\n" 
          << '\n'
          << "Option G is to get gene expression of 2 genes for survival curves\n"
          << "   Example: ibrun -n 1 vga_spotLight --optGdat ACC__geneExprT.txt --optGgene1 GRB2 --optGgene2 FGFR2\n"
          << "   Output file will be 'ACC_GRB2_FGFR2_forKM.txt'\n"
          << '\n'
          << "In main:\n"
          << "readRows()         - options A-F: function to read gene expression dataset data into vector v1\n"
          << "regrPair()         - option A:    function to perform regression\n"
          << "regrOneToAll()     - option B:    function to perform regression\n"
          << "geneExprOneGene()  - option C|G:  function to get expression data for 1 gene\n"
          << "geneExprTwoGene()  - option G:    function to get expression data for gene 2 for survival curves\n"
          << "readGeVal2()       - option C:    function to read data from dataset2 (mutations) into vector v3\n"
          << "countMuts()        - option C:    function to add mutations for each patient\n"
          << "joinExprWithMuts() - option C:    function to pair gene expression with mutation load\n\n";
}

struct errCode
{
    errCode(const int& param_)
        : param{ param_ } {}

    void errMessage()
    {
        if (param < 3)
        {
            usage();
            std::cout << "...exiting gracefully...\n\n";
        }
        else
        {
            std::cout << "\nCHECK PARAMETER OPTIONS!\n";
            usage();
        }
    }

private:
    int param = 0;

};


std::string pre1 = "/work/02076/abacolla/stampede2/rnaSeq_tcga_18/";
std::string pre2 = "/work/02076/abacolla/stampede2/somMut_tcga_18/";
std::string d01a = pre1 + "acc/Part2_BasicDataProcessing/ACC__geneExpT.txt";
std::string d02a = pre1 + "blca/Part2_BasicDataProcessing/BLCA__geneExpT.txt";
std::string d03a = pre1 + "brca/Part2_BasicDataProcessing/BRCAp1__geneExpT.txt";
std::string d04a = pre1 + "cesc/Part2_BasicDataProcessing/CESC__geneExpT.txt";
std::string d05a = pre1 + "chol/Part2_BasicDataProcessing/CHOL__geneExpT.txt";
std::string d06a = pre1 + "coad/Part2_BasicDataProcessing/COAD__geneExpT.txt";
std::string d07a = pre1 + "dlbc/Part2_BasicDataProcessing/DLBC__geneExpT.txt";
std::string d08a = pre1 + "esca/Part2_BasicDataProcessing/ESCA__geneExpT.txt";
std::string d09a = pre1 + "gbm/Part2_BasicDataProcessing/GBM__geneExpT.txt";
std::string d10a = pre1 + "hnsc/Part2_BasicDataProcessing/HNSC__geneExpT.txt";
std::string d11a = pre1 + "kich/Part2_BasicDataProcessing/KICH__geneExpT.txt";
std::string d12a = pre1 + "kirc/Part2_BasicDataProcessing/KIRC__geneExpT.txt";
std::string d13a = pre1 + "kirp/Part2_BasicDataProcessing/KIRP__geneExpT.txt";
std::string d14a = pre1 + "laml/Part2_BasicDataProcessing/LAML__geneExpT.txt";
std::string d15a = pre1 + "lgg/Part2_BasicDataProcessing/LGG__geneExpT.txt";
std::string d16a = pre1 + "lihc/Part2_BasicDataProcessing/LIHC__geneExpT.txt";
std::string d17a = pre1 + "luad/Part2_BasicDataProcessing/LUAD__geneExpT.txt";
std::string d18a = pre1 + "lusc/Part2_BasicDataProcessing/ACC__geneExpT.txt";
std::string d19a = pre1 + "meso/Part2_BasicDataProcessing/MESO__geneExpT.txt";
std::string d20a = pre1 + "ov/Part2_BasicDataProcessing/OV__geneExpT.txt";
std::string d21a = pre1 + "paad/Part2_BasicDataProcessing/PAAD__geneExpT.txt";
std::string d22a = pre1 + "pcpg/Part2_BasicDataProcessing/PCPG__geneExpT.txt";
std::string d23a = pre1 + "prad/Part2_BasicDataProcessing/PRAD__geneExpT.txt";
std::string d24a = pre1 + "read/Part2_BasicDataProcessing/READ__geneExpT.txt";
std::string d25a = pre1 + "sarc/Part2_BasicDataProcessing/SARC__geneExpT.txt";
std::string d26a = pre1 + "skcm/Part2_BasicDataProcessing/SKCM__geneExpT.txt";
std::string d27a = pre1 + "stad/Part2_BasicDataProcessing/STAD__geneExpT.txt";
std::string d28a = pre1 + "tgct/Part2_BasicDataProcessing/TGCT__geneExpT.txt";
std::string d29a = pre1 + "thca/Part2_BasicDataProcessing/THCA__geneExpT.txt";
std::string d30a = pre1 + "thym/Part2_BasicDataProcessing/THYM__geneExpT.txt";
std::string d31a = pre1 + "ucec/Part2_BasicDataProcessing/UCEC__geneExpT.txt";
std::string d32a = pre1 + "ucs/Part2_BasicDataProcessing/UCS__geneExpT.txt";
std::string d33a = pre1 + "uvm/Part2_BasicDataProcessing/UVM__geneExpT.txt";
std::string d34a = pre1 + "brca/Part2_BasicDataProcessing/BRCAp2__geneExpT.txt";

std::string d01b = pre2 + "acc/Part2_BasicDataProcessing/ACC__somMutT_geneLevel.txt";
std::string d02b = pre2 + "blca/Part2_BasicDataProcessing/BLCA__somMutT_geneLevel.txt";
std::string d03b = pre2 + "brca/Part2_BasicDataProcessing/BRCA__somMutT_geneLevel.txt";
std::string d04b = pre2 + "cesc/Part2_BasicDataProcessing/CESC__somMutT_geneLevel.txt";
std::string d05b = pre2 + "chol/Part2_BasicDataProcessing/CHOL__somMutT_geneLevel.txt";
std::string d06b = pre2 + "coad/Part2_BasicDataProcessing/COAD__somMutT_geneLevel.txt";
std::string d07b = pre2 + "dlbc/Part2_BasicDataProcessing/DLBC__somMutT_geneLevel.txt";
std::string d08b = pre2 + "esca/Part2_BasicDataProcessing/ESCA__somMutT_geneLevel.txt";
std::string d09b = pre2 + "gbm/Part2_BasicDataProcessing/GBM__somMutT_geneLevel.txt";
std::string d10b = pre2 + "hnsc/Part2_BasicDataProcessing/HNSC__somMutT_geneLevel.txt";
std::string d11b = pre2 + "kich/Part2_BasicDataProcessing/KICH__somMutT_geneLevel.txt";
std::string d12b = pre2 + "kirc/Part2_BasicDataProcessing/KIRC__somMutT_geneLevel.txt";
std::string d13b = pre2 + "kirp/Part2_BasicDataProcessing/KIRP__somMutT_geneLevel.txt";
std::string d14b = pre2 + "laml/Part2_BasicDataProcessing/LAML__somMutT_geneLevel.txt";
std::string d15b = pre2 + "lgg/Part2_BasicDataProcessing/LGG__somMutT_geneLevel.txt";
std::string d16b = pre2 + "lihc/Part2_BasicDataProcessing/LIHC__somMutT_geneLevel.txt";
std::string d17b = pre2 + "luad/Part2_BasicDataProcessing/LUAD__somMutT_geneLevel.txt";
std::string d18b = pre2 + "lusc/Part2_BasicDataProcessing/ACC__somMutT_geneLevel.txt";
std::string d19b = pre2 + "meso/Part2_BasicDataProcessing/MESO__somMutT_geneLevel.txt";
std::string d20b = pre2 + "ov/Part2_BasicDataProcessing/OV__somMutT_geneLevel.txt";
std::string d21b = pre2 + "paad/Part2_BasicDataProcessing/PAAD__somMutT_geneLevel.txt";
std::string d22b = pre2 + "pcpg/Part2_BasicDataProcessing/PCPG__somMutT_geneLevel.txt";
std::string d23b = pre2 + "prad/Part2_BasicDataProcessing/PRAD__somMutT_geneLevel.txt";
std::string d24b = pre2 + "read/Part2_BasicDataProcessing/READ__somMutT_geneLevel.txt";
std::string d25b = pre2 + "sarc/Part2_BasicDataProcessing/SARC__somMutT_geneLevel.txt";
std::string d26b = pre2 + "skcm/Part2_BasicDataProcessing/SKCM__somMutT_geneLevel.txt";
std::string d27b = pre2 + "stad/Part2_BasicDataProcessing/STAD__somMutT_geneLevel.txt";
std::string d28b = pre2 + "tgct/Part2_BasicDataProcessing/TGCT__somMutT_geneLevel.txt";
std::string d29b = pre2 + "thca/Part2_BasicDataProcessing/THCA__somMutT_geneLevel.txt";
std::string d30b = pre2 + "thym/Part2_BasicDataProcessing/THYM__somMutT_geneLevel.txt";
std::string d31b = pre2 + "ucec/Part2_BasicDataProcessing/UCEC__somMutT_geneLevel.txt";
std::string d32b = pre2 + "ucs/Part2_BasicDataProcessing/UCS__somMutT_geneLevel.txt";
std::string d33b = pre2 + "uvm/Part2_BasicDataProcessing/UVM__somMutT_geneLevel.txt";

std::vector<std::pair<std::string, std::string>> tcgaDset
{
    {d01a, d01b}, {d02a, d02b}, {d03a, d03b}, {d04a, d04b}, {d05a, d05b},
    {d07a, d07b}, {d08a, d08b}, {d09a, d09b}, {d10a, d10b},
    {d11a, d11b}, {d12a, d12b}, {d13a, d13b}, {d14a, d14b}, {d15a, d15b},
    {d16a, d16b}, {d17a, d17b}, {d18a, d18b}, {d19a, d19b}, {d20a, d20b},
    {d21a, d21b}, {d22a, d22b}, {d23a, d23b}, {d24a, d24b}, {d25a, d25b},
    {d27a, d27b}, {d28a, d28b}, {d29a, d29b}, {d30a, d30b},
    {d32a, d32b}, {d33a, d33b}, {d34a, d03b}
};

std::vector<std::pair<std::string, std::string>> tcgaCheck
{
    {d01a, d01b}, {d06a, d06b}, {d26a, d26b}
};

