#include <iostream>
#include <fstream>
#include <ios>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <cassert>

#define TIME 20
#define DEC 0.2 
#define TIME_ITERS 10000
#define MIN_FITNESS_SCORE -9
#define OMITTED_LETTER 'J'

#define CIPHERTEXT "cipher.txt"
#define TETRAGRAM_LIST "tetragram_list.txt"


std::string decipher(std::string ciphertext, std::string key) {
    // TODO: make decipher work for odd ciphertexts
    char letter_0;
    char letter_1;
    int letter_0_idx;
    int letter_1_idx;
    int letter_0_row;
    int letter_1_row;
    int letter_0_col;
    int letter_1_col;
    int decipher_0_idx;
    int decipher_1_idx;
    std::string plaintext;

    for (int i = 0; i < ciphertext.length(); i += 2) {
        letter_0 = ciphertext[i];
        letter_1 = ciphertext[i+1];
        letter_0_idx = key.find(letter_0);
        letter_1_idx = key.find(letter_1);
        letter_0_row = letter_0_idx / 5;
        letter_1_row = letter_1_idx / 5;
        letter_0_col = letter_0_idx % 5;
        letter_1_col = letter_1_idx % 5;

        if (letter_0_row == letter_1_row) {
            if (letter_0_col == 0) {
                letter_0_col = 5;
            }
            else if (letter_1_col == 0) {
                letter_1_col = 5;
            }
            decipher_0_idx = (letter_0_row * 5) + (letter_0_col - 1);
            decipher_1_idx = (letter_1_row * 5) + (letter_1_col - 1);
            plaintext += key[decipher_0_idx];
            plaintext += key[decipher_1_idx];
        } else if (letter_0_col == letter_1_col) {
            if (letter_0_row == 0) {
                letter_0_idx += 25;
            }
            else if (letter_1_row == 0) {
                letter_1_idx += 25;
            }
            decipher_0_idx = (letter_0_idx - 5);
            decipher_1_idx = (letter_1_idx - 5);
            plaintext += key[decipher_0_idx];
            plaintext += key[decipher_1_idx];
        } else {
            decipher_0_idx = (letter_0_row * 5) + letter_1_col;
            decipher_1_idx = (letter_1_row * 5) + letter_0_col;
            plaintext += key[decipher_0_idx];
            plaintext += key[decipher_1_idx];
        }
    }

    return plaintext;
}

double fitness_score(std::string plaintext, std::unordered_map<std::string, double> &tetragrams) {
    std::string tetragram;
    double score = 0;

    for (int i = 0; i <= plaintext.length() - 4; i++) {
        tetragram = plaintext.substr(i, 4);
        std::unordered_map<std::string, double>::iterator iter = tetragrams.find(tetragram);
        if (iter == tetragrams.end()) {
            // tetragram not found in lexical
            score += MIN_FITNESS_SCORE;
        } else {
            // tetragram found in lexical
            score += iter->second;
        }
    }

    return score;
}

std::string permutate_key(std::string key) {
    int letter_0_idx = std::rand() % 25;
    int letter_1_idx = std::rand() % 25;
    char letter_holder; 

    letter_holder = key[letter_0_idx];
    key[letter_0_idx] = key[letter_1_idx];
    key[letter_1_idx] = letter_holder;

    return key;
}

std::string switch_rows_key(std::string key) {
    int letter_0_row = std::rand() % 5;
    int letter_1_row = std::rand() % 5;
    char letter_holder;

    for (int i = 0; i < 5; i++) {
        letter_holder = key[(letter_0_row * 5) + i];
        key[(letter_0_row * 5) + i] = key[(letter_1_row * 5) + i];
        key[(letter_1_row * 5) + i] = letter_holder;
    }

    return key;
}

std::string switch_cols_key(std::string key) {
    int letter_0_col = std::rand() % 5;
    int letter_1_col = std::rand() % 5;
    char letter_holder;

    for (int i = 0; i < 5; i++) {
        letter_holder = key[(i * 5) + letter_0_col];
        key[(i* 5) + letter_0_col] = key[(i * 5) + letter_1_col];
        key[(i* 5) + letter_1_col] = letter_holder;
    }

    return key;
}

std::string change_key(std::string key) {
    std::string new_key;
    int rand_num = rand() % 25;
    switch (rand_num) {
        case 0:
            new_key = switch_rows_key(key);
            break;
        case 1:
            new_key = switch_cols_key(key);
            break;
        default:
            new_key = permutate_key(key);
    }
    return new_key;
}

int main(int argc, char *argv[]) {
    char ch;
    double old_score;
    double new_score;
    unsigned int iteration = 0;
    double best_score = -99e99;
    double prev_best_score = best_score;
    std::string ciphertext;
    std::string old_key;
    std::string new_key;
    std::string best_key("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::string plaintext;
    std::string best_text;
    std::ifstream fin(CIPHERTEXT, std::ifstream::in);
    std::ifstream ftetra(TETRAGRAM_LIST, std::ifstream::in);
    std::ofstream results("results.txt", std::ofstream::trunc);
    std::unordered_map<std::string, double> tetragrams;
    
    // set random seed
    std::srand(time(NULL));
    
    // store ciphertext
    while (fin >> std::noskipws >> ch) {
        if (ch == '\n') {
            continue;
        }
        ciphertext += ch;
    }

    // remove omitted letter from key (usually 'J' or 'Q')
    best_key.erase(std::remove(best_key.begin(), best_key.end(), OMITTED_LETTER), best_key.end());

    // populate tetragram map with tetragram occurrences in English
    std::string tetragram;
    double occurrences;
    while (ftetra >> tetragram >> occurrences) {
        tetragrams[tetragram] = occurrences;
    }
    
    old_key.assign(best_key);
    new_key.assign(best_key);

    while (1) {
        iteration++;
        plaintext = decipher(ciphertext, best_key);
        best_score = fitness_score(plaintext, tetragrams);
        old_score = best_score;
        for (double time = TIME; time >= 0; time -= DEC) {
            for (int count = 0; count <= TIME_ITERS; count++) {
                new_key = change_key(old_key);
                plaintext = decipher(ciphertext, new_key);
                new_score = fitness_score(plaintext, tetragrams);
                if (new_score > old_score) {
                    old_key.assign(new_key);
                    old_score = new_score;
                    if (new_score > best_score) {
                        best_key.assign(new_key);
                        best_score = new_score;
                        best_text.assign(plaintext);
                    }

                } else {
                    double probability = exp((new_score - old_score) / time) * 100;
                    double rand_num = (double) (rand() % 101);
                    if (probability >= rand_num) {
                        old_key.assign(new_key);
                        old_score = new_score;
                    }
                }
            }
        }
        if (best_score > prev_best_score) {
            results << "Iteration: " << iteration << '\n';
            results << "Best Score: " << best_score << '\n';
            results << "Best Key: " << best_key << "\n";
            results << "Text: " << best_text << "\n\n\n\n";
            results.flush();
            prev_best_score = best_score;
        }
    }

    fin.close();
    ftetra.close();
    results.close();

    return 0;
}
