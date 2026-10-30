#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'queensAttack' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 *  3. INTEGER r_q
 *  4. INTEGER c_q
 *  5. 2D_INTEGER_ARRAY obstacles
 */

int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {
    // Para cada uma das 8 direcoes, guarda quantas casas livres existem
    // ate a borda do tabuleiro (ou ate o obstaculo mais proximo).
    int dr[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dc[8] = {1, 0, -1, 1, -1, 1, 0, -1};
    int reach[8];

    for (int d = 0; d < 8; d++) {
        int stepsRow = dr[d] > 0 ? n - r_q : dr[d] < 0 ? r_q - 1 : INT_MAX;
        int stepsCol = dc[d] > 0 ? n - c_q : dc[d] < 0 ? c_q - 1 : INT_MAX;
        reach[d] = min(stepsRow, stepsCol);
    }

    // Cada obstaculo so importa se estiver em linha reta com a rainha;
    // nesse caso limita a direcao correspondente (O(k) no total).
    for (int i = 0; i < k; i++) {
        int diffR = obstacles[i][0] - r_q;
        int diffC = obstacles[i][1] - c_q;

        if (diffR != 0 && diffC != 0 && abs(diffR) != abs(diffC)) continue;

        int sr = (diffR > 0) - (diffR < 0);
        int sc = (diffC > 0) - (diffC < 0);
        int dist = max(abs(diffR), abs(diffC));

        for (int d = 0; d < 8; d++) {
            if (dr[d] == sr && dc[d] == sc) {
                reach[d] = min(reach[d], dist - 1);
                break;
            }
        }
    }

    int total = 0;
    for (int d = 0; d < 8; d++) total += reach[d];
    return total;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string second_multiple_input_temp;
    getline(cin, second_multiple_input_temp);

    vector<string> second_multiple_input = split(rtrim(second_multiple_input_temp));

    int r_q = stoi(second_multiple_input[0]);

    int c_q = stoi(second_multiple_input[1]);

    vector<vector<int>> obstacles(k);

    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        string obstacles_row_temp_temp;
        getline(cin, obstacles_row_temp_temp);

        vector<string> obstacles_row_temp = split(rtrim(obstacles_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int obstacles_row_item = stoi(obstacles_row_temp[j]);

            obstacles[i][j] = obstacles_row_item;
        }
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
