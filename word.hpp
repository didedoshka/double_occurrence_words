#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <set>

using word_t = std::vector<int>;

inline std::string to_string(const word_t& word) {
    std::string result;
    for (auto& i : word) {
        result += std::to_string(i) += ' ';
    }
    return result;
}

inline std::ostream& operator<<(std::ostream& os, const word_t& word) {
    for (auto& i : word) {
        os << i << ' ';
    }
    return os;
}

// Reads a line, containing a word
inline std::istream& operator>>(std::istream& is, word_t& word) {
    std::string line;
    std::getline(is, line);
    std::istringstream ss(line);

    word = word_t(std::istream_iterator<int>(ss), std::istream_iterator<int>());
    return is;
}

inline bool is_double_occurrence_word(const word_t& word) {
    std::map<int, int> m;
    for (auto i : word) {
        ++m[i];
        if (m[i] > 2) {
            return false;
        }
    }
    for (auto [k, v] : m) {
        if (v != 2) {
            return false;
        }
    }

    return true;
}

inline word_t to_ascending_order(const word_t& word) {
    word_t result(word.size());

    std::map<int, int> m;

    for (int i = 0; i < std::ssize(word); ++i) {
        if (!m.contains(word[i])) {
            m[word[i]] = m.size() + 1;
        }

        result[i] = m[word[i]];
    }

    return result;
}

inline bool is_in_ascending_order(const word_t& word) {
    word_t in_ascending_order = to_ascending_order(word);

    return word == in_ascending_order;
}

inline word_t reverse(const word_t& word) {
    word_t result = word;
    std::reverse(result.begin(), result.end());
    return result;
}

// Expects word in ascending order
inline bool is_palindrome(const word_t& word) {
    return word == to_ascending_order(reverse(word));
}

// Expects double occurrence words in any order
inline bool equal_as_double_occurrence_words(const word_t& lhs, const word_t& rhs) {
    return to_ascending_order(lhs) == to_ascending_order(rhs);
}

inline int len(const word_t& word) {
    return word.size() / 2;
}

// Expects word in ascending order
inline bool is_semi_palindrome(const word_t& word) {
    for (int i = 0; i < std::ssize(word); ++i) {
        if (len(word) - word[i] + 1 != word[std::ssize(word) - i - 1]) {
            return false;
        }
    }

    return true;
}

inline bool is_reducible(const word_t& word) {
    for (int i = 2; i <= std::ssize(word) - 2; i += 2) {
        if (is_double_occurrence_word(word_t(word.begin(), word.begin() + i)) &&
            is_double_occurrence_word(word_t(word.begin() + i, word.end()))) {
            return true;
        }
    }

    return false;
}

inline bool is_irreducible(const word_t& word) {
    return !is_reducible(word);
}

inline bool is_strongly_reducible(const word_t& word) {
    for (int i = 0; i < std::ssize(word); ++i) {
        for (int j = i + 1; j < std::ssize(word); ++j) {
            if (is_double_occurrence_word(word_t(word.begin() + i, word.begin() + j))) {
                return true;
            }
        }
    }

    return false;
}

inline bool is_strongly_irreducible(const word_t& word) {
    return !is_strongly_reducible(word);
}

inline bool next_in_ascending_order(word_t& word) {
    do {
        bool is_last = !std::next_permutation(word.begin(), word.end());
        if (is_last) {
            return false;
        }
    } while (!is_in_ascending_order(word));

    return true;
}

inline bool next_palindrome(word_t& word) {
    do {
        bool is_last = !next_in_ascending_order(word);
        if (is_last) {
            return false;
        }
    } while (!is_palindrome(word));

    return true;
}

inline bool next_semi_palindrome(word_t& word) {
    do {
        bool is_last = !next_in_ascending_order(word);
        if (is_last) {
            return false;
        }
    } while (!is_semi_palindrome(word));

    return true;
}

inline word_t first_double_occurrence_word(int n) {
    word_t word(2 * n);
    for (int i = 0; i < n; ++i) {
        word[2 * i] = i + 1;
        word[2 * i + 1] = i + 1;
    }
    return word;
}

namespace detail {

class dcu_t {
public:
    dcu_t(int n) : p(n + 1), s(n + 1, 1) {
        std::iota(p.begin(), p.end(), 0);
    }

    int leader(int v) {
        return (p[v] == v) ? v : p[v] = leader(p[v]);
    }

    void unite(int a, int b) {
        a = leader(a), b = leader(b);
        if (s[a] > s[b]) {
            std::swap(a, b);
        }
        s[b] += s[a];
        p[a] = b;
    }

private:
    std::vector<int> p, s;
};

inline int get_ans(const word_t& word, const std::vector<int>& v) {
    // std::cout << v << '\n';
    dcu_t dcu(len(word));

    for (auto i : v) {
        if (dcu.leader(word[i]) == dcu.leader(word[i + 1])) {
            return INT_MAX;
        }
        dcu.unite(word[i], word[i + 1]);
    }

    std::set<int> s;
    for (int i = 1; i <= len(word); ++i) {
        s.insert(dcu.leader(i));
    }
    return std::ssize(s);
}

inline std::pair<int, std::vector<int>> recursive(const word_t& word, int i, std::vector<int>& v) {
    int result = get_ans(word, v);
    std::vector<int> result_v = v;

    if (i >= std::ssize(word) - 1) {
        return {result, v};
    }

    for (int j = 0; i + j <= std::ssize(word) - 2; ++j) {
        v.push_back(i + j);
        auto [new_res, new_res_v] = recursive(word, i + j + 2, v);
        if (new_res < result) {
            std::tie(result, result_v) = {new_res, new_res_v};
        }
        v.pop_back();
    }

    return {result, result_v};
}

}  // namespace detail

// Expects word in ascending order
inline std::pair<int, std::vector<int>> assembly_number(const word_t& word) {
    std::vector<int> v;
    return detail::recursive(word, 0, v);
}

inline std::pair<int, word_t> minimal_realization_number_and_its_realization(int k) {
    for (int i = 1; i < 100; ++i) {
        word_t word = first_double_occurrence_word(i);

        do {
            if (assembly_number(word).first == k) {
                return {i, word};
            }
        } while (next_in_ascending_order(word));
    }
    return {-1, {}};
}

inline int minimal_realization_number(int k) {
    return minimal_realization_number_and_its_realization(k).first;
}

inline std::string get_data(const word_t& word, bool calculate_assembly_number = false, bool escape = false) {
    std::string endl = escape ? "\\n" : "\n";
    std::string result = to_string(word) + endl;
    bool idow = is_double_occurrence_word(word);
    if (!idow) {
        result += "Not a double occurrence word" + endl;
        return result;
    }
    result += "A double occurrence word" + endl;
    word_t tao = to_ascending_order(word);
    if (tao == word) {
        result += "Already in ascending order" + endl;
    } else {
        result += "Ascending order " + to_string(tao) + endl;
    }

    result += "Palindrome: " + std::string(is_palindrome(tao) ? "yes" : "no") + endl;
    result += "Semi-palindrome: " + std::string(is_semi_palindrome(tao) ? "yes" : "no") + endl;
    result += "Irreducible: " + std::string(is_irreducible(tao) ? "yes" : "no") + endl;
    result += "Strongly-irreducible: " + std::string(is_strongly_irreducible(tao) ? "yes" : "no") + endl;
    if (calculate_assembly_number) {
        auto [an, an_v] = assembly_number(word);
        result += "Assembly number: " + std::to_string(an) + endl;
        // result += "Edges in Hamiltonion set of polygonal paths: " + to_string(an_v) + endl;
        if (an == 1) {
            result += "Realizable" + endl;
        } else {
            result += "Unrealizable" + endl;
        }
    }

    return result;
}

// Expects double occurrence word
inline void draw_as_graph(const word_t& word, std::string graph_name, bool calculate_assembly_number = true) {
    std::ofstream dot("data/" + graph_name + ".dot");
    dot << "digraph {\nfontname=\"Helvetica\"\nnode [fontname=\"Helvetica\"]\nnode [shape=diamond]\nlabel=\""
        << get_data(word, calculate_assembly_number, true) << "\"\n";

    dot << "a [style=\"invis\"]\nb [style=\"invis\"]\n";
    dot << "a";
    dot << ":s";
    dot << " -> ";

    std::map<int, bool> m;

    bool w = true;

    auto [an, an_v] = assembly_number(word);

    for (int i = 0; i < std::ssize(word); ++i) {
        dot << word[i];

        dot << ":";
        if (m[word[i]]) {
            if (w) {
                dot << "w";
            } else {
                dot << "e";
            }
        } else {
            dot << "n";
        }

        if (std::find(an_v.begin(), an_v.end(), i - 1) != an_v.end()) {
            dot << " [color=\"blue\"]";
        }

        dot << "\n";

        dot << word[i];

        dot << ":";
        if (m[word[i]]) {
            if (w) {
                dot << "e";
            } else {
                dot << "w";
            }
            w = !w;
        } else {
            dot << "s";
        }

        dot << " -> ";

        m[word[i]] = true;
    }

    dot << "b:n\n";
    dot << "}\n";
    dot.close();

    std::string dot_exec = "dot -Tsvg data/" + graph_name + ".dot -o data/" + graph_name + ".svg";
    // std::cout << dot_exec << '\n';
    system(dot_exec.c_str());
}

namespace detail {

inline void recursive_semi_palindomes(int n, int bal, std::vector<bool>& cur, std::vector<word_t>& result) {
    if (cur.size() == n) {
        word_t to_push(2 * n);
        int opening = 0;
        int closing = 0;
        for (int i = 0; i < n; ++i) {
            if (cur[i]) {
                ++closing;
                to_push[i] = closing;
            } else {
                ++opening;
                to_push[i] = opening;
            }
            to_push[2 * n - i - 1] = n - to_push[i] + 1;
        }
        result.push_back(std::move(to_push));
        return;
    }

    if (bal != 0) {
        cur.push_back(1);
        recursive_semi_palindomes(n, bal - 1, cur, result);
        cur.pop_back();
    }

    cur.push_back(0);
    recursive_semi_palindomes(n, bal + 1, cur, result);
    cur.pop_back();
}

}  // namespace detail

inline std::vector<word_t> all_semi_palindromes(int n) {
    std::vector<bool> cur;
    std::vector<word_t> result;
    detail::recursive_semi_palindomes(n, 0, cur, result);
    return result;
}
