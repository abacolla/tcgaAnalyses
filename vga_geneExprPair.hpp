#ifdef _MSC_VER
#  pragma warning(disable: 4512) // assignment operator could not be generated.
#  pragma warning(disable: 4510) // default constructor could not be generated.
#  pragma warning(disable: 4610) // can never be instantiated - user defined constructor required.
#endif
# pragma once
#include <boost/math/distributions/fisher_f.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <map>
#include "vga_geneExprUtils.hpp"

using namespace std;
using namespace boost::math;

class ProcFields
{
public:
    ProcFields(string filename_, string gene1_)
        : filename{ filename_ }, gene1{ gene1_ } {}

    ProcFields(string filename_, string gene1_, string geVal2_)
        : filename{ filename_ }, gene1{ gene1_}, geVal2{ geVal2_} {}

    int numPatients = 0;
	int numPatients2 = 0;
    int readRows(); 						// read data from dataset1 into vector v1
    int readGeVal2(); 						// read data from dataset2 into vector v3
    int regrPair(); 						// select pair of genes for regression
    int geneExprOneGene(int const&); 		// outputs gene expression for 1 gene for correlation with mutations
    int geneExprTwoGene();                  // goes with geneExprOneGene to have gene expression of 2 genes => survival curve
    int regrOneToAll(); 					// select one gene for regression against all genes
	int countMuts(); 						// count mutations in genes per patient
	int joinExprWithMuts(int const&); 		// outputs patient + gene expression for 1 gene + mutations in all genes
    void getGeneList(); 					// get names of all genes in gene expression dataset
    void runAllGenesVsMuts(); 				// get correlation between gene expression (all genes) and mutations using MPI

private:
    string filename;
    string gene1;
    string geVal2; 							// this is either a gene expression or a mutation dataset
    bool isInt(float x); 					// check if any data are missing
    vector<string> v1; 						// contains all data from dataset1 (filename)
    vector<pair<string, double> > v2; 		// contains patient + gene expression data for 1 gene to use with mutations or gene expression
    vector<string> v3; 						// contains all data from dataset2 (geVal2)
	vector<pair<string, double> > v4; 		// contains patient + total mutations in genes or + gene expression (surv. curves), multimap because of multiple patient IDs
    vector<pair<string, string>> geneList; 	// contains the list of genes and their gene ID  
    const string str2 = "GeneSymbol";
    void sums(double& lsh, double& rhs); 	// compute x and y pair
    double r_value(); 						// compute regression coefficient r
    double p_value(); 						// compute p-value for the regression
    double sumXY{};
    double sumX{};
    double sumY{};
    double sumX2{};
    double sumY2{};
    int n = 0;
    double F{};
};

bool ProcFields::isInt(float x) 			// check if it's an integer
{
    return floor(x) == x;
}
void ProcFields::sums(double& lhs, double& rhs) // get sums
{
    sumXY += (lhs * rhs);
    sumX += lhs;
    sumY += rhs;
    sumX2 += (lhs * lhs);
    sumY2 += (rhs * rhs);
    ++n;
}

double ProcFields::r_value() 				// get r and F values
{
    double r = 0.0;
    F = 0.0;
    if (n > (numPatients - 2) / 10) 		// increased the number of hits from 80 to 90% - this is just precaution
    {
        float numerat = (n * sumXY) - (sumX * sumY);
        float denom1 = ((n * sumX2) - (sumX*sumX)) * ((n * sumY2) - (sumY*sumY));
        float denom2 = sqrt(denom1);
        r = numerat / denom2;
        F = (r*r*(n-2)) / (1-r*r);
    }
    else
    {
        r = 2.0;
    }
    return r;
}

double ProcFields::p_value() 				// get p-value
{
    double p = 0.0;
    if (F > 0.0)
    {
        fisher_f dist(1, n-2);
        p = cdf(complement(dist, F));
    }
    else
    {
        p = 1.0;
    }
    return p;
}

int ProcFields::readRows()
{
    string str3; 							// temp string
    ifstream f1 (filename.c_str());
    if (f1.is_open())
    {
        while (f1.good())
        {
            string str1 = "";
            getline(f1, str1);
            size_t found = str1.find(str2); // find GeneSymbol
            if (found != string::npos)
            {
                istringstream iss1(str1);
                while (iss1 >> str3)
                {
                    ++numPatients;
                    v1.push_back(str3);
                }
            }
            istringstream iss2(str1);
            while (iss2 >> str3)
            {
                if (str3 == "0") str3 = "0.00";
                v1.push_back(str3);
            }
        }
    }
    else
    {
        cerr << "could not open file " << filename << '\n';
        return 1;
    }
    auto check1 = isInt(v1.size() / numPatients);
    if (check1 == 0)
    {
        cerr << "Invalid number of data" << endl;
        return 1;
    }
    f1.close();
    return EXIT_SUCCESS;
}

int ProcFields::readGeVal2()
{
    string str3; 							// temp string
    ifstream f1 (geVal2.c_str());
    if (f1.is_open())
    {
        while (f1.good())
        {
            string str1;
            getline(f1, str1);
            size_t found = str1.find(str2); // find GeneSymbol
            if (found != string::npos)
            {
                istringstream iss1(str1);
                while (iss1 >> str3)
                {
                    ++numPatients2;
                }
            }
            istringstream iss2(str1);
            while (iss2 >> str3)
            {
                v3.push_back(str3);
            }
        }
    }
    else
    {
        cerr << "could not open file " << geVal2 << '\n';
        return EXIT_FAILURE;
    }
    auto check1 = isInt(v1.size() / numPatients);
    if (check1 == 0)
    {
        cerr << "Invalid number of data" << endl;
        return EXIT_FAILURE;
    }
    f1.close();
    return EXIT_SUCCESS;
}

int ProcFields::regrPair() 				// Correlates expression between two genes - output = patient - gene1 - gene2 (geVal2 is gene2)
{
    vector<string>::iterator it1, it2, it3;
    it1 = find(v1.begin(), v1.end(), str2);
    it2 = find(v1.begin(), v1.end(), gene1);
    it3 = find(v1.begin(), v1.end(), geVal2);
    int counter = numPatients;
    int boundary = 0;
    size_t pos1 = filename.find_last_of("/");
    size_t pos2 = filename.find("__geneExp");
    string outName = filename.substr(pos1 + 1, (pos2 - pos1 - 1));
    string outF = outName + "_" + gene1 + "_" + geVal2 + "_expr.txt";
    ofstream outfile(outF.c_str(), ios_base::app);
    if (outfile.is_open())
    {
        if (it1 != v1.end() && it2 != v1.end() && it3 != v1.end())
        {
            while (counter > 0)
            {
                while (boundary < 2)
                {
                    if (boundary == 0)
                        outfile << *it1 << '\t' << *it2 << '\t' << *it3 << '\n';
                    ++boundary;
                    ++it1; ++it2; ++it3;
                    --counter;
                }
                double val1 = log2( stod(*it2) + 1.0);
                double val2 = log2( stod(*it3) + 1.0);
                sums(val1, val2);
                outfile << *it1 << '\t' << val1 << '\t' << val2 << '\n';
                ++it1; ++it2; ++it3;
                --counter;
            }
            double regr = r_value();
            double pval = p_value();
            outfile << "R and P" << '\t' << outName << '\t' << regr << '\t' << pval << '\n';
        }
        else
        {
            cerr << "No data to process; please check that gene symbol is correct!" << endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        cerr << "Could not open " << outF << '\n';
        return EXIT_FAILURE;
    }
    outfile.close();
    return EXIT_SUCCESS;
}

int ProcFields::geneExprOneGene(int const& choice) 	// 0 = expression of 1 gene for correlation with mutations - output = patient,gene
													// 1 = expression of 1 gene -> output
{
    multimap<string, double> mm2;
    vector<string>::iterator it1, it2;
    it1 = find(v1.begin(), v1.end(), str2);
    it2 = find(v1.begin(), v1.end(), gene1);
    int counter = numPatients;
    int boundary = 0;
    if (it1 != v1.end() && it2 != v1.end())
    {
        while (counter > 0)
        {
            while (boundary < 2)
            {
                ++boundary;
                ++it1; ++it2;
                 --counter;
            }
            double val1 = log2( stod(*it2) + 1);
            mm2.insert(make_pair((*it1).substr(0, 12), val1));
            ++it1; ++it2;
            --counter;
        }
        multimapToVec(mm2, v2);
    }
    else
    {
        cerr << "No data to process; please check that gene symbol is correct!" << endl;
        return EXIT_FAILURE;
    }
	if (choice == 1)
	{
		size_t pos1 = filename.find_last_of("/");
		size_t pos2 = filename.find("__geneExp");
		string outName = filename.substr(pos1 + 1, (pos2 - pos1 - 1));
		string outF = outName + "_" + gene1 + "_exprOne.txt";
		ofstream outfile(outF.c_str(), ios_base::app);
		if (outfile.is_open())
		{
    		for (const auto &i : v2) 
			{
   				outfile << i.first << '\t' << i.second << '\n';
    		}
		}
        else
        {
            cerr << "could not open " << outF << '\n';
            return EXIT_FAILURE;
        }
        outfile.close();
	}
//    else if (choice == 0) // just check
//    {
//        cout << gene1 << '\n';
//        for (const auto &i : v2)
//            cout << i.first << '\t' << i.second << '\n';
//    }
    return EXIT_SUCCESS;
}


//new
int ProcFields::geneExprTwoGene()
{
    multimap<string, double> mm2;
    vector<string>::iterator it1, it2;
    it1 = find(v1.begin(), v1.end(), str2);
    it2 = find(v1.begin(), v1.end(), geVal2);
    int counter = numPatients;
    int boundary = 0;
    if (it1 != v1.end() && it2 != v1.end())
    {
        while (counter > 0)
        {
            while (boundary < 2)
            {
                ++boundary;
                ++it1; ++it2;
                 --counter;
            }
            double val1 = log2( stod(*it2) + 1);
            mm2.insert(make_pair((*it1).substr(0, 12), val1));
            ++it1; ++it2;
            --counter;
        }
        multimapToVec(mm2, v4);
    }
    else
    {
        cerr << "No data to process; please check that gene symbol is correct!" << endl;
        return EXIT_FAILURE;
    }
    size_t pos1 = filename.find_last_of("/");
    size_t pos2 = filename.find("__geneExp");
    string outName = filename.substr(pos1 + 1, (pos2 - pos1 - 1));
    printGE<string, double>(v2, v4, gene1, geVal2, outName);
    return EXIT_SUCCESS;
}
//new

int ProcFields::countMuts() // Builds v4 - contains mutations - output = patient,numMutations
{
    multimap<string, double> mm1;
	vector<string>::iterator it1, it2;
	int numBlocks = v3.size() / numPatients2;
	int goOn = 2;
	while (goOn < numPatients2)
	{
		it1 = (v3.begin() + goOn);
		double sumMuts = 0.0;
		for (size_t j = 0; j < numBlocks - 1; ++j)
		{
			it2 = (v3.begin() + goOn + numPatients2*(j+1));
			sumMuts += stod(*it2);
		}
		mm1.insert(make_pair((*it1).substr(0, 12), sumMuts));
		++goOn;
	}

    multimapToVec(mm1, v4);

//    for (const auto &t : v4) {
//        cout << t.first << '\t' << t.second << '\n';
//    }
	return EXIT_SUCCESS;
}

int ProcFields::joinExprWithMuts(int const& level)
{
	sumXY = sumX = sumY = sumX2 = sumY2 = 0;
    n = 0;
	for (auto j1 : v2)
	{
		for (auto j2 : v4)
		{
			if (j1.first == j2.first)
			{
//				cout << j1.first << '\t' << j1.second << '\t' << j2.second << '\n';
				sums(j1.second, j2.second);
			}
		}
	}
	double regr = r_value();
	double pval = p_value();
    size_t pos1 = filename.find_last_of("/");
    size_t pos2 = filename.find("__geneExp");
    string outName = filename.substr(pos1 + 1, (pos2 - pos1 - 1));
    string outF;
    if (level == 0)
     {
         outF = outName + "_expr_mutsOne.txt";
     } else if (level == 1)
     {
         outF = outName + "_expr_mutsAll.txt";
     }
    ofstream outfile(outF.c_str(), ios_base::app);
    if (outfile.is_open())
    {
        if (pval < 1.0)
        {
	        outfile << outName << '\t' << gene1 << '\t' << n << '\t' << sumX/n << '\t' << sumY/n << '\t' << regr << '\t' << pval << '\n';
        }
    }
    else
    {
        cerr << "Could not open " << outF << '\n';
        return EXIT_FAILURE;
    }
    v2.clear();
    v4.clear();
    outfile.close();
	return EXIT_SUCCESS;
}

int ProcFields::regrOneToAll()
{
    size_t found = filename.find_last_of("/");
    size_t found1 = filename.find_last_of("_");
    size_t found2 = filename.find_last_of(".");
    string outF = gene1 + 
                  "_toAll_" + 
                  filename.substr(found + 1, found1 - found - 2) + 
                  "_" + 
                  filename.substr(found2 - 1);
    ofstream outfile(outF.c_str());
    if (outfile.is_open())
    {
        int numBlocks = v1.size() / numPatients;
        int numBlockGenes = numBlocks - 2;
        int goOn = 2;
        vector<string>::iterator it2, it3;
        while (goOn < numBlocks)
        {
            it2 = find(v1.begin(), v1.end(), gene1);
            it3 = (v1.begin() + numPatients * goOn);
            if (it2 != it3) 
            {
                outfile << *it2 << '\t' << *it3 << '\t' << *(it3 + 1) << '\t';
                sumXY = sumX = sumY = sumX2 = sumY2 = n = 0;
                it2 += 2;
                it3 += 2;
                int counter = numPatients - 2;
                while (counter > 0)
                {
                    auto val1 = log2( stod(*it2) + 1 );
                    auto val2 = log2( stod(*it3) + 1 );
                    if (val1 > 0.0 && val2 > 0.0) // Exclude 0 values
                        sums(val1, val2);
                    ++it2;
                    ++it3;
                    --counter;
                }
                double regr = r_value();
                double pval = p_value();
                outfile << n << '\t' << regr << '\t' << pval << '\n';
            }
            ++goOn;
        }
    }
    else
    {
        cerr << "Could not open outfile" << endl;
        return EXIT_FAILURE;
    }
    outfile.close();
    return EXIT_SUCCESS;
}

void ProcFields::getGeneList()
{
    int numBlocks = v1.size() / numPatients;
    int numBlockGenes = numBlocks - 2;
    int goOn = 2;
    vector<string>::iterator it3;
    while (goOn < numBlocks)
    {
        it3 = (v1.begin() + numPatients * goOn);
        string post = *(it3 + 1);
        geneList.emplace_back(make_pair(*it3, post));
        ++goOn;
    }
}

void ProcFields::runAllGenesVsMuts()
{
    for (const auto &i : geneList)
    {
        gene1 = i.first;
        geneExprOneGene(0);
        countMuts();
        joinExprWithMuts(1);
    }
}

