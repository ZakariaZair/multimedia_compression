#include "explorer.h"
#include <vector>

int main() {
    std::vector<const char*> filenames {
        "data/accumulation-accounts-2008-2023-provisional.csv",
        "data/annual-enterprise-survey-2024-financial-year-provisional.csv",
        "data/code1.py",
        "data/code2.html",
        "data/code3.css",
        "data/industry-2018-census-csv.csv",
        "data/languages-spoken-total-responses-2018-census-csv.csv",
        "data/text1_natural_1.txt",
        "data/text1_natural_3.txt",
        "data/text1_natural_4.txt",
        "data/text1_natural_5.txt"
    };

    Explorer dataExplorer = Explorer();
    for (int i = 0; i < filenames.size(); i++) {
        dataExplorer.explore(filenames[i]);
        dataExplorer.draw();
    }
}
