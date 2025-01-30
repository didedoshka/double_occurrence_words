#include "word.hpp"

void assembly_number_test() {
    std::cout << "========== Assembly numbers ==========" << '\n';
    word_t word_4 = first_double_occurrence_word(4);

    do {
        std::cout << word_4 << '\n';
        std::cout << assembly_number(word_4) << '\n';
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
            mx = std::max(mx, assembly_number(word));
        } while (next_palindrome(word));

        std::cout << i << ' ' << mx << '\n';
    }
}

void assembly_numbers_for_semi_palindromes_test() {
    std::cout << "========== Assembly numbers for semi-palindroms ==========" << '\n';
    for (int i = 1; i <= 6; ++i) {
        int mx = 0;
        word_t word = first_double_occurrence_word(i);

        do {
            int an = assembly_number(word);
            if (an != 1) {
                draw_as_graph(word, "semi_palindrome_an_2", true);
            }
            mx = std::max(mx, an);
        } while (next_semi_palindrome(word));

        std::cout << i << ' ' << mx << '\n';
    }
}

void calculate_semi_palindromes_test(const int N = 6) {
    std::cout << "========== Amount of different semi-palindroms ==========" << '\n';

    std::vector<int> all(N + 1), irr(N + 1), str_irr(N + 1);
    for (int i = 1; i <= N; ++i) {
        word_t word = first_double_occurrence_word(i);
        do {
            ++all[i];
            if (is_reducible(word) && i == 2) {
                draw_as_graph(word, "reducible_semi_palindrome", true);
            }
            irr[i] += is_irreducible(word);
            str_irr[i] += is_strongly_irreducible(word);
        } while (next_semi_palindrome(word));
    }

    std::cout << "All semi-palindroms: " << all << '\n';
    std::cout << "Irreducible semi-palindroms: " << irr << '\n';
    std::cout << "Strongly irreducible semi-palindroms: " << str_irr << '\n';
    //            All semi-palindroms: 0 1 2 3 6 10 20 35
    //            Irreducible semi-palindroms: 0 1 1 2 3 6 10 20
    //            Strongly irreducible semi-palindroms: 0 1 1 2 3 6 10 20
    //            https://oeis.org/search?q=1%2C+2%2C+3%2C+6%2C+10%2C+20%2C+35&language=english&go=Search
}

int main() {
    // assembly_number_test();
    // minimal_realization_test();
    // assembly_numbers_for_palindromes_test();
    // assembly_numbers_for_semi_palindromes_test();
    calculate_semi_palindromes_test();

    word_t word;
    std::cin >> word;
    draw_as_graph(word, "graph", true);
}
