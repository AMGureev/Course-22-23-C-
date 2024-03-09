#pragma once

#include <algorithm>
#include <unordered_map>

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::unordered_map<const T*, std::shared_ptr<T>> uniqueItems;
    std::vector<std::shared_ptr<T>> out;

    for (const auto& item : items) {
        const T* rawPtr = item.get();
        if (uniqueItems.find(rawPtr) == uniqueItems.end()) {
            uniqueItems[rawPtr] = std::make_shared<T>(*item);
        }
        out.push_back(uniqueItems[rawPtr]);
    }

    return out;
}

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> out;
    for (const auto& item : items) {
        out.push_back(std::make_unique<T>(*item));
    }
    return out;
}
