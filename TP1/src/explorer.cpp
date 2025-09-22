#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

#include "explorer.h"

Explorer::Explorer() {
    printf("INIT  > exploring... \n");
    fCount_ = 0;
}

int Explorer::explore(const char* filename) {
    frequency_.clear();
    currentFilename_ = "VOID";
    FILE* filePtr = fopen(filename, "r");

    if (filePtr == nullptr) {
        printf("ERROR > couldn't open %s\n", filename);
        return 1;
    }

    int character;
    while((character = getc(filePtr)) != EOF) frequency_[static_cast<char>(character)]++;
    currentFilename_ = filename;
    fCount_++;
    return 0;
}

#include <filesystem>

int Explorer::draw() {
    if (frequency_.empty()) {
        printf("LOG   > no frequency map to draw\n");
        return 1;
    }

    FILE* gp = popen("gnuplot", "w");
    if (!gp) { std::cerr << "gnuplot not working\n"; return 1; }

    // Clean state every time
    fprintf(gp, "reset session\n");
    fprintf(gp, "unset multiplot\n");
    fprintf(gp, "set encoding utf8\n");

    // Write to file
    fprintf(gp, "set terminal pngcairo size 800,600 noenhanced font 'Arial,10'\n");
    fprintf(gp, "set output 'out/histogram_%d.png'\n", fCount_);

    // Style
    fprintf(gp, "set style data histograms\n");
    fprintf(gp, "set style fill solid 1.0 border -1\n");
    fprintf(gp, "set boxwidth 0.8\n");
    fprintf(gp, "set yrange [0:*]\n");

    // Use double quotes for title to avoid issues if filename has apostrophes
    fprintf(gp, "set title \"Histogram - %s\"\n", currentFilename_);
    fprintf(gp, "set xlabel 'Category'\n");
    fprintf(gp, "set ylabel 'Frequency'\n");
    fprintf(gp, "set xtics font ',7' rotate by -45 offset 0,-0.5\n");

    // Data: col1=label (string), col2=value
    fprintf(gp, "plot '-' using 2:xtic(1) with histograms title 'Data'\n");
    for (auto it = frequency_.begin(); it != frequency_.end(); ++it) {
        fprintf(gp, "'%c' %d\n", it->first, it->second);
    }
    fprintf(gp, "e\n");

    // Finish file cleanly
    fprintf(gp, "unset output\n");
    fflush(gp);
    pclose(gp);
    return 0;
}



int Explorer::print() {
    if (frequency_.empty()) {
        printf("LOG   > no frequency map to print\n");
        return 1;
    }

    for (auto it = frequency_.begin(); it != frequency_.end(); ++it) {
        printf("{%c,%d} \n", it->first, it->second);
    }
    return 0;
}
