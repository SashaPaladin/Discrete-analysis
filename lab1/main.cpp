#include <iostream>
#include <vector>

struct Pair {
    unsigned long long key{};
    char value[64]{};
};

void swap(Pair &first, Pair &second) {
    Pair tmp = first;
    first = second;
    second = tmp;
}

void insertionSort(std::vector<Pair> &vec) {
    for (int i = 1; i < vec.size(); i++)
        for (int j = i; j > 0; --j)
            if (vec[j - 1].key > vec[j].key)
                swap(vec[j - 1], vec[j]);
}

void bucketSort(std::vector<Pair> &vec) {
    std::vector<std::vector<Pair>> buckets(vec.size());
    unsigned long long maxKey = vec[0].key;
    unsigned long long minKey = vec[0].key;
    for (const auto &v: vec) {
        if (maxKey < v.key) maxKey = v.key;
        if (minKey > v.key) minKey = v.key;
    }
    const long double interval = (long double) (maxKey - minKey + 1) / vec.size();
    for (int i = 0; i < vec.size(); ++i) {
        auto j = (unsigned long long) ((vec[i].key - minKey) / interval);
        if (j == vec.size())
            j--;
        buckets[j].push_back(vec[i]);
    }
    for (int i = 0; i < vec.size(); ++i)
        insertionSort(buckets[i]);
    int position = 0;
    for (auto &bucket : buckets) {
        for (auto &pair : bucket) {
            vec[position++] = pair;
        }
    }
}

int main() {
    std::vector<Pair> vec;
    unsigned long long k;
    std::string v;
    while (std::cin >> k >> v) {
        Pair pair;
        pair.key = k;
        for (int i = 0; i < 64; i++) {
            pair.value[i] = v[i];
        }
        vec.push_back(pair);
    }
    if (!vec.empty()) {
        bucketSort(vec);
        for (Pair &p: vec)
            std::cout << p.key << '\t' << p.value << '\n';
    }
    return 0;
}
