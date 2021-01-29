
#include "vga_geneExprPair.hpp"
#include "vga_geneExprUsage.hpp"
#include <iostream>
#include <string>
#include <mpi.h>
#include <ctime>
using namespace std;

int main(int argc, char* argv[])
{
    clock_t t = clock();
    time_t currTime;
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Comm comm;
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    
    string Adat, Agene1, Agene2, Bdat, Bgene, Cdat1, Cgene, Cdat2, Ddat1, Ddat2, proc, EallGM, Fdat, Fgene, Gdat, Ggene1, Ggene2;

    if (argc == 1)
    {
        errCode e(argc);
        e.errMessage();
        return EXIT_SUCCESS;
    } else {
        for (int i = 1; i < argc; ++i)
        {
            string arg = argv[i];
            if (argc == 2 && (arg == "-h" || arg == "--help"))
            {
                errCode e(argc);
                e.errMessage();
                return EXIT_SUCCESS;
            } 
            else if (argc == 3)
            {
                if (arg == "--optE") { EallGM = argv[i + 1]; }
            }
            else if (argc == 5) 
            {
                if (arg == "--optBdat") { Bdat = argv[i + 1]; }
                if (arg == "--optBgene") { Bgene = argv[i + 1]; }
				if (arg == "--optFdat") { Fdat = argv[i + 1]; }
				if (arg == "--optFgene") { Fgene = argv[i + 1]; }
            } else if (argc == 7) 
            {
                if (arg == "--optAdat") { Adat = argv[i + 1]; }
                if (arg == "--optAgene1") { Agene1 = argv[i + 1]; }
                if (arg == "--optAgene2") { Agene2 = argv[i + 1]; }
                if (arg == "--optCdat1") { Cdat1 = argv[i + 1]; }
                if (arg == "--optCgene") { Cgene = argv[i + 1]; }
                if (arg == "--optCdat2") { Cdat2 = argv[i + 1]; }
                if (arg == "--optDdat1") { Ddat1 = argv[i + 1]; }
                if (arg == "--optDdat2") { Ddat2 = argv[i + 1]; }
                if (arg == "--procs") { proc = argv[i + 1]; }
                if (arg == "--optGdat") { Gdat = argv[i + 1]; }
                if (arg == "--optGgene1") { Ggene1 = argv[i + 1]; }
                if (arg == "--optGgene2") { Ggene2 = argv[i + 1]; }
            }
        }
    }

    if (!(Adat.empty() && Agene1.empty() && Agene2.empty()) && 
        Bdat.empty() && Bgene.empty() && 
        Cdat1.empty() && Cgene.empty() && Cdat2.empty() &&
        Ddat1.empty() && Ddat2.empty() && proc.empty() &&
		EallGM.empty() && 
		Fdat.empty() && Fgene.empty() &&
        Gdat.empty() && Ggene1.empty() && Ggene2.empty())    /* Option  A  - example: ibrun -n 1 vga_spotLight --optAdat ACC__geneExprT.txt 
                                                                             --optAgene1 GRB2 --optAgene2 FGFR2 */
    {
        ProcFields r3(Adat, Agene1, Agene2);
        r3.readRows();
        r3.regrPair();
    } 
    else if (!(Bdat.empty() && Bgene.empty()) &&
        Adat.empty() && Agene1.empty() && Agene2.empty() &&
        Cdat1.empty() && Cgene.empty() && Cdat2.empty() &&
        Ddat1.empty() && Ddat2.empty() && proc.empty() &&
		EallGM.empty() && 
		Fdat.empty() && Fgene.empty() &&
        Gdat.empty() && Ggene1.empty() && Ggene2.empty())     /* option B  - example: ibrun -n 1 vga_spotLight --optBdat ACC__geneExprT.txt 
                      								                         --optBgene GRB2 */
    {
        ProcFields r2(Bdat, Bgene);
        r2.readRows();
        r2.regrOneToAll();
    }
    else if (!(Cdat1.empty() && Cgene.empty() && Cdat2.empty()) &&
        Adat.empty() && Agene1.empty() && Agene2.empty() &&
        Bdat.empty() && Bgene.empty() &&
        Ddat1.empty() && Ddat2.empty() && proc.empty() &&
		EallGM.empty() && 
		Fdat.empty() && Fgene.empty() &&
        Gdat.empty() && Ggene1.empty() && Ggene2.empty())    /* Option C - example: ibrun -n 1 vga_spotLight --optCdat1 ACC__geneExprT.txt 
                                                                           --optCgene GRB2 --optCdat2 ACC__somMutT_geneLevel.txt */
    {
        ProcFields r1(Cdat1, Cgene, Cdat2);
        r1.readRows();
        r1.geneExprOneGene(0);
        r1.readGeVal2();
	    r1.countMuts();
	    r1.joinExprWithMuts(0);
    } 
    else if(!(Ddat1.empty() && Ddat2.empty() && proc.empty()) &&
        Adat.empty() && Agene1.empty() && Agene2.empty() &&
        Bdat.empty() && Bgene.empty() &&
        Cdat1.empty() && Cgene.empty() && Cdat2.empty() &&
		EallGM.empty() && 
		Fdat.empty() && Fgene.empty() &&
        Gdat.empty() && Ggene1.empty() && Ggene2.empty())	/* Option D - example: vga_spotLight -n 1 runme7 --optDdat1 ACC__geneExprT.txt
                                                               --optDdat2 ACC__somMutT_geneLevel.txt --procs 16 */
    {
        ProcFields r4(Ddat1, proc, Ddat2);
        r4.readRows();
        r4.getGeneList();
        r4.readGeVal2();
        r4.runAllGenesVsMuts();
    }
    else if (EallGM == "expMutAll" && 
        Adat.empty() && Agene1.empty() && Agene2.empty() &&
        Bdat.empty() && Bgene.empty() &&
        Cdat1.empty() && Cgene.empty() && Cdat2.empty() &&
        Ddat1.empty() && Ddat2.empty() && proc.empty() &&
		Fdat.empty() && Fgene.empty() &&
        Gdat.empty() && Ggene1.empty() && Ggene2.empty())	/* Option E - example: ibrun vga_spotLight --optE expMutAll */
    {
        ProcFields r5(tcgaCheck[rank].first, EallGM, tcgaCheck[rank].second);
        r5.readRows();
        r5.getGeneList();
        r5.readGeVal2();
        r5.runAllGenesVsMuts();
        t = clock() - t;
        double t1 = ((float)t/CLOCKS_PER_SEC/60);
        size_t pos1 = tcgaDset[rank].first.find_last_of("/");
        string myData = tcgaDset[rank].first.substr(pos1 + 1);
        cout << "Processor " << rank << " finished file " << myData << " in " << t1 << " min.; " << endl;
    }
	else if (!(Fdat.empty() && Fgene.empty()) && 
		Adat.empty() && Agene1.empty() && Agene2.empty() &&
		Bdat.empty() && Bgene.empty() &&
		Cdat1.empty() && Cgene.empty() && Cdat2.empty() &&
		Ddat1.empty() && Ddat2.empty() && proc.empty() &&
		EallGM.empty() &&
        Gdat.empty() && Ggene1.empty() && Ggene2.empty())	/* Option F - example: ibrun -n 1 vga_spotLight --optFdat ACC__geneExprT.txt
	 																      --optFgene GRB2 */
	{
		ProcFields r6(Fdat, Fgene);
		r6.readRows();
		r6.geneExprOneGene(1);
	}
    else if (!(Gdat.empty() && Ggene1.empty() && Ggene2.empty()) &&
        Adat.empty() && Agene1.empty() && Agene2.empty() &&
        Bdat.empty() && Bgene.empty() &&
        Cdat1.empty() && Cgene.empty() && Cdat2.empty() &&
        Ddat1.empty() && Ddat2.empty() && proc.empty() &&
        EallGM.empty() &&
        Fdat.empty() && Fgene.empty())   /* Option G - example: ibrun -n 1 vga_spotLight --optGdat ACC__geneExprT.txt --optGgene1 GRB2                                                                --optGgene2 FGFR2 */
    {
        ProcFields r7(Gdat, Ggene1, Ggene2);
        r7.readRows();
        r7.geneExprOneGene(0);
        r7.geneExprTwoGene();
    }
    else
    {
        errCode e(argc);
        e.errMessage();
        return EXIT_FAILURE;
    }
     
    MPI_Finalize();

    return 0;
}
