
# pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
using namespace std;

int multimapToVec(multimap<string, double>& multim, vector<pair<string, double>>& vec0)
{
    vec0.clear();
    multimap<string, double>::iterator m_it, s_it;
    for (m_it = multim.begin(); m_it != multim.end(); m_it = s_it)
    {
        double j = 0.0;
        double n = 0.0;
        string theKey = (*m_it).first;
//        cout << '\n';
//        cout << " key = '" << theKey << "'" << '\n';
        pair<multimap<string, double>::iterator, multimap<string, double>::iterator> keyRange = multim.equal_range(theKey);

        for (s_it = keyRange.first; s_it != keyRange.second; ++s_it)
        {
//            cout << " value = " << (*s_it).second << '\n';
            j += (*s_it).second;
            ++n;
        }
        double res = j/n;
//        cout << " average for " << theKey << ' ' << res << '\n';
        vec0.emplace_back(theKey, res);
    }

//    for (const auto &t : vec0) {
//        cout << t.first << '\t' << t.second << '\n';
//    }

    return EXIT_SUCCESS;
}

template<typename T, typename U>
void printGE(vector<pair<T,U>> const& vec1, vector<pair<T,U>> const& vec2, T const& val1, T const& val2, T const& val3)
{
    double sum1{}, sum2{}, mean1{}, mean2{};
    string str1 = val3 + '_' + val1 + '_' + val2 + "_forKM.txt";
    ofstream outFile(str1.c_str(), ios::out);
    if (outFile.is_open())
    {
        cout << sum1 << '\t' << sum2 << '\n';
        cout << str1 << '\n';
        for (auto const& i : vec1)
        {
            sum1 += i.second;
        }

        for (auto const& j : vec2)
        {
            sum2 += j.second;
        }
        mean1 = sum1/vec1.size();
        mean2 = sum2/vec2.size();

        outFile << "Patient\t" << val1 << '\t' << val2 << "\tClass\n";
        cout << mean1 << '\t' << mean2 << '\n';

        for (auto const& l : vec1) 
        {
            for (auto const& m : vec2) 
            {
                if (l.first == m.first)
                {
                    if (l.second <= mean1 && m.second <= mean2)
                    {
                        outFile << l.first << '\t' << l.second << '\t' << m.second << "\tlow" + val1 + "_low" + val2 << '\n';
                    }
                    else if (l.second <= mean1 && m.second > mean2)
                    {
                        outFile << l.first << '\t' << l.second << '\t' << m.second << "\tlow" + val1 + "_high" + val2 << '\n';
                    }
                    else if (l.second > mean1 && m.second <= mean2)
                    {
                        outFile << l.first << '\t' << l.second << '\t' << m.second << "\thigh" + val1 + "_low" + val2 << '\n';
                    }
                    else if (l.second > mean1 && m.second > mean2)
                    {
                        outFile << l.first << '\t' << l.second << '\t' << m.second << "\thigh" + val1 + "_high" + val2 << '\n';
                    }
                }
            }
        }
    }
    else
    {
        cerr << "Could not open " << str1 << '\n';
    }
    outFile.close();
}
