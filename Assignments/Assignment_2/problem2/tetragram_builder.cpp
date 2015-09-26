#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>

#define TEXTFILE "moby_dick.txt"
#define TEXTFILE_CONVERTED "moby_dick_converted.txt"
#define TETRAGRAM_FILE "tetragram_list.txt"


struct sort_tetragrams {
    bool operator()(const std::pair<std::string, unsigned int>&left, const std::pair<std::string, unsigned int>&right) {
        return left.second > right.second;
    }
};

int main(int argc, char *argv[]) {
    char ch;
    char tetragramizer[5] = {'\0'};
    unsigned int total_tetragrams = 0;
    std::vector<char> database;
    std::map<std::string, unsigned int> tetragrams;
    database.reserve(100000);
    std::ifstream fin(TEXTFILE, std::ifstream::in); 
    std::ofstream fout(TEXTFILE_CONVERTED, std::ofstream::trunc);
    std::vector<std::pair<std::string, unsigned int> > sorted_tetragrams;
    
    // read in english story and only keep the alphabetic characters
    while (fin >> std::noskipws >> ch) {
        if (isalpha(ch)) {
            database.push_back(toupper(ch));               
        }
    }
    fin.close();

    // write the converted text containing only alphabetic text back to a file
    for(std::vector<int>::size_type i = 0; i != database.size(); i++) {
        fout << database.at(i);
        if (((i % 100000) == 0) && i != 0) {
            fout << '\n';
        }
    }
    fout.close();

    // read in the converted file again, find all the tetragrams
    fin.open(TEXTFILE_CONVERTED, std::ifstream::in);
    while (fin >> std::noskipws >> ch) {
        // Avoid new line characters
        if (ch == '\n') {
            continue;
        }
        memmove(tetragramizer, tetragramizer + 1, 3);
        tetragramizer[3] = ch;
        if (strlen(tetragramizer) < 4) {
            continue;
        }
        total_tetragrams++;
        if ((tetragrams.find(tetragramizer)) == tetragrams.end()) {
            tetragrams[tetragramizer] = 1;
        } else {
            tetragrams[tetragramizer]++;
        }
    }
    fin.close();

    // sort the tetragram map
    for (std::map<std::string,unsigned int>::iterator iter=tetragrams.begin(); iter != tetragrams.end(); iter++) {
        sorted_tetragrams.push_back(std::make_pair(iter->first, iter->second));
    }
    std::sort(sorted_tetragrams.begin(), sorted_tetragrams.end(), sort_tetragrams());

    // copy the tetragrams and their occurences to a file
    fout.open(TETRAGRAM_FILE, std::ofstream::trunc);
    for (std::vector<std::pair<std::string, unsigned int> >::iterator iter=sorted_tetragrams.begin(); iter != sorted_tetragrams.end(); iter++) {
        double log_val = log10(((double) iter->second) / ((double) total_tetragrams));
        fout << iter->first << " " << log_val << '\n';
    }
    fout.close();

    return 0;
}
