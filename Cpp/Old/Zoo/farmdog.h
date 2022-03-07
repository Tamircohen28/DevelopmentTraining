#pragma once
#include "dog.h"

class FarmDog : public Dog
{
private:
    string m_favorite_tree;
    bool m_like_cows;

public:
    FarmDog(string color, string bark, string favorite_tree, bool like_cows = true);

    string get_favorite_tree();
    void set_favorite_tree(string favorite_tree);

    bool get_like_cows();
    void set_like_cows(bool like_cows);

    // virtual functio  of 'animal'
    void print() override;
};