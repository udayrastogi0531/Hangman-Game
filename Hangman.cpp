// Hangman game with Trie-based hints and leaderboard heap
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <vector>

using namespace std;

const int MAX_LIST = 100;
const int MAX_SIZE = 100;

// Trie implementation for hint system
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; ++i)
            children[i] = nullptr;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index])
                node->children[index] = new TrieNode();
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    void suggestWordsWithPrefix(TrieNode* node, string current, vector<string>& suggestions, int limit) {
        if (suggestions.size() >= limit) return;
        if (node->isEndOfWord)
            suggestions.push_back(current);
        for (int i = 0; i < 26; ++i) {
            if (node->children[i])
                suggestWordsWithPrefix(node->children[i], current + char('a' + i), suggestions, limit);
        }
    }

    vector<string> getSuggestions(const string& prefix, int limit = 5) {
        TrieNode* node = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!node->children[index])
                return {};
            node = node->children[index];
        }
        vector<string> suggestions;
        suggestWordsWithPrefix(node, prefix, suggestions, limit);
        return suggestions;
    }
};

// Score entry for leaderboard
struct ScoreEntry {
    string word;
    int score;
    bool operator<(const ScoreEntry& other) const {
        return score < other.score; // max-heap
    }
};

void welcomeMessage();
void readWord(const int, ifstream&, string[]);
void writeFile(ofstream&, const int[], const string[], int);
int wordLetters(const string[], char[], const int);
int hangmanFigure(int, const string[], int);
int guessLetters(const string[], char[], int&, Trie&);

int main() {
    string words[MAX_SIZE];
    unsigned seed = time(0);
    srand(seed);

    welcomeMessage();

    ifstream inputFile("WordList.txt");
    if (!inputFile) {
        cout << "Error! Couldn't open the word list! Game Crashed!!\n";
        return 1;
    }

    int word_index, game_score, try_index = 0;
    char blank_for_word[MAX_SIZE];
    int score_list[MAX_LIST];
    string words_list[MAX_LIST];
    char option;

    readWord(MAX_LIST, inputFile, words);
    inputFile.close();

    // Build Trie for hints
    Trie trie;
    for (int i = 0; i < MAX_LIST && !words[i].empty(); ++i)
        trie.insert(words[i]);

    do {
        word_index = wordLetters(words, blank_for_word, MAX_LIST);
        game_score = guessLetters(words, blank_for_word, word_index, trie);

        cout << "\nDo you want to play again (press y or Y)? ";
        cin >> option;
        system("cls");

        words_list[try_index] = words[word_index];
        score_list[try_index] = game_score;
        try_index++;

    } while (option == 'y' || option == 'Y');

    ofstream outputFile("scores.txt");
    writeFile(outputFile, score_list, words_list, try_index);
    outputFile.close();

    // Leaderboard using heap
    priority_queue<ScoreEntry> leaderboard;
    for (int i = 0; i < try_index; ++i)
        leaderboard.push({words_list[i], score_list[i]});

    cout << "\n\n=== Leaderboard (Top Scores) ===\n";
    int rank = 1;
    while (!leaderboard.empty() && rank <= 5) {
        ScoreEntry entry = leaderboard.top();
        leaderboard.pop();
        cout << rank++ << ". " << entry.word << " - Score: " << entry.score << "\n";
    }

    return 0;
}

void welcomeMessage() {
    char ch;
    cout << "\t\t\t~~~~~~WELCOME TO HANGMAN!!!~~~~~~\n\n\n";
    cout << "\t\tRules of the game:-\n";
    cout << "\t1. Guess letters of a word shown as blanks.\n";
    cout << "\t2. Each wrong guess adds to the hangman.\n";
    cout << "\t3. When the figure is complete, you lose!\n\n";
    cout << "\tScoring system:\n";
    cout << "\t✔ Correct guess: +1 point\n";
    cout << "\t✘ Wrong guess: -1 point\n";
    cout << "\t✔ Full word guessed: +2 points\n";
    cout << "\t✔ No wrong guesses: +3 bonus points\n";
    cout << "\n\tPress Y to start: ";
    cin >> ch;
    if (ch == 'Y') system("cls");
}

void readWord(const int MAX_LIST, ifstream& inputFile, string words[]) {
    int i = 0;
    while (i < MAX_LIST && getline(inputFile, words[i])) i++;
}

int wordLetters(const string words[], char blank_for_word[], const int MAX_LIST) {
    int random_word = rand() % 12;
    for (int blanks = 0; blanks < words[random_word].length(); blanks++) {
        blank_for_word[blanks] = '_';
        cout << blank_for_word[blanks] << " ";
    }
    return random_word;
}

int guessLetters(const string words[], char blank_for_word[], int& word_index, Trie& trie) {
    char letter;
    int i = 0, wrong_choice = 0;
    int score = 0, rounded_score = 0;
    const int MAX_GUESS = 26;

    while (i < MAX_GUESS) {
        cout << "\n\nEnter a letter to guess: ";
        cin >> letter;

        int search_letter = 0, count_letter = 0;
        bool found_letter = false;

        while (search_letter < words[word_index].length()) {
            if (blank_for_word[search_letter] == letter)
                score--;
            if (words[word_index][search_letter] == letter) {
                blank_for_word[search_letter] = letter;
                found_letter = true;
                score++;
            }
            search_letter++;
        }
        i++;

        int j = 0;
        while (j < words[word_index].length()) {
            if (blank_for_word[j] != '_') count_letter++;
            j++;
        }

        system("cls");
        for (int k = 0; k < words[word_index].length(); ++k)
            cout << blank_for_word[k] << " ";

        if (!found_letter) {
            cout << "\n\nWrong letter!\n";
            wrong_choice++;
            score--;
        }

        // Show hint after 3 wrong guesses
        if (wrong_choice == 3) {
            string prefix = "";
            for (int j = 0; j < words[word_index].length(); ++j) {
                if (blank_for_word[j] != '_')
                    prefix += blank_for_word[j];
                else break;
            }
            vector<string> hints = trie.getSuggestions(prefix);
            if (!hints.empty()) {
                cout << "\nHint! Words starting with '" << prefix << "': ";
                for (string s : hints)
                    cout << s << " ";
                cout << "\n";
            }
        }

        cout << "\n\nHANGMAN FIGURE DISPLAY\n";
        int check = hangmanFigure(wrong_choice, words, word_index);

        rounded_score = static_cast<double>(score) / words[word_index].length() * 10;

        if (count_letter == words[word_index].length() && check == 0) {
            cout << "\nYou guessed the word!";
            rounded_score += 2;
            if (wrong_choice == 0) {
                cout << "\nCONGRATS ON FIRST TRY!!";
                rounded_score += 3;
            }
            break;
        } else if (check == -1) {
            if (rounded_score < 0) rounded_score = 0;
            break;
        }
    }

    cout << "\nYour score is: " << rounded_score << "/10";
    return rounded_score;
}

int hangmanFigure(int wrong_choice, const string words[], int word_index) {
    char head = 'O', left_body = '/', right_body = '\\', body = '|';
    if (wrong_choice > 0)
        cout << "\t\t " << head << endl;
    if (wrong_choice == 2)
        cout << "\t\t " << body;
    else if (wrong_choice > 2)
        cout << "\t\t" << left_body << body;
    if (wrong_choice > 3)
        cout << right_body << endl;
    if (wrong_choice > 4)
        cout << "\t\t" << left_body;
    if (wrong_choice > 5)
        cout << " " << right_body;
    if (wrong_choice > 6) {
        cout << "\n\nGAME OVER!!";
        cout << "\nThe word was: " << words[word_index];
        return -1;
    }
    return 0;
}

void writeFile(ofstream& outputFile, const int score_list[], const string words_list[], int try_index) {
    for (int i = 0; i < try_index; ++i)
        outputFile << words_list[i] << ": " << score_list[i] << endl;
}
