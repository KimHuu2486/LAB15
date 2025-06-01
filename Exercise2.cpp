#include <iostream>
#include <string>
#include <vector>
using namespace std;
class HashTable {
private: 
    struct Entry {
        string key = "";
        int value = 0;
        bool isOccupied = false;
    };
    vector<Entry>table;
    int size;
    int hashFunction(const string& key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % size;
    }
public:
    HashTable(int tableSize) : size(tableSize) {
        table.resize(size);
    }
    bool insert(const string& key, int value) {
        int idx = hashFunction(key);
        int originalIdx = idx;
        while (table[idx].isOccupied && table[idx].key!=table[idx].key) {
            idx = (idx + 1) % size;
            if (idx == originalIdx) {
                cout << "Table is full" << endl;
                return false;
            }
        }
        table[idx].key = key;
        table[idx].value = value;
        table[idx].isOccupied = true;
    }
    bool search(const string& key, int& value) {
        int idx = hashFunction(key);
        int originalIdx = idx;
        while (table[idx].isOccupied) {
            if (table[idx].key == key) {
                value = table[idx].value;
                return true;
            }
            idx = (idx + 1) % size;
            if (idx == originalIdx) break;
        }
        return false;
    }
    void print() {
        for (int i = 0; i < size; i++) {
            if (table[i].isOccupied) {
                cout << i << ": " << table[i].key << " -> " << table[i].value << endl;
            }
            else {
                cout << i << ": Empty" << endl;
            }
        }
    }
};
int main()
{
    HashTable ht(10);
    ht.insert("apple", 5);
    ht.insert("banana", 8);
    ht.insert("cherry", 3);
    ht.insert("date", 12);
    ht.insert("grape", 10);
    ht.insert("lemon", 7);

    cout << "Hash Table Contents: " << endl;
    ht.print();
    cout << "\nLookup Operations:" << endl;
    int value;
    if (ht.search("banana", value)) {
        cout << "Found banana with value " << value << endl;
    }
    else {
        cout << "Could not find banana" << endl;
    }
    if (ht.search("kiwi", value)) {
        cout << "Found kiwi with value " << value << endl;
    }
    else {
        cout << "Could not find kiwi" << endl;
    }
    return 0;
}

