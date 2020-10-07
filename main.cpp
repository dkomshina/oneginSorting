#include <vector>
#include <fstream>
#include <string>

using namespace std;

/**
 * Сравнивает строки посимвольно, начиная с начала строки,
 * игнорирует пунктуацию и пробелы
 * @param s1 - первая строка
 * @param s2 = вторая строка
 * @return true - если первая строка меньше второй, false - иначе
 */
bool comparisonWithoutPunctuation(const string& s1, const string& s2) {
    int i = 0;
    int j = 0;
    while (i < s1.length() || j < s2.length()) {
        while (ispunct(s1[i]) || isspace(s1[i])) {
            i++;
        }
        while (ispunct(s2[j]) || isspace(s2[j])) {
            j++;
        }
        if (tolower(s1[i]) == tolower(s2[j])) {
            i++;
            j++;
            continue;
        }
        return tolower(s1[i]) < tolower(s2[j]);
    }
    return false;
}

/**
 * Сравнивает строки посимвольно, начиная с конца строки,
 * игнорирует пунктуацию и пробелы
 * @param s1 - первая строка
 * @param s2 = вторая строка
 * @return true - если первая строка меньше второй, false - иначе
 */
bool comparisonWithoutPunctuationReverse(const string& s1, const string& s2) {
    int i = s1.length() - 1;
    int j = s2.length() - 1;
    while (i >= 0 || j >= 0) {
        while (ispunct(s1[i]) || isspace(s1[i])) {
            i--;
        }
        while (ispunct(s2[j]) || isspace(s2[j])) {
            j--;
        }
        if (tolower(s1[i]) == tolower(s2[j])) {
            i--;
            j--;
            continue;
        }
        return tolower(s1[i]) < tolower(s2[j]);
    }
    return false;
}

/**
 * Сортирует строки в том порядке, который задает передваяемая
 * как параметр функция
 * @param unsortedArray - вектор строк
 * @param left - правая граница сортировки
 * @param right - левая граница сортировки
 * @param comparisonFunction - функция, задающая способ сравнения строк между собой
 */
void quickSort(vector<string>& unsortedArray, int left, int right,
               bool (* comparisonFunction)(const string&, const string&)) {
    int i = left;
    int j = right;
    string pivot = unsortedArray[(i + j) / 2];

    while (i <= j) {
        while (comparisonFunction(unsortedArray[i], pivot)) {
            i++;
        }
        while (comparisonFunction(pivot, unsortedArray[j])) {
            j--;
        }
        if (i <= j) {
            swap(unsortedArray[i], unsortedArray[j]);
            i++;
            j--;
        }
    }
    if (j > left) {
        quickSort(unsortedArray, left, j, comparisonFunction);
    }
    if (i < right) {
        quickSort(unsortedArray, i, right, comparisonFunction);
    }
}

int main() {
    vector<string> poem = vector<string>();
    string inputString;
    fstream readerWriter;

    readerWriter.open("../input.txt", ios::in);
    if (readerWriter.is_open()) {
        while (getline(readerWriter, inputString)) {
            poem.push_back(inputString);
        }

        readerWriter.close();

        quickSort(poem, 0, poem.size() - 1, comparisonWithoutPunctuation);
        readerWriter.open("../output.txt", ios::out);
        for (const string& poemString : poem) {
            readerWriter << poemString << '\n';
        }
        readerWriter.close();

        quickSort(poem, 0, poem.size() - 1, comparisonWithoutPunctuationReverse);
        readerWriter.open("../output_reverse.txt", ios::out);
        for (const string& poemString : poem) {
            readerWriter << poemString << '\n';
        }
        readerWriter.close();
    }
    return 0;
}