#include "ItemManager.h"

using namespace std;

void ItemManager::Initialize() 
{
    // Adding Weapons
    itemDatabase.insert({ 101, Item(101, "Rusty Dagger", ItemType::Weapon, Rarity::Common, 5, "A small, rusted blade.",1) });
    itemDatabase.insert({ 102, Item(102, "Iron Sword", ItemType::Weapon, Rarity::Rare, 15, "A standard issue soldier's sword.",1) });
    itemDatabase.insert({ 103, Item(103, "Great Axe", ItemType::Weapon, Rarity::Legendary, 30, "A heavy axe that requires two hands.",1) });

    // Adding Armors
    itemDatabase.insert({ 201, Item(201, "Cloth Tunic", ItemType::Armor, Rarity::Common, 2, "Simple clothes offering minimal protection.",1) });
    itemDatabase.insert({ 202, Item(202, "Leather Armor", ItemType::Armor, Rarity::Rare, 8, "Lightweight armor made of cured leather.",1) });
    itemDatabase.insert({ 203, Item(203, "Plate Mail", ItemType::Armor, Rarity::Legendary, 20, "Heavy steel armor for maximum defense.",1) });

    // Adding Potions
    itemDatabase.insert({ 301, Item(301, "Red Potion", ItemType::Potion, Rarity::Common, 50, "Restores 50 HP immediately.",1) });
    itemDatabase.insert({ 302, Item(302, "Greater Potion", ItemType::Potion, Rarity::Rare, 150, "Restores 150 HP immediately.",1) });
    itemDatabase.insert({ 303, Item(303, "Greater Potion", ItemType::Potion, Rarity::Common, 50, "Increase 50 power immediately.",1) });
    itemDatabase.insert({ 304, Item(304, "Greater Potion", ItemType::Potion, Rarity::Rare, 150, "Increase 150 power immediately.",1) });


    // Adding Miscellaneous Items
    itemDatabase.insert({ 401, Item(401, "Old Map", ItemType::Etc, Rarity::Legendary, 0, "A map showing the location of a hidden dungeon.",1) });
    itemDatabase.insert({ 402, Item(402, "Iron Key", ItemType::Etc, Rarity::Legendary,0, "A rusty key used for iron doors.",1) });
}

Item* ItemManager::GetItemById(int id) 
{
    auto it = itemDatabase.find(id);
    if (it != itemDatabase.end()) 
    {
        return &(it->second);
    }
    return nullptr;
}


const map<int, Item>& ItemManager::GetFullDatabase() const {return itemDatabase;}