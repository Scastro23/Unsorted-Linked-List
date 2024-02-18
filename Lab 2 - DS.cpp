// Samuel Castro
// Lab 2 
// SP2024
/* Description: A data structure of objects arranged in a linear order. The order is determined by a
pointer in each object. See definition on pg. 134 and implementation on pg. 167 of the 6th
edition of C++ Plus Data Structures. Your welcome to learn from the books implementation,
however, make sure to write your own code. This unsorted list must be implemented with
pointers. You will then write a client code that will have a function that will take two unsorted
lists and perform the union set operation. The resulting new unsorted list will consist of all the
unique items from the original two lists with no duplicates.*/

#include <iostream>

// ItemType class
class ItemType {
public:
    
    enum RelationType { LESS, GREATER, EQUAL };

    // Function compare two items
    RelationType ComparedTo(ItemType item) const {
        if (value < item.value)
            return LESS;
        else if (value > item.value)
            return GREATER;
        else
            return EQUAL;
    }

    // Constructor
    ItemType(int val = 0) : value(val) {}

    // Get and set
    int getValue() const { return value; }
    void setValue(int val) { value = val; }

private:
    int value;
};

// Define NodeType struct
struct NodeType {
    ItemType info; // Item stored
    NodeType* next; // Pointer
};

// Define UnsortedType class for managing the list
class UnsortedType {
public:
    
    UnsortedType(); // Initialize
    ~UnsortedType(); // Deallocate

    void MakeEmpty(); // List empty
    bool IsFull(); // List is full
    int GetLength(); // Length
    ItemType GetItem(ItemType item, bool& found); // Get an item
    void PutItem(ItemType item); // Put an item
    void DeleteItem(ItemType item); // Delete an item
    void ResetList(); // Reset
    ItemType GetNextItem(); // Next item in the list

private:
    NodeType* listData; // Pointer
    int length; // Length of the list
    NodeType* currentPos; // Pointer
};

// Constructor
UnsortedType::UnsortedType() {
    length = 0;
    listData = nullptr;
    currentPos = nullptr;
}

// Destructor
UnsortedType::~UnsortedType() {
    MakeEmpty();
}

// Make the list empty
void UnsortedType::MakeEmpty() {
    NodeType* tempPtr;
    while (listData != nullptr) {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
    length = 0;
}

// Check if is full
bool UnsortedType::IsFull() {
    NodeType* location;
    location = new NodeType;
    delete location;
    return false;
}

// Get the length of the list
int UnsortedType::GetLength() {
    return length;
}

// Get an item from the list
ItemType UnsortedType::GetItem(ItemType item, bool& found) {
    bool moreToSearch;
    NodeType* location;
    location = listData;
    found = false;
    moreToSearch = (location != nullptr);
    while (moreToSearch && !found) {
        switch (item.ComparedTo(location->info)) {
        case ItemType::LESS:
        case ItemType::GREATER:
            location = location->next;
            moreToSearch = (location != nullptr);
            break;
        case ItemType::EQUAL:
            found = true;
            item = location->info;
            break;
        }
    }
    return item;
}

// Put an item into the list
void UnsortedType::PutItem(ItemType item) {
    NodeType* location;
    location = new NodeType;
    location->info = item;
    location->next = listData;
    listData = location;
    length++;
}

// Delete an item from the list
void UnsortedType::DeleteItem(ItemType item) {
    NodeType* location = listData;
    NodeType* tempLocation;

    if (item.getValue() == listData->info.getValue()) {
        tempLocation = location;
        listData = listData->next;
    }
    else {
        while (item.ComparedTo(location->next->info) != ItemType::EQUAL)
            location = location->next;

        tempLocation = location->next;
        location->next = location->next->next;
    }

    delete tempLocation;
    length--;
}


void UnsortedType::ResetList() {
    currentPos = nullptr;
}

// Get next item in the list
ItemType UnsortedType::GetNextItem() {
    if (currentPos == nullptr)
        currentPos = listData;
    else
        currentPos = currentPos->next;
    return currentPos->info;
}


int main() {
    
    UnsortedType list;

    // Create ItemType objects
    ItemType item1(10);
    ItemType item2(20);
    ItemType item3(30);

    // Put items into the list
    list.PutItem(item1);
    list.PutItem(item2);
    list.PutItem(item3);

    // Print the length
    std::cout << "Length of list: " << list.GetLength() << std::endl;

    // Search for item in the list
    bool found;
    ItemType foundItem = list.GetItem(item2, found);
    if (found) {
        std::cout << "Item found: " << foundItem.getValue() << std::endl;
    }
    else {
        std::cout << "Item not found." << std::endl;
    }

    // Delete item from the list
    list.DeleteItem(item2);
    std::cout << "Length of list after deletion: " << list.GetLength() << std::endl;

    
    list.ResetList();
    std::cout << "Next item after reset: " << list.GetNextItem().getValue() << std::endl;

    return 0;
}

