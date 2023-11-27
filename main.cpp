#include "Restaurants.h"
#include "HashSet.h"
#include <iostream>
#include <cassert>

using namespace std;

int main () {
    //Tests for the Restaurants class
    Restaurants testClassRestaurants;

    HashSet<string> writer1Preferences;
    HashSet<string> writer2Preferences;
    HashSet<string> writer3Preferences;

    writer1Preferences.insert("wow");
    writer1Preferences.insert("Some restaurant");
    writer1Preferences.insert("MMM");
    writer1Preferences.insert("ad232134");
    writer1Preferences.insert("ad232");

    writer2Preferences.insert("Some restaurant");
    writer2Preferences.insert("MMM");
    writer2Preferences.insert("ad232");
    writer2Preferences.insert("Lad");

    writer3Preferences.insert("MMM");
    writer3Preferences.insert("ad232");
    writer3Preferences.insert("23asd");
    writer3Preferences.insert("Some restaurant");

    testClassRestaurants.add(writer1Preferences);
    testClassRestaurants.add(writer2Preferences);
    testClassRestaurants.add(writer3Preferences);

    HashSet<string> commonPreferences = testClassRestaurants.getCommonPreferences();

    HashSet<string> resultPreferences;
    resultPreferences.insert("Some restaurant");
    resultPreferences.insert("MMM");
    resultPreferences.insert("ad232");
    assert(resultPreferences == commonPreferences);

    cout << "The tests for the class 'Restaurants.h' have been successfully passed" << endl;

    //Tests for HashSet
    //1.The size of the collection created by the default constructor is zero
    HashSet<string> testHashSet;
    assert(testHashSet.size() == 0);
    cout << "The first test was successfully passed" << endl;

    //2.When adding a new value, the size of the collection implemented on sets increases by one,
    // and when adding an existing value, the size remains the same
    testHashSet.insert("Moscow restaurant");
    assert(testHashSet.size() == 1);
    testHashSet.insert("Moscow restaurant");
    assert(testHashSet.size() == 1);
    cout << "The second test was successfully passed" << endl;

    //3.A non-empty collection after deleting all objects is equal to the collection
    // created using the default constructor
    testHashSet.eraseAll();
    HashSet<string> testHashSet3;
    assert(testHashSet == testHashSet3);
    cout << "The third test was successfully passed" << endl;

    //4.When any collection intersects with an empty one, the && operator returns an empty
    // collection (any && empty == empty)
    testHashSet.insert("Moscow restaurant");
    testHashSet.insert("St.Petersburg restaurant");
    HashSet<string> testHashSet4;
    HashSet<string> resultTest4 = testHashSet && testHashSet4;
    assert(resultTest4.size() == 0);
    cout << "The fourth test was successfully passed" << endl;

    //5.When the same collections intersect, the && operator returns a new collection equal to any of
    // them (any && any == any)
    HashSet<string> testHashSet5 = testHashSet && testHashSet;
    assert(testHashSet5.size() == 2);
    cout << "The fifth test was successfully passed" << endl;

    //6.A copy of a non-empty collection is equal to the original, after inserting, deleting or changing
    // an element, equality is violated
    HashSet<string> testHashSet6 = testHashSet;
    assert(testHashSet == testHashSet6);
    testHashSet6.insert("Moscow");
    assert(testHashSet.size() == 2);
    assert(testHashSet6.size() == 3);
    assert(!(testHashSet == testHashSet6));
    cout << "The sixth test was successfully passed" << endl;

    //7.A non-empty collection saved to a file is equal to a new collection loaded from the same file
    HashSet<string> testHashSet7;
    testHashSet7.insert("MoscowRestaurant");
    testHashSet7.insert("St.PetersburgRestaurant");
    testHashSet7.insert("Restaurant");
    testHashSet7.insert("JapaneseRestaurant");
    testHashSet7.loadToFile(R"(C:\Users\Inmot\file_OOP_test_Laba4.txt)");

    HashSet<string> testLoadedHashSet7;
    testLoadedHashSet7.loadFromFile(R"(C:\Users\Inmot\file_OOP_test_Laba4.txt)");

    assert(testHashSet7 == testLoadedHashSet7);
    cout << "The seventh test was successfully passed" << endl;

    cout << "All tests have been successfully passed" << endl;
    return 0;
}
