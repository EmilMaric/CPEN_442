#include <boost/crc.hpp>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>



unsigned int get_crc_32(const std::string& str) {
    boost::crc_32_type  crc;
    crc.process_bytes( str.data(), str.size() );
    return crc.checksum();
}

void get_next_str(std::vector<char> &str) {
    std::string alpha_numeric =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    bool carry = true;
    for (int i = str.size() - 1; (i >= 0) && carry; i--) {
        unsigned int char_val = alpha_numeric.find(str[i]);
        char_val++;
        if (char_val >= alpha_numeric.length() - 1) {
            char_val = 0;
            carry = true;
        } else {
            carry = false;
        }
        str[i] = alpha_numeric[char_val];
    }
    if (carry) {
        str.insert(str.begin(), '0');
    }
}

int main(int argc, char *argv[]) {
    std::vector<char> v_str;
    std::string str;
    unsigned int checksum;
    std::unordered_map<unsigned int, std::string> crc_values;

    v_str.insert(v_str.begin(), '0');

    while (1) {
        str.assign(v_str.begin(), v_str.end());
        checksum = get_crc_32(str);
        if (crc_values.find(checksum) == crc_values.end()) {
            crc_values[checksum] = str;
        } else {
            break;
        }
        get_next_str(v_str);
    }

    std::cout << "x: " << str << std::endl;
    std::cout << "y: " << crc_values[checksum] << std::endl;
    std::cout << "CHECKSUM: " << std::hex << checksum << std::endl;

    return 0;
}
