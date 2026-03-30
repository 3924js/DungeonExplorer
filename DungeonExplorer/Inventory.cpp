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

int Inventory::GetItemCount() const { return static_cast<int>(ownedItems.size()); }

void Inventory::UseItem() {
    if (ownedItems.empty()) {
        std::cout << "[System] Inventory is empty." << std::endl;
        return;
    }

    std::cout << "Enter Item Name: ";
    std::string itemName;
    std::cin.ignore();
    std::getline(std::cin, itemName);

    for (auto it = ownedItems.begin(); it != ownedItems.end(); ++it) 
    {
        if (it->name == itemName) 
        {
            // 1. Get the already created player instance
            Character* player = Character::GetInstance();

            if (player == nullptr) 
            {
                std::cout << "[Error] Player not found. Create character first!" << std::endl;
                return;
            }

            if (it->type == ItemType::Potion) 
            {
                std::cout << "[System] Used " << it->name << "!" << std::endl;

                // 2. HP Recovery logic
                if (it->id == 301 || it->id == 302) 
                {
                    int finalHP = player->GetHP() + it->value;
                    if (finalHP > player->GetMaxHP()) finalHP = player->GetMaxHP();
                    player->SetHP(finalHP);
                    std::cout << "[Effect] HP is now " << player->GetHP() << std::endl;
                }
                // 3. Temporary Attack Boost logic
                else if (it->id == 303 || it->id == 304) 
                {
                    player->SetAttack(player->GetAttack() + it->value);
                    this->tempAtkBuff = it->value; // add temp attack buff
                    std::cout << "[Effect] Attack boosted by " << it->value << "!" << " temporarily for this stage!" << std::endl;
                }

                // 4. Consume item
                if (it->count > 1) it->count--;
                else ownedItems.erase(it);
            }
            return;
        }
    }
    std::cout << "[System] Item not found." << std::endl;
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

    Character* player = Character::GetInstance();

    // Determine the slot based on ItemType
    if (selectedItem.type == ItemType::Weapon) 
    {
        slotIndex = (int)EquipSlot::Weapon;
        player->SetAttack(player->GetAttack() + selectedItem.value);
        std::cout << "[Effect] Attack boosted by " << selectedItem.value << "!" << std::endl;
    }
    else if (selectedItem.type == ItemType::Armor) 
    {
        slotIndex = (int)EquipSlot::Armor;
        player->SetDefense(player->GetDefense() + selectedItem.value);
        std::cout << "[Effect] Defense boosted by " << selectedItem.value << "!" << std::endl;
    }
    else 
    {
        cout << "[System] This item cannot be equipped." << endl;
        return;
    }

    // Assign the item address to the corresponding slot
    equippedSlots[slotIndex] = selectedItem.id;

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

void Inventory::RemoveItem(int index)
{
    if (index >= 0 && index < (int)ownedItems.size())
    {
        ownedItems.erase(ownedItems.begin() + index);
    }
}

void Inventory::SetTempAtkBuff(int buff)
{
    tempAtkBuff += buff;
}
