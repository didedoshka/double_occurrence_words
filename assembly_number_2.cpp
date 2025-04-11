#include "word.hpp"

void semi_palindrome_with_assembly_number_2() {
    std::cout << "========== Semi-palindrome with assembly number 2 ==========" << '\n';
    for (int i = 1;; ++i) {
        std::vector<word_t> result = all_semi_palindromes(i);
        int mx = 0;
        for (auto& word : result) {
            int an = assembly_number(word).first;
            if (an == 2) {
                std::cout << "Len of shortest semi-palindrome with assembly number 2 is " << i << '\n';
                draw_as_graph(word, "semi_palindrome_len_" + std::to_string(i) + "_an_" + std::to_string(an));
                return;
            }
        }
    }
}

int main() {
    semi_palindrome_with_assembly_number_2();
}
