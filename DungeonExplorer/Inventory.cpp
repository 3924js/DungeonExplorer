#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "LogSystem.h"
#include "Inventory.h"

using namespace std;

void Inventory::AddItem(const Item& newItem) 
{
    stringstream SS;
    for (auto it = ownedItems.begin(); it != ownedItems.end(); ++it)
    {
        if (it->id == newItem.id)
        {
            it->count += newItem.count;
            SS.str("");
            SS << "[System] " << newItem.name << " stack increased to " << it->count << ".";
            LogSystem::PrintStringsOnLog({ SS.str()});
            return;
        }
    }
    ownedItems.push_back(newItem);
    SS.str("");
    SS << "[System] Added " << newItem.name << " to inventory.";
    LogSystem::PrintStringsOnLog({ SS.str() });
}

void Inventory::ShowInventory() const
{
    vector<string> Input = {};
    stringstream SS;
    Input.push_back("--- Current Inventory ---");

    if (ownedItems.empty()) 
    {
        Input.push_back("(Empty)");
        LogSystem::PrintStringsOnMain(Input);
        return;
    }

    for (size_t i = 0; i < ownedItems.size(); ++i)
    {
        SS.str("");
        SS << "[" << i + 1 << "] " 
            << PrintByRarity(ownedItems[i]) 
            << " (x" << ownedItems[i].count << ")"
            << " | " << ownedItems[i].desc;
        Input.push_back(SS.str());
        
    }
    LogSystem::PrintStringsOnMain(Input);
}

int Inventory::GetItemCount() const { return static_cast<int>(ownedItems.size()); }

void Inventory::UseItem() {
    if (ownedItems.empty()) {
        LogSystem::PrintStringsOnLog({"[System] Inventory is empty."});
        return;
    }

    LogSystem::PrintStringsOnLog({ "Enter Item Name: " });
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
                LogSystem::PrintStringsOnLog({"[Error] Player not found. Create character first!"});
                return;

            }

            if (it->type == ItemType::Potion) 
            {
                stringstream SS;
                SS << "[System] Used " << it->name << "!";
                LogSystem::PrintStringsOnLog({ SS.str() });

                // 2. HP Recovery logic
                if (it->id == 301 || it->id == 302) 
                {
                    SS.str("");
                    int finalHP = player->GetHP() + it->value;
                    if (finalHP > player->GetMaxHP()) finalHP = player->GetMaxHP();
                    player->SetHP(finalHP);
                    SS << "[Effect] HP is now " << player->GetHP();
                    LogSystem::PrintStringsOnLog({ SS.str() });
                }
                // 3. Temporary Attack Boost logic
                else if (it->id == 303 || it->id == 304) 
                {
                    SS.str("");
                    player->SetAttack(player->GetAttack() + it->value);
                    this->tempAtkBuff = it->value; // add temp attack buff
                    SS << "[Effect] Attack boosted by " << it->value << "!" << " temporarily for this stage!";
                    LogSystem::PrintStringsOnLog({ SS.str() });
                }

                // 4. Consume item
                if (it->count > 1) it->count--;
                else ownedItems.erase(it);
            }
            return;
        }
    }
    LogSystem::PrintStringsOnLog({"[System] Item not found."});
}

void Inventory::EquipItem(int index) 
{
    int actualIndex = index - 1;

    // Boundary Check
    if (actualIndex < 0 || actualIndex >= (int)ownedItems.size()) 
    {
        LogSystem::PrintStringsOnLog({ "[System] Invalid item index!" });
        return;
    }

    Item& selectedItem = ownedItems[actualIndex];
    int slotIndex = -1;

    Character* player = Character::GetInstance();

    stringstream SS;
    // Determine the slot based on ItemType
    if (selectedItem.type == ItemType::Weapon) 
    {
        slotIndex = (int)EquipSlot::Weapon;
        player->SetAttack(player->GetAttack() + selectedItem.value);
        SS << "[Effect] Attack boosted by " << selectedItem.value << "!";
        LogSystem::PrintStringsOnLog({ SS.str() });
    }
    else if (selectedItem.type == ItemType::Armor) 
    {
        slotIndex = (int)EquipSlot::Armor;
        player->SetDefense(player->GetDefense() + selectedItem.value);
        SS << "[Effect] Defense boosted by " << selectedItem.value << "!";
        LogSystem::PrintStringsOnLog({ SS.str() });
    }
    else 
    {
        LogSystem::PrintStringsOnLog({ "[System] This item cannot be equipped." });
        return;
    }

    // Assign the item address to the corresponding slot
    equippedSlots[slotIndex] = selectedItem.id;

    SS.str("");
    SS << "[System] Equipped " << selectedItem.name << " to " << (slotIndex == 0 ? "Weapon" : "Armor") << " slot.";
    LogSystem::PrintStringsOnLog({ SS.str() });
}

void Inventory::SetColor(int color) const
{
    // Get the standard output handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set the text attribute
    SetConsoleTextAttribute(hConsole, color);
}

string Inventory::PrintByRarity(Item item) const
{
    stringstream SS;
    int color = 7; // Default: White

    // Selection logic based on Rarity Enum
    switch (item.rarity)
    {
    case Rarity::Common:// White
        SS << TextFormat::WHITE << item.name << TextFormat::DEFAULT;
        return SS.str();
    case Rarity::Rare:// Green
        SS << TextFormat::GREEN << item.name << TextFormat::DEFAULT;
        return SS.str();
    case Rarity::Legendary:// Yellow/Gold
        SS << TextFormat::YELLOW << item.name << TextFormat::DEFAULT;
        return SS.str();
    default:// Default
        SS << TextFormat::WHITE << item.name << TextFormat::DEFAULT;
        return SS.str();
    }

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
