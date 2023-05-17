// BernsteinAndAdler32.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <random>
#include <unordered_map>

using namespace std;
unsigned long BernsteinHash(string str);
string generateString(int length);
unsigned long Adler32(string str);

int main()
{

    const int arraySize = 100000;
    unordered_map<unsigned long, vector<string>> hashCollisions1;
    unordered_map<unsigned long, vector<string>> hashCollisions2;
    unordered_map<unsigned long, vector<string>> hashCollisions3;
    unordered_map<unsigned long, vector<string>> hashCollisions4;

    for (int i = 0; i < arraySize; i++) {
        string generatedString = generateString(8);
        string generatedString2 = generateString(100);
        unsigned long hash = BernsteinHash(generatedString);
        unsigned long hash2 = BernsteinHash(generatedString2);
        unsigned long hash3 = Adler32(generatedString);
        unsigned long hash4= Adler32(generatedString2);
        //bernstein
        if (hashCollisions1.find(hash) == hashCollisions1.end()) {
            hashCollisions1[hash] = vector<string>{ generatedString };
        }
        else {
            hashCollisions1[hash].push_back(generatedString);
        }
        if (hashCollisions2.find(hash2) == hashCollisions2.end()) {
            hashCollisions2[hash2] = vector<string>{ generatedString2 };
        }
        else {
            hashCollisions2[hash2].push_back(generatedString2);
        }
        //adler32
        if (hashCollisions3.find(hash3) == hashCollisions3.end()) {
            hashCollisions3[hash3] = vector<string>{ generatedString };
        }
        else {
            hashCollisions3[hash3].push_back(generatedString);
        }
        if (hashCollisions4.find(hash4) == hashCollisions4.end()) {
            hashCollisions4[hash4] = vector<string>{ generatedString2 };
        }
        else {
            hashCollisions4[hash4].push_back(generatedString2);
        }

    }

    int numCollisions = 0;
    int numCollisions2 = 0;
    for (const auto& entry : hashCollisions1) {
        if (entry.second.size() > 1) {
            numCollisions++;
        }
    }

    for (const auto& entry : hashCollisions2) {
        if (entry.second.size() > 1) {
            numCollisions2++;
        }
    }
    // Dane o ilosci kolizji Bernstein
    cout << "Liczba kolizji dla stringow 8 elementowych przy użyciu Bernstein Hash: " << numCollisions << endl;
    cout << "Liczba kolizji dla stringow 100 elementowych przy użyciu Bernstein Hash: " << numCollisions2 << endl<<endl;
    // Losowa kolizja Bernstein
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, numCollisions - 1);

    int randomIndex = distribution(generator);

    uniform_int_distribution<int> distribution2(0, numCollisions2 - 1);
    int randomIndex2 = distribution2(generator);

    int currentCollisionIndex = 0;
    int currentCollisionIndex2 = 0;

    for (const auto& entry : hashCollisions1) {
        if (entry.second.size() > 1) {
            if (currentCollisionIndex == randomIndex) {
                cout << "Losowa kolizja dla stringow 8 elementowych:" << endl;
                cout << "Hash: " << entry.first << endl;
                cout << "String:" << entry.second[1] << endl<<endl;
               /* for (const auto& str : entry.second) {
                    cout << str << endl;
                }*/
            }
            currentCollisionIndex++;
        }
    }

    for (const auto& entry : hashCollisions2) {
        if (entry.second.size() > 1) {
            if (currentCollisionIndex2 == randomIndex2) {
                cout << "Losowa kolizja dla stringow 100 elementowych:" << endl;
                cout << "Hash: " << entry.first << endl;
                cout << "String:" << entry.second[1] << endl<<endl;
                /* for (const auto& str : entry.second) {
                     cout << str << endl;
                 }*/
            }
            currentCollisionIndex2++;
        }
    }
    // Dane o ilosci kolizji Adler32
    int numCollisions3 = 0;
    int numCollisions4 = 0;
    for (const auto& entry : hashCollisions3) {
        if (entry.second.size() > 1) {
            numCollisions3++;
        }
    }

    for (const auto& entry : hashCollisions4) {
        if (entry.second.size() > 1) {
            numCollisions4++;
        }
    }

    cout << "Liczba kolizji dla stringow 8 elementowych przy uzyciu Adler32: " << numCollisions3 << endl;
    cout << "Liczba kolizji dla stringow 100 elementowych przy uzyciu Adler32: " << numCollisions4 <<endl<<endl;


    // Losowa kolizja Adler32
    uniform_int_distribution<int> distribution3(0, numCollisions3 - 1);

    int randomIndex3 = distribution3(generator);

    uniform_int_distribution<int> distribution4(0, numCollisions4 - 1);
    int randomIndex4 = distribution4(generator);

    int currentCollisionIndex3 = 0;
    int currentCollisionIndex4 = 0;

    for (const auto& entry : hashCollisions3) {
        if (entry.second.size() > 1) {
            if (currentCollisionIndex3 == randomIndex3) {
                cout << "Losowa kolizja dla stringow 8 elementowych:" << endl;
                cout << "Hash: " << entry.first << endl;
                cout << "String:" << entry.second[1] << endl<<endl;
                /* for (const auto& str : entry.second) {
                     cout << str << endl;
                 }*/
            }
            currentCollisionIndex3++;
        }
    }

    for (const auto& entry : hashCollisions4) {
        if (entry.second.size() > 1) {
            if (currentCollisionIndex4 == randomIndex4) {
                cout << "Losowa kolizja dla stringow 100 elementowych:" << endl;
                cout << "Hash: " << entry.first << endl;
                cout << "String:" << entry.second[1] << endl<<endl;
                /* for (const auto& str : entry.second) {
                     cout << str << endl;
                 }*/
            }
            currentCollisionIndex4++;
        }
    }

    return 0;
}

//void stringToAscii( string& str, long* asciiCode, int size)
//{
//    for (int i = 0; i < size; ++i) {
//        asciiCode[i] = static_cast<long>(str[i]);
//    }
//}

string generateString(int length) {
    if (length <= 0) {
        return "";
    }

    const string Alphabet = "abcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, Alphabet.length() - 1);
    string randomString;

    for (int i = 0; i < length; ++i) {
        randomString += Alphabet[distribution(generator)];
    }

    return randomString;
}
unsigned long BernsteinHash(string str)
{
    unsigned long hash = 5381;
    unsigned long hashed = 0;
    for (auto c : str) {
        hashed += (hash *32) +hash+ static_cast<unsigned long>(c);
    }

    return hashed;
}
unsigned long Adler32(string str)
{
    const unsigned long MOD_ADLER = 65521;
    unsigned long A = 1;
    unsigned long B = 0;

    for (char c : str) {
        A = (A + static_cast<unsigned long>(c)) % MOD_ADLER;
        B = (B + A) % MOD_ADLER;
    }

    return (B *MOD_ADLER)+ A;
}
