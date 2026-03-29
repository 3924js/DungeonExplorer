#include "Store.h"

using namespace std;

Store::Store() {}

void Store::InitializeStore()
{
    shopItemIDs.push_back(101); // Rusty Dagger
    shopItemIDs.push_back(102); // Iron Sword
    shopItemIDs.push_back(103); // Great Axe

    shopItemIDs.push_back(201); // Cloth Tunic
    shopItemIDs.push_back(202); // Leather Armor
    shopItemIDs.push_back(203); // Plate Mail

    shopItemIDs.push_back(301); // Red Potion
    shopItemIDs.push_back(302); // Greater Red Potion
    shopItemIDs.push_back(303); // Power Potion
    shopItemIDs.push_back(304); // Greater Power Potion
}

void Store::ShowShopMenu(int playerGold) const
{
    cout << "\n================ [ SHOP MENU ] ================" << endl;
    cout << " [ Current Gold: " << playerGold << " G ]" << endl;
    cout << "-----------------------------------------------" << endl;

    for (size_t i = 0; i < shopItemIDs.size(); ++i)
    {
        Item* item = ItemManager::GetInstance().GetItemById(shopItemIDs[i]);
        if (item)
        {
            cout << "[" << i + 1 << "] " << item->name  << " | Price: " << item->price << " G" << endl;
        }
    }
    cout << "===============================================" << endl;
}

void Store::BuyItem(int selection, int& playerGold, Inventory& playerInventory)
{
    int index = selection - 1;
    if (index < 0 || index >= (int)shopItemIDs.size()) return;

    int itemId = shopItemIDs[index];
    Item* masterData = ItemManager::GetInstance().GetItemById(itemId);

    // Check if player has enough gold
    if (playerGold >= masterData->price)
    {
        playerGold -= masterData->price;
        // Create a new item instance and add to inventory
        playerInventory.AddItem(ItemFactory::CreateItem(itemId));
        cout << "[System] Purchase success! Current Gold: " << playerGold << " G" << endl;
    }
    else
    {
        cout << "[System] Not enough gold!" << endl;
    }
}

void Store::SellItem(int selection, int& playerGold, Inventory& playerInventory)
{
    // 1. Convert user selection to vector index
    int index = selection - 1;

    std::vector<Item>& items = playerInventory.GetOwnedItems();

    if (index < 0 || index >= (int)items.size())
    {
        cout << "[System] Invalid inventory number!" << endl;
        return;
    }

    Item& itemToSell = items[index];
    int refund = static_cast<int>(itemToSell.price * sellReturnRate);

    playerGold += refund;
    cout << "[System] Sold " << itemToSell.name << " for " << refund << " G." << endl;

    playerInventory.RemoveItem(index);
}