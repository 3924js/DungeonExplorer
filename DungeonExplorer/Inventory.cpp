#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "Inventory.h"

using namespace std;

void Inventory::AddItem(const Item& newItem) 
{
    for (auto it = ownedItems.begin(); it != ownedItems.end(); ++it)
    {
        if (it->id == newItem.id)
        {
            it->count += newItem.count;
            cout << "[System] " << newItem.name << " stack increased to " << it->count << "." << endl;
            return;
        }
    }
    ownedItems.push_back(newItem);
    cout << "[System] Added " << newItem.name << " to inventory." << endl;
}

void Inventory::ShowInventory() const 
{
    cout << "\n--- Current Inventory ---" << endl;

    if (ownedItems.empty()) 
    {
        cout << "(Empty)" << endl;
        return;
    }

    for (size_t i = 0; i < ownedItems.size(); ++i) 
    {
        cout << "[" << i + 1 << "] ";

        PrintByRarity(ownedItems[i]);

        cout << " (x" << ownedItems[i].count << ")"
            << " | " << ownedItems[i].desc << endl; 
    }

    cout << "-------------------------\n" << endl;
}

int Inventory::GetItemCount() const {return static_cast<int>(ownedItems.size());}

void Inventory::UseItem()
{
    if (ownedItems.empty())
    {
        cout << "[System] Your inventory is empty. Nothing to use." << endl;
        return;
    }

    cout << "Enter the item name you want to use: ";
    string itemName;
    // Use getline if the item name has spaces (e.g., "Iron Sword")
    cin.ignore(); // Clear the buffer before getline
    getline(cin, itemName);

    // Flag to check if item was found
    bool found = false;

    // Search through the inventory
    for (auto it = ownedItems.begin(); it != ownedItems.end(); ++it) 
    {
        if (it->name == itemName) 
        {
            cout << "[System] You used: " << it->name << "!" << endl;

            // Logic for item effects could go here (e.g., heal, buff)

            // Remove the item from the vector
            ownedItems.erase(it);
            found = true;
            break;
        }
    }

    if (!found) 
    {
        cout << "[System] Item '" << itemName << "' not found in inventory." << endl;
    }

}

void Inventory::EquipItem(int index) 
{
    int actualIndex = index - 1;

    // Boundary Check
    if (actualIndex < 0 || actualIndex >= (int)ownedItems.size()) 
    {
        cout << "[System] Invalid item index!" << endl;
        return;
    }

    Item& selectedItem = ownedItems[actualIndex];
    int slotIndex = -1;

    // Determine the slot based on ItemType
    if (selectedItem.type == ItemType::Weapon) 
    {
        slotIndex = (int)EquipSlot::Weapon;
    }
    else if (selectedItem.type == ItemType::Armor) 
    {
        slotIndex = (int)EquipSlot::Armor;
    }
    else 
    {
        cout << "[System] This item cannot be equipped." << endl;
        return;
    }

    // Assign the item address to the corresponding slot
    equippedSlots[slotIndex] = &selectedItem;

    cout << "[System] Equipped " << selectedItem.name << " to " << (slotIndex == 0 ? "Weapon" : "Armor") << " slot." << endl;
}

void Inventory::SetColor(int color) const
{
    // Get the standard output handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set the text attribute
    SetConsoleTextAttribute(hConsole, color);
}

void Inventory::PrintByRarity(const Item& item) const
{
    int color = 7; // Default: White

    // Selection logic based on Rarity Enum
    switch (item.rarity)
    {
    case Rarity::Common:    color = 7;  break; // White
    case Rarity::Rare:      color = 10; break; // Green
    case Rarity::Legendary: color = 14; break; // Yellow/Gold
    default:                color = 7;  break;
    }

    // Apply color and print
    SetColor(color);
    cout << "[" << item.name << "]";

    // Reset color to White (7) immediately!
    SetColor(7);
}