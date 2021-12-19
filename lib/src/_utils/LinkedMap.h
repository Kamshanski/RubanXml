#ifndef XML_RUBAN_LINKEDMAP_H
#define XML_RUBAN_LINKEDMAP_H

#include <functional>
#include <vector>
#include <stdexcept>

template<typename K, typename V>
class LinkedMap {
private:
    std::vector<std::pair<K, V>> map;


    int indexOf(const K& key) {
        int limit = map.size();
        for (int i = 0; i < limit; ++i) {
            std::pair<K, V>& pair = map[i];
            if (pair.first == key) {
                return i;
            }
        }
        return -1;
    }
public:
    int size() const { return map.size(); }
    bool isEmpty() const { return map.empty(); }
    bool isNotEmpty() const { return !isEmpty(); };

    void put(const K& key, const V& value) {
        int i = indexOf(key);
        if (i < 0) {
            map.push_back({key, value});
        } else {
            map[i] = {key, value};
        }
    }

    V& get(const K& key) {
        int i = indexOf(key);
        if (i < 0) {
            throw std::out_of_range("No entry with such key exists");
        } else {
            return map[i].second;
        }
    }

    std::pair<K, V>& indexed(int index) {
        return map[index];
    }

    void forEachIndexed(std::function<void(int, const V&, const K&)> consumer) const {
        int limit = map.size();
        for (int i = 0; i < limit; ++i) {
            const std::pair<K, V>& entry = map[i];
            consumer(i, entry.first, entry.second);
        }

    }

    void forEachIndexed(std::function<void(int, V&, K&)> consumer) {
        int limit = map.size();
        for (int i = 0; i < limit; ++i) {
            std::pair<K, V>& entry = map[i];
            consumer(i, entry.first, entry.second);
        }

    }


};


#endif //XML_RUBAN_LINKEDMAP_H
