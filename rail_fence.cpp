// #include <iostream>
// #include <string>
// #include <vector>
// #include<bits/stdc++.h>
// using namespace std;

// string rail_fence_encrypt(string& plaintext, int rails) {
//     vector<string> fence(rails);
//     int rail = 0;
//     bool direction = false; // false for downward, true for upward

//     for (char ch : plaintext) {
//         fence[rail] += ch;

//         if (rail == 0 || rail == rails - 1) {
//             direction = !direction; // Change direction at the top or bottom rail
//         }

//         if (direction) {
//             rail--;
//         } else {
//             rail++;
//         }
//     }

//     string ciphertext;
//     for (string& railStr : fence) {
//         ciphertext += railStr;
//     }

//     return ciphertext;
// }

// string rail_fence_decrypt(string& ciphertext, int rails) {
//     vector<string> fence(rails, "");
//     int rail = 0;
//     bool direction = false;

//     // Calculate the number of characters in each rail
//     vector<int> railLengths(rails, 0);
//     int railIndex = 0;

//     for (char ch : ciphertext) {
//         fence[rail] += ch;
//         railLengths[rail]++;

//         if (rail == 0 || rail == rails - 1) {
//             direction = !direction; // Change direction at the top or bottom rail
//         }

//         if (direction) {
//             rail--;
//         } else {
//             rail++;
//         }
//     }

//     string plaintext;
//     rail = 0;

//     for (int i = 0; i < ciphertext.length(); i++) {
//         plaintext += fence[rail][railIndex];
//         railIndex++;

//         if (rail == 0 || rail == rails - 1) {
//             direction = !direction; // Change direction at the top or bottom rail
//         }

//         if (direction) {
//             rail--;
//         } else {
//             rail++;
//         }

//         if (railLengths[rail] == railIndex) {
//             railIndex = 0;
//         }
//     }

//     return plaintext;
// }

// int main() {
//     string plaintext = "HELLO RAIL FENCE CIPHER";
//     int rails = 3;

//     string ciphertext = rail_fence_encrypt(plaintext, rails);
//     cout << "Ciphertext: " << ciphertext << endl;

//     string decryptedText = rail_fence_decrypt(ciphertext, rails);
//     cout << "Decrypted Text: " << decryptedText << endl;

//     return 0;
// }


#include <bits/stdc++.h>
using namespace std;

string format(string &str)
{
    stringstream res;
    for (auto &ch : str)
    {
        if (ch != ' ')
        {
            res << (char)tolower(ch);
        }
    }
    return res.str();
}
string encrypt(string &plain, int key)
{
    vector<vector<char>> matrix(key);
    int rowNumber = 0;
    int flag = 1;
    for (int i = 0; i < plain.size(); i++)
    {
        matrix[rowNumber].push_back(plain[i]);
        rowNumber += flag;
        if (rowNumber == 0)
            flag = 1;

        if (rowNumber == key - 1)
            flag = -1;
    }
    stringstream cipher;
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
            cipher << char(matrix[i][j]);
    }
    return cipher.str();
}



string decrypt(string &cipher, int key)
{
    vector<vector<int>> matrixDecry(key);
    int rowNumber = 0;
    int flag = 1;
    int n = cipher.length();
    for (int i = 0; i < n; i++)
    {
        matrixDecry[rowNumber].push_back(i);
        rowNumber += flag;
        if (rowNumber == (key - 1))
            flag = -1;
        if (rowNumber == 0)
            flag = 1;
    }
    vector<int> mapping;
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < matrixDecry[i].size(); j++)
            mapping.push_back(matrixDecry[i][j]);
    }
    map<int, char> m;
    for (int i = 0; i < n; i++)
        m[mapping[i]] = cipher[i];
    stringstream plain;
    for (int i = 0; i < n; i++)
        plain << char(m[i]);
    return plain.str();
}
int main()
{
    int choice;
    cout << "1. Encrypt\n2. Decrypt\nEnter your choice: "; 
     cin >>choice;
    cin.get();

    if (choice == 1)
    {
        string plain;
        int key;
        cout << "\nEnter plain text: ";
        getline(cin, plain);
        plain = format(plain);
        cout << "\nEnter key: integer value: ";
        cin >> key;
        string cipher = encrypt(plain, key);
        cout << "\nEncrypted text is : " << cipher << endl;
    }
    else if (choice == 2)
    {
        string cipher;
        int key;
        cout << "\nEnter cipher text: ";
        getline(cin, cipher);
        cipher = format(cipher);
        cout << "\nEnter key: integer value: ";
        cin >> key;
        string plain = decrypt(cipher, key);
        cout << "\nDecrypted text is : " << plain << endl;
    }
    return 0;
}
