#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last) {
    Contact *currentContact = headContactList;

    while (currentContact != nullptr){
        if (currentContact->first == first && currentContact->last == last){
            os << "Contact Name: " << currentContact->first << " " << currentContact->last << endl;

            Info *currentInfo = currentContact->headInfoList;
            while (currentInfo != nullptr){
                os << currentInfo->name << " | " << currentInfo->value << endl;
                currentInfo = currentInfo->next; //Needs to be in while loop
            }
                return true;
        }
        currentContact = currentContact->next;
    }
    
    return false;
}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) {
    Contact *currentContact = headContactList;

    while (currentContact != nullptr){
            os << "Contact Name: " << currentContact->first << " " << currentContact->last << endl;

            Info *currentInfo = currentContact->headInfoList;
            while (currentInfo != nullptr){
                os << currentInfo->name << " | " << currentInfo->value << endl;
                currentInfo = currentInfo->next; //Needs to be in while loop
            }
            currentContact = currentContact->next;
        }
    }

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) {
    Contact *currentContact = headContactList;
    
    //Part 1
    while (currentContact != nullptr){
        if (currentContact->first == first && currentContact->last == last){
            return false; // Contact already exists
        }
        currentContact = currentContact->next;
    }

    //Part 2
    Contact *newContact = new Contact(first, last, nullptr);
    if (headContactList == nullptr){
        headContactList = newContact; //For empty list
    }
    else {
        currentContact = headContactList; //Find last contact in the list
        while (currentContact->next != nullptr){
            currentContact = currentContact->next;
        }
        currentContact->next = newContact; //Append new contact
    }
    count++;
    return true;
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Contact *currentContact = headContactList;

    while (currentContact != nullptr){
        if (currentContact->first == first && currentContact->last == last){//Finds if contact exists
            
            //Check if infoName exists
            Info *currentInfo = currentContact->headInfoList;
            while (currentInfo != nullptr){
                if (currentInfo->name == infoName){
                    currentInfo->value = infoVal; //2. Update infoVal
                    return true;
                }
                currentInfo = currentInfo->next;
            }

            //Info name DNE add to back of list
            Info *newInfo = new Info(infoName, infoVal, nullptr);
 
            if (currentContact->headInfoList == nullptr){ //List empty
                currentContact->headInfoList = newInfo;
            }
            else { //Find last info in list
                currentInfo = currentContact->headInfoList;
                while(currentInfo->next != nullptr){
                    currentInfo = currentInfo->next;
                }
                currentInfo->next = newInfo;
            }
            return true;
        }
        currentContact = currentContact->next;
    }
    
    return false;
}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended
bool ContactList::addContactOrdered(std::string first, std::string last) {
    Contact *currentContact = headContactList;
    Contact *previousContact = nullptr;
    
    //Part 1
    while (currentContact != nullptr){
        if (currentContact->first == first && currentContact->last == last){
            return false; // Contact already exists
        }
        if (last < currentContact->last || (last == currentContact->last && first < currentContact->first)){
            break; //Position to put new contact found
        }
        previousContact = currentContact;
        currentContact = currentContact->next;
    }

    //Part 2
    Contact *newContact = new Contact(first, last, nullptr);
    
    //List empty or new contact should be first one
    if (headContactList == nullptr || previousContact == nullptr){
        newContact->next = headContactList;
        headContactList = newContact; //For empty list
    }
    else { //Insert between prev and cur info
        previousContact->next = newContact;
        newContact->next = currentContact;
    }
    count++;
    return true;
}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Contact *currentContact = headContactList;

    while (currentContact != nullptr){
        if (currentContact->first == first && currentContact->last == last){//Finds if contact exists
            
            //Check if infoName exists
            Info *currentInfo = currentContact->headInfoList;
            Info *previousInfo = nullptr;

            while (currentInfo != nullptr){
                if (currentInfo->name == infoName){
                    currentInfo->value = infoVal; //2. Update infoVal
                    return true;
                }
                if (infoName < currentInfo->name){
                    break; //Position to put new info found
                }
                previousInfo = currentInfo;
                currentInfo = currentInfo->next;
            }

            //Info name DNE add to back of list
            Info *newInfo = new Info(infoName, infoVal, nullptr);
 
            if (currentContact->headInfoList == nullptr || previousInfo == nullptr){ //List empty
                newInfo->next = currentContact->headInfoList;
                currentContact->headInfoList = newInfo;
            }
            else { //Insert between prev and cur info
                previousInfo->next = newInfo;
                newInfo->next = currentInfo;
            }
            return true;
        }
        currentContact = currentContact->next;
    }
    
    return false;
}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) {
    Contact *currentContact = headContactList;
    Contact *previousContact = nullptr;
    
    //Part 1
    while (currentContact != nullptr){
        if (currentContact->first == first && currentContact->last == last){
            if (previousContact == nullptr){
                headContactList = currentContact->next; //Remove 1st item in list
            }
            else{
                previousContact->next = currentContact->next;
            }
            delete currentContact;
            count--;
            return true;
        }
        previousContact = currentContact;
        currentContact = currentContact->next;
    }
    
    return false;
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
    Contact *currentContact = headContactList;

    while (currentContact != nullptr){
        if (currentContact->first == first && currentContact->last == last){
            Info *currentInfo = currentContact->headInfoList;
            Info *previousInfo = nullptr;
            while (currentInfo != nullptr){
                if (currentInfo->name == infoName){
                    if (previousInfo == nullptr){ // 1st info in list
                        currentContact->headInfoList = currentInfo->next;
                    }
                    else{
                        previousInfo->next = currentInfo->next;
                    }
                    delete currentInfo;
                    return true;
                }
                previousInfo = currentInfo;
                currentInfo = currentInfo->next;
            }
            return false; // Info not in contact
        }
        currentContact = currentContact->next;
    }
    
    return false;
}

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() {
    Contact *currentContact = headContactList;

    while (currentContact != nullptr){
        Info *currentInfo = currentContact->headInfoList;
        
        while(currentInfo != nullptr){ // For info
            Info *nextInfo = currentInfo->next;
            delete currentInfo;
            currentInfo = nextInfo;
        }
        Contact *nextContact = currentContact->next; // For contact
        delete currentContact;
        currentContact = nextContact;
    }
    //Reset
    headContactList = nullptr;
    count = 0;
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src) {
    headContactList = nullptr;
    count = 0;

    Contact *srcContact = src.headContactList; // Copy each contact and info node
    Contact *previousContact = nullptr;

    while (srcContact != nullptr){
        Contact *newContact = new Contact(srcContact->first, srcContact->last, nullptr); // New contact node to copy info
        if (previousContact == nullptr){
            headContactList = newContact; // Set head of list
        }
        else{
            previousContact->next = newContact; // Link previous contact to new
        }
        Info *srcInfo = srcContact->headInfoList; // Info node with current contact
        Info *previouInfo = nullptr;

        while (srcInfo != nullptr){
            Info *newInfo = new Info(srcInfo->name, srcInfo->value, nullptr); // New info node to copy info
            if (previouInfo == nullptr){
                newContact->headInfoList = newInfo; // Set head of list
            }
            else{
                previouInfo->next = newInfo; // Link previous info node to new
            }
            previouInfo = newInfo;
            srcInfo = srcInfo->next;
        }
        previousContact = newContact;
        srcContact = srcContact->next;
    }
    count = src.count; // Update count
}

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src) {
    if (this != &src) {
        
        // Remove all contacts and info from current list
        Contact *currentContact = headContactList;
        while (currentContact != nullptr){
            Info *currentInfo = currentContact->headInfoList;
            while (currentInfo != nullptr){
                Info *tempInfo = currentInfo;
                currentInfo = currentInfo-> next;
                delete tempInfo;
            }
            Contact *tempContact = currentContact;
            currentContact = currentContact->next;
            delete tempContact;
        }

        // Deep copy
        headContactList = nullptr;
        count = 0;

        Contact *srcContact = src.headContactList; // Copy each contact and info node
        Contact *previousContact = nullptr;

         while (srcContact != nullptr){
        Contact *newContact = new Contact(srcContact->first, srcContact->last, nullptr); // New contact node to copy info
        if (previousContact == nullptr){
            headContactList = newContact; // Set head of list
        }
        else{
            previousContact->next = newContact; // Link previous contact to new
        }
        Info *srcInfo = srcContact->headInfoList; // Info node with current contact
        Info *previouInfo = nullptr;

        while (srcInfo != nullptr){
            Info *newInfo = new Info(srcInfo->name, srcInfo->value, nullptr); // New info node to copy info
            if (previouInfo == nullptr){
                newContact->headInfoList = newInfo; // Set head of list
            }
            else{
                previouInfo->next = newInfo; // Link previous info node to new
            }
            previouInfo = newInfo;
            srcInfo = srcInfo->next;
        }
        previousContact = newContact;
        srcContact = srcContact->next;
    }
    count = src.count; // Update count
    }
    return *this;
}