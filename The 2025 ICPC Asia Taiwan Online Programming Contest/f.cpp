#include <bits/stdc++.h>
using namespace std;
#define ll long long

void printBox(char box[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << (int) box[i][j] << " ";
        }
        cout << endl;
    }
}

uint16_t box2mask(char box[4][4]) {
    return accumulate(&box[0][0], &box[0][0] + 16, uint16_t(0), [](uint16_t acc, char c) {
        return (acc << 1) | (c != 0);
    });
}

char boxDegree(char box[4][4]) {
    return 16 - count_if(&box[0][0], &box[0][0] + 16, [](char c) { return c == 0; });
}

bool isValid(char box[4][4], int row, int col, char fruit) {
    for (int i = 0; i < 4; i++) {
        if (box[row][i] == fruit || box[i][col] == fruit) {
            return false;
        }
    }
    return true;
}

uint16_t fill_row[4] = {
    0b0000111111111111,
    0b1111000011111111,
    0b1111111100001111,
    0b1111111111110000,
};
uint16_t fill_col[4] = {
    0b0111011101110111,
    0b1011101110111011,
    0b1101110111011101,
    0b1110111011101110,
};

const uint64_t cellMask = 0b10000000'00000000'10000000'00000000'10000000'00000000'10000000'00000000;

size_t solution_count(char box[4][4]) {
    uint64_t fullMap = -1ull;
    uint64_t tryMask = 0;
    for (int i = 0; i < 16; i++) {
        int row = i / 4, col = i % 4;
        if (!box[row][col]) continue;
        uint16_t rowMask = rotr(uint16_t(0b00001111'11111111), row);
        uint16_t colMask = rotr(uint16_t(0b01110111'01110111), col);
        char fruit = box[row][col] - 1;
        fullMap &= uint64_t(rowMask & colMask) << (48 - fruit * 16);
    }
    for (int i = 0; i < 16; i++) {
        auto cell = fullMap & (cellMask >> i);
        auto oneCount = popcount(cell);
        if (oneCount == 0) {
            return 0;
        } else if (oneCount == 1) {
            auto fruit = countl_zero(cell) / 16;
            tryMask |= cell;
            box[i / 4][i % 4] = fruit + 1;
        }
    }
    for (int fruit = 0; fruit < 4; fruit++) 
        for (int row = 0; row < 4; row++) for (int col = 0; col < 4; col++) {
            
        }
    
    bool full = 1;
    bool hasSolution = 0;
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
        if (box[i][j]) continue;
        full = 0;

        size_t count = 0;
        char solvedFruit;
        for (char fruit = 1; fruit <= 4; fruit++) {
            if (!isValid(box, i, j, fruit)) continue;

            box[i][j] = fruit;
            count += solution_count(box);
            box[i][j] = 0;
            if (count == 1) solvedFruit = fruit;

            if (count > 1) {
                printBox(box);
                cout << "after placing " << (int) fruit << " at (" << i <<
                    ", " << j << "), count: " << count << endl;
                return count;
            }
        }
        if (count) {
            hasSolution = 1;
        }
    }
    if (full) {
        // printBox(box);
        // cout << "count: " << 1 << " (full)" << endl;
        return 1;
    }
    // printBox(box);
    // cout << "count: " << hasSolution << endl;
    return hasSolution;
}

array<bool, (1 << 16)> isUnique;
void buildUnique(char box[4][4]) {
    auto endMask = box2mask(box);
    for (int mask = 0; mask <= endMask; mask++) {
        vector<uint16_t> childMasks;
        for (int shift = 0; shift < 16; shift++) {
            if (!uint16_t((1 << shift) & mask)) continue;
            childMasks.push_back(mask ^ (1 << shift));
        }
        // cout << bitset<16>(mask) << ": ";
        // for (auto m : childMasks) cout << bitset<16>(m) << " ";
        // cout << endl;
        if (any_of(childMasks.begin(), childMasks.end(), [=](uint16_t childMask) { 
            return isUnique[childMask];
        })) {
            isUnique[mask] = 1;
            continue;
        };

        char maskedBox[4][4];
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
            maskedBox[i][j] = (mask & ((1 << 15) >> (i * 4 + j))) ? box[i][j] : 0;
        }
        cout << "counting solutions of " << bitset<16>(mask) << endl;
        auto count = solution_count(maskedBox);
        isUnique[mask] = count <= 1;
        // if (mask < 10) {
        //     printBox(maskedBox);
        //     cout << bitset<16>(mask) << ": " << count << endl;
        // }
    }
}

char dp_cache[1 << 16];
char dp(uint16_t mask, char degree) {
    if (dp_cache[mask] != -1) {
        return dp_cache[mask];
    }
    if (!isUnique[mask]) {
        return dp_cache[mask] = 17; // dead end
    }

    vector<char> answers;
    for (int shift = 0; shift < 16; shift++) {
        if (!uint16_t((1 << shift) & mask)) continue;
        uint16_t nextMask = mask ^ (1 << shift);
        auto answer = dp(nextMask, degree - 1);
        if (answer > 16) continue; // dead end
        answers.push_back(answer);
    }
    if (answers.empty()) { // game over
        return dp_cache[mask] = degree;
    }
    auto lose = partition(answers.begin(), answers.end(), [=](char answer) {
        return (degree - answer) % 2; // 1: win, 0: lose
    });
    auto win = answers.begin();
    if (win != lose) { // "If there's a way I can eventually grab the last fruit"
        // "maximize the total number of fruits"
        return dp_cache[mask] = *min_element(win, lose); 
    } else { // "if my sibling could outsmart me and grab the last fruit"
        // "minimize the number of fruits"
        return dp_cache[mask] = *max_element(lose, answers.end()); 
    }
}

void solve(char box[4][4]) {
    cout << "mask: " << bitset<16>(box2mask(box)) << endl;
    cout << "degree: " << (int) boxDegree(box) << endl;
    for (int i = 0; i < (1 << 16); i++) {
        dp_cache[i] = -1; // not visit yet
    }
    buildUnique(box);
    auto answer = dp(box2mask(box), boxDegree(box));
    cout << int(answer) << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        char box[4][4];
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                char c; cin >> c;
                switch (c) {
                    case 'X': box[j][k] = 0; break;
                    case 'G': box[j][k] = 1; break;
                    case 'L': box[j][k] = 2; break;
                    case 'M': box[j][k] = 3; break;
                    case 'S': box[j][k] = 4; break;
                }
            }
        }
        // solve(box);
    }

    char box[4][4] = {
        {1, 2, 0, 0},
        {0, 0, 3, 0},
        {0, 0, 0, 1},
        {0, 4, 0, 0}
    };
    cout << solution_count(box);
}