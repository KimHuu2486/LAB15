#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct Entry {
    int key;
    int value;
    bool occupied;

    Entry() {
        key = -1;
        value = -1;
        occupied = false;
    }
};

class HashTable {
private:
    vector<Entry> table;
    int capacity;

    int hash(int key) const {
        return key % capacity;
    }

    void insertToTable(vector<Entry>& targetTable, int newCapacity, int key, int value) {
        int i = key % newCapacity;

        Entry newEntry{ key, value, true };

        while (targetTable[i].occupied) {
            swap(newEntry, targetTable[i]);
            i = (i + 1) % newCapacity;
        }

        targetTable[i] = newEntry;
    }

public:
    HashTable(int size = 10) {
        capacity = size;
        table.resize(capacity);
    }

    void insertLCFS(int key, int value) {
        if (loadFactor() > 0.7) {
            resize(capacity * 2); // tự động resize nếu vượt ngưỡng
        }

        int i = hash(key);
        Entry newEntry{ key, value, true };

        while (table[i].occupied) {
            swap(newEntry, table[i]);
            i = (i + 1) % capacity;
        }

        table[i] = newEntry;
    }

    void resize(int newCapacity) {
        vector<Entry> oldTable = table;
        table = vector<Entry>(newCapacity);
        capacity = newCapacity;

        for (const auto& entry : oldTable) {
            if (entry.occupied) {
                insertToTable(table, capacity, entry.key, entry.value);
            }
        }
    }

    double loadFactor() const {
        int count = 0;
        for (const auto& entry : table)
            if (entry.occupied) count++;
        return (double)count / capacity;
    }

    void display() {
        cout << "Index | Key | Value\n";
        for (int i = 0; i < capacity; ++i) {
            cout << "  " << i << "   | ";
            if (table[i].occupied)
                cout << table[i].key << "   | " << table[i].value;
            else
                cout << "EMPTY";
            cout << endl;
        }
    }
};

int main() {
    HashTable ht(5);

    ht.insertLCFS(5, 100);
    ht.insertLCFS(15, 200);
    ht.insertLCFS(25, 300);
    ht.insertLCFS(35, 400); // gây ra va chạm và resize

    cout << "\nSau khi chèn và resize:\n";
    ht.display();

    return 0;
}


