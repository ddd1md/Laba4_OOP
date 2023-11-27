#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#pragma once

template<typename K>
class HashSet {
public:
    HashSet();
    HashSet(const HashSet& other) = default;
    ~HashSet() = default;

    bool insert(K key);
    bool erase(K key);
    void eraseAll();
    std::size_t size() const;
    bool containKey(K key) const;
    std::vector<K> keys() const;

    bool loadFromFile(const std::string& fileName);
    bool loadToFile(const std::string& fileName) const;

    bool operator==(const HashSet& other) const;
    HashSet<K> operator&&(const HashSet& other) const;
    HashSet& operator<<(const K& key) {
        insert(key);
        return *this;
    }
private:
    std::vector<std::vector<K>> table_;
    std::size_t capacity_;
    std::size_t size_;

    std::size_t hashCode(K key) const;
};

template<typename K>
HashSet<K>::HashSet(): capacity_(10), size_(0) {
    table_.resize(capacity_);
}

template<typename K>
bool HashSet<K>::insert(K key) {
    std::size_t index = hashCode(key) % capacity_;
    auto& bucket = table_[index];

    auto it = std::find(bucket.begin(), bucket.end(), key);
    if (it == bucket.end()) {
        bucket.push_back(key);
        ++size_;
        return true;
    }

    return false;  // Key already exists
}

template<typename K>
bool HashSet<K>::erase(K key) {
    std::size_t index = hashCode(key) % capacity_;
    auto& bucket = table_[index];

    auto it = std::find(bucket.begin(), bucket.end(), key);
    if (it != bucket.end()) {
        bucket.erase(it);
        --size_;
        return true;
    }

    return false;  // Key not found
}

template<typename K>
void HashSet<K>::eraseAll() {
    for (auto& bucket : table_) {
        bucket.clear();
    }
    size_ = 0;
}

template<typename K>
std::size_t HashSet<K>::size() const {
    return size_;
}

template<typename K>
bool HashSet<K>::containKey(K key) const {
    std::size_t index = hashCode(key) % capacity_;
    const auto& bucket = table_[index];

    return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
}

template<typename K>
std::vector<K> HashSet<K>::keys() const {
    std::vector<K> result;
    for (const auto& bucket : table_) {
        result.insert(result.end(), bucket.begin(), bucket.end());
    }
    return result;
}

template<typename K>
bool HashSet<K>::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    eraseAll();

    K key;
    while (file >> key) {
        insert(key);
    }

    file.close();
    return true;
}

template<typename K>
bool HashSet<K>::loadToFile(const std::string& fileName) const {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& bucket : table_) {
        for (const auto& key : bucket) {
            file << key << std::endl;
        }
    }

    file.close();
    return true;
}

template<typename K>
bool HashSet<K>::operator==(const HashSet& other) const {
    return table_ == other.table_ && size_ == other.size_;
}

template<typename K>
HashSet<K> HashSet<K>::operator&&(const HashSet& other) const {
    HashSet<K> intersectionSet;

    for (const auto& bucket : table_) {
        for (const auto& key : bucket) {
            if (other.containKey(key)) {
                intersectionSet.insert(key);
            }
        }
    }

    return intersectionSet;
}

template<typename K>
HashSet<K>& operator<<(HashSet<K>& set, const K& key) {
    set.insert(key);
    return set;
}

template<typename K>
std::size_t HashSet<K>::hashCode(K key) const {
    return std::hash<K>{}(key);
}
