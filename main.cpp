#include <iterator>
#include <string>
#include "word.hpp"

void assembly_number_test() {
    std::cout << "========== Assembly numbers ==========" << '\n';
    word_t word_4 = first_double_occurrence_word(4);

    do {
        std::cout << word_4 << '\n';
        std::cout << assembly_number(word_4).first << '\n';
    } while (next_in_ascending_order(word_4));
}

void minimal_realization_test() {
    std::cout << "========== Minimal realization ==========" << '\n';
    for (int i = 1; i <= 3; ++i) {
        auto [rmin, realization] = minimal_realization_number_and_its_realization(i);
        std::cout << i << ' ' << rmin << '\n';
        draw_as_graph(realization, "minimal_realization_" + std::to_string(i));
    }
}

void assembly_numbers_for_palindromes_test() {
    std::cout << "========== Assembly numbers for palindroms ==========" << '\n';
    for (int i = 1; i <= 6; ++i) {
        int mx = 0;
        word_t word = first_double_occurrence_word(i);

        do {
            mx = std::max(mx, assembly_number(word).first);
        } while (next_palindrome(word));

        std::cout << i << ' ' << mx << '\n';
    }
}

void assembly_numbers_for_semi_palindromes_test() {
    std::cout << "========== Assembly numbers for semi-palindroms ==========" << '\n';
    for (int i = 15; i <= 15; ++i) {
        std::vector<word_t> result = all_semi_palindromes(i);
        int mx = 0;
        for (auto& word : result) {
            int an = assembly_number(word).first;
            mx = std::max(mx, an);
        }
        for (auto& word : result) {
            int an = assembly_number(word).first;
            if (an == mx) {
                draw_as_graph(word, "semi_palindrome_len_" + std::to_string(i) + "_an_" + std::to_string(an));
                break;
            }
        }

        std::cout << i << ' ' << mx << std::endl;
    }
}

void draw_all_semi_palindromes_len(int len) {
    std::cout << "========== draw_all_semi_palindromes_len ==========" << '\n';
    std::vector<word_t> result = all_semi_palindromes(len);

    for (int i = 0; i < std::ssize(result); ++i) {
        draw_as_graph(result[i], "semi_palindrome_len_7_" + std::to_string(i));
    }
}

void calculate_semi_palindromes_test(const int N = 6) {
    std::cout << "========== Amount of different semi-palindroms ==========" << '\n';

    std::vector<int> all(N + 1), irr(N + 1), str_irr(N + 1);
    for (int i = 1; i <= N; ++i) {
        std::vector<word_t> result = all_semi_palindromes(i);
        for (auto& word : result) {
            ++all[i];
            irr[i] += is_irreducible(word);
            str_irr[i] += is_strongly_irreducible(word);
        }
    }

    std::cout << "All semi-palindroms: " << all << '\n';
    std::cout << "Irreducible semi-palindroms: " << irr << '\n';
    std::cout << "Strongly irreducible semi-palindroms: " << str_irr << '\n';
    //            All semi-palindroms:                  0 1 2 3 6 10 20 35
    //            Irreducible semi-palindroms:          0 1 1 2 3 6  10 20
    //            Strongly irreducible semi-palindroms: 0 1 1 2 3 6  10 20
    //            https://oeis.org/search?q=1%2C+2%2C+3%2C+6%2C+10%2C+20%2C+35&language=english&go=Search
}

void calculate_palindromes_test(const int N = 6) {
    std::cout << "========== Amount of different palindroms ==========" << '\n';

    std::vector<int> all(N + 1), irr(N + 1), str_irr(N + 1);
    for (int i = 1; i <= N; ++i) {
        word_t word = first_double_occurrence_word(i);
        do {
            ++all[i];
            irr[i] += is_irreducible(word);
            str_irr[i] += is_strongly_irreducible(word);
        } while (next_palindrome(word));
    }

    std::cout << "All palindroms: " << all << '\n';
    std::cout << "Irreducible palindroms: " << irr << '\n';
    std::cout << "Strongly irreducible palindroms: " << str_irr << '\n';
}

void check_recursive_semi_palindrome_test(const int N = 4) {
    std::cout << "========== check_recursive_semi_palindrome_test ==========" << '\n';

    for (int i = 1; i <= N; ++i) {
        int am = 0;
        word_t word = first_double_occurrence_word(i);
        do {
            am += 1;
            std::cout << word << '\n';
        } while (next_semi_palindrome(word));
        std::cout << am << '\n';

        std::vector<word_t> result = all_semi_palindromes(i);
        for (auto& e : result) {
            std::cout << e << '\n';
        }
        std::cout << result.size() << '\n';
        std::cout << '\n';
    }
}

int main() {
    // assembly_number_test();
    // minimal_realization_test();
    // assembly_numbers_for_palindromes_test();
    // assembly_numbers_for_semi_palindromes_test();
    // calculate_semi_palindromes_test(10);
    // calculate_palindromes_test();
    // check_recursive_semi_palindrome_test(6);
    // draw_all_semi_palindromes_len(7);

    word_t word;
    std::cin >> word;
    draw_as_graph(word, "graph", true);
}
