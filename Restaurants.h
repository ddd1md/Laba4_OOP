#include "HashSet.h"

class Restaurants {
public:
    Restaurants() = default;
    Restaurants(const Restaurants& other) = default;

    void add(const HashSet<std::string>& preferences);
    HashSet<std::string> getCommonPreferences() const;
private:
    std::vector<HashSet<std::string>> restaurants_;
};

void Restaurants::add(const HashSet<std::string>& preferences) {
    restaurants_.push_back(preferences);
}

HashSet<std::string> Restaurants::getCommonPreferences() const {
    if (restaurants_.empty()) {
        return HashSet<std::string>();
    }

    HashSet<std::string> commonPreferences = restaurants_[0];

    for (size_t i = 1; i < restaurants_.size(); ++i) {
        commonPreferences = commonPreferences && restaurants_[i];
    }

    return commonPreferences;
}