#pragma once

#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet();
    explicit UnorderedSet(size_t count);
    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last);
    UnorderedSet(const UnorderedSet& other);
    UnorderedSet(UnorderedSet&& other);
    ~UnorderedSet() = default;
    UnorderedSet& operator=(const UnorderedSet& other);
    UnorderedSet& operator=(UnorderedSet&& other);
    size_t Size() const;
    bool Empty() const;
    void Clear();
    void Insert(const KeyT& key);
    void Insert(KeyT&& key);
    void Erase(const KeyT& key);
    bool Find(const KeyT& key) const;
    void Rehash(size_t new_bucket_count);
    void Reserve(size_t new_bucket_count);
    size_t BucketCount() const;
    size_t BucketSize(size_t id) const;
    size_t Bucket(const KeyT& key) const;
    double LoadFactor() const;

private:
    size_t n_elements_;
    std::vector<std::list<KeyT>> data_;
};
