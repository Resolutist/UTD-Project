#ifndef HOT_DOG_STAND_CLASS_CPP
#define HOT_DOG_STAND_CLASS_CPP

using namespace std;

//Define private outside of the class. Not a global variable. Making it static will not compile.
unsigned HotDogStandClass::globalSalesCount;

//Function for pass testing structures and logic.
void HotDogStandClass::hotDogsBuy(int count)
{
    //Check for 3 conditions:
    //1.If requested an invalid amount of hot dogs.
    if(count <= 0)
    {
        cout << "You cannot order a negative amount." << endl;
        return;
    }
    //2. If there are no more hot dogs to be sold.
    else if(inventoryCount == 0)
    {
        cout << "There are no more hot dogs in inventory to be sold." << endl;
        return;
    }
    //3. If there are more hot dogs requested than what is in the inventory.
    else if(inventoryCount < count)
    {
        //Use the conditional ternary operator to produce correct grammar (I thought it was funny too)
        cout << "*We only have " << inventoryCount << " hot dog" << (inventoryCount > 1 ? "s left.*" : " left.*") << endl;
        return;
    }
        //Subtract the inventory by the order requested.
        inventoryCount -= count;
        //Add the order requested to the total sales count, and the global count.
        soldCount += count;
        globalSalesCount += count;
}

void HotDogStandClass::stockInventory(int stockCount)
{
    //Validate amount of inventory.
    if(stockCount <= 0)
    {
        cout << "You cannot have a negative amount of stock." << endl;
        return;
    }
    //Add stock received to inventory.
    inventoryCount += stockCount;
}

#endif // HOT_DOG_STAND_CLASS_CPP
