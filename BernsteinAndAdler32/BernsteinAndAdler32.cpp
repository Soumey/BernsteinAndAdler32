// BernsteinAndAdler32.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <unordered_map>
using namespace std;
unsigned long BernsteinHash(string str);
string generateString(int length);
unsigned long Adler32(string str);
void printRandomCollision(unordered_set<unsigned long>& collisionSet, unordered_map<unsigned long, string>& hashToStringMap);

int main()
{
    const int arraySize = 100000;
    string* C1 = new string[arraySize];
    string* C2 = new string[arraySize];
   // long** C2ascii = new long*[arraySize];
    long* C1HashedByBernstein = new long[arraySize];
    long* C2HashedByBernstein = new long[arraySize];
    long* C1HashedAdler32 = new long[arraySize];
    long* C2HashedAdler32= new long[arraySize];
    unordered_set<unsigned long> c1BernsteinHashes;
    unordered_set<unsigned long> c1Adler32Hashes;
    unordered_set<unsigned long> c2BernsteinHashes;
    unordered_set<unsigned long> c2Adler32Hashes;
    int c1BernsteinCollisionCount = 0;
    int c1Adler32CollisionCount = 0;
    int c2BernsteinCollisionCount = 0;
    int c2Adler32CollisionCount = 0;

    unordered_map<unsigned long, string> c1BernsteinHashToStringMap;
    unordered_map<unsigned long, string> c1Adler32HashToStringMap;
    unordered_map<unsigned long, string> c2BernsteinHashToStringMap;
    unordered_map<unsigned long, string> c2Adler32HashToStringMap;

    for (int i = 0; i < arraySize; i++)
    {
        C1[i] = generateString(8);
        C2[i] = generateString(100);

    }

   /* for (int i = 0; i < 100000; i=i + 1000)
    {
        cout << "C1[" << i << "] = " << C1[i] << endl;
        

    }
    for (int i = 0; i < 100000; i=i+1000)
    {
        cout << "C2[" << i << "] = " << C2[i] << endl;
    }*/
    for (int i = 0; i < arraySize;i++)
    {
        C1HashedByBernstein[i] = BernsteinHash(C1[i]);
        C1HashedAdler32[i] = Adler32(C1[i]);
        C2HashedByBernstein[i] = BernsteinHash(C2[i]);
        C2HashedAdler32[i] = Adler32(C1[i]);

        if (c1BernsteinHashes.count(C1HashedByBernstein[i]) > 0)
        {
            c1BernsteinCollisionCount++;
        }
        else
        {
            c1BernsteinHashes.insert(C1HashedByBernstein[i]);
            c1BernsteinHashToStringMap[C1HashedByBernstein[i]] = C1[i];
        }

        if (c1Adler32Hashes.count(C1HashedAdler32[i]) > 0)
        {
            c1Adler32CollisionCount++;
        }
        else
        {
            c1Adler32Hashes.insert(C1HashedAdler32[i]);
            c1Adler32HashToStringMap[C1HashedAdler32[i]] = C1[i];
        }

        if (c2BernsteinHashes.count(C2HashedByBernstein[i]) > 0)
        {
            c2BernsteinCollisionCount++;
        }
        else
        {
            c2BernsteinHashes.insert(C2HashedByBernstein[i]);
            c2BernsteinHashToStringMap[C2HashedByBernstein[i]] = C2[i];
        }

        if (c2Adler32Hashes.count(C2HashedAdler32[i]) > 0)
        {
            c2Adler32CollisionCount++;
        }
        else
        {
            c2Adler32Hashes.insert(C2HashedAdler32[i]);
            c2Adler32HashToStringMap[C2HashedAdler32[i]] = C2[i];
        }

    }
  /*  for (int i = 0; i <= arraySize; i=i+1000)
    {
        cout << "C1HashedByBernstein[" << i+1 << "] = " << C1HashedByBernstein[i] << endl;
        cout << "C1Adler32[" << i + 1 << "] = " << C1HashedAdler32[i] << endl;
    }

    for (int i = 0; i < arraySize; i=i+1000)
    {
        cout << "C2HashedByBernstein[" << i+1 << "] = " << C2HashedByBernstein[i] << endl;
        cout << "C2Adler32[" << i + 1 << "] = " << C2HashedAdler32[i] << endl;
    }*/
    cout << "C1 - Bernstein Hash Collisions: " << c1BernsteinCollisionCount << endl;
    cout << "C1 - Adler-32 Hash Collisions: " << c1Adler32CollisionCount << endl;
    cout << "C2 - Bernstein Hash Collisions: " << c2BernsteinCollisionCount << endl;
    cout << "C2 - Adler-32 Hash Collisions: " << c2Adler32CollisionCount << endl;

    printRandomCollision(c1BernsteinHashes, c1BernsteinHashToStringMap);
    printRandomCollision(c1Adler32Hashes, c1Adler32HashToStringMap);
    printRandomCollision(c2BernsteinHashes, c2BernsteinHashToStringMap);
    printRandomCollision(c2Adler32Hashes, c2Adler32HashToStringMap);
    
    delete[] C1; 
    delete[] C2; 
    delete[] C1HashedByBernstein;
    delete[] C2HashedByBernstein;
    delete[] C1HashedAdler32;
    delete[] C2HashedAdler32;

    return 0;
}

//void stringToAscii( string& str, long* asciiCode, int size)
//{
//    for (int i = 0; i < size; ++i) {
//        asciiCode[i] = static_cast<long>(str[i]);
//    }
//}
void printRandomCollision(unordered_set<unsigned long>& collisionSet, unordered_map<unsigned long, string>& hashToStringMap)
{
    if (collisionSet.empty())
    {
        cout << "No collisions found." << endl;
        return;
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<size_t> distribution(0, collisionSet.size() - 1);

    size_t randomIndex = distribution(generator);
    auto it = collisionSet.begin();
    advance(it, randomIndex);
    unsigned long randomCollision = *it;

    cout << "Random Collision: Hash = " << randomCollision << ", String = " << hashToStringMap[randomCollision] << endl;
}
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
