#include <iostream>
#include <fstream>
#include <cctype>
#include <stdexcept>
#include "Room.h"
#include "Global.h"
using namespace std;

extern Room roomInventory[MAX_ROOMS];
extern int currentRoomCount;

Room Room::addRoom(int roomNumber) {
    for (int i = 0; i < currentRoomCount; ++i) {
        if (roomInventory[i].roomNumber == roomNumber) {
            throw runtime_error("Room number already exists");
        }
    }

    Room newRoom;
    newRoom.roomNumber = roomNumber;

    cout << "\nAdding New Room #" << roomNumber << endl;

    char acInput;
    cout << "Does the room have air conditioning? (Y/N): ";
    cin >> acInput;
    newRoom.hasAirConditioning = (toupper(acInput) == 'Y');

    cout << "Enter comfort level (S for Standard, D for Deluxe): ";
    cin >> newRoom.comfortLevel;
    newRoom.comfortLevel = toupper(newRoom.comfortLevel);

    cout << "Enter room size (S for Small, M for Medium, L for Large): ";
    cin >> newRoom.roomSize;
    newRoom.roomSize = toupper(newRoom.roomSize);

    cout << "Enter daily rate: ";
    cin >> newRoom.dailyRent;
    while (newRoom.dailyRent <= 0) {
        cout << "Invalid amount. Please enter positive value: ";
        cin >> newRoom.dailyRent;
    }

    newRoom.isOccupied = false;

    ofstream roomFile("RoomList.txt", ios::app);
    if (!roomFile) {
        throw runtime_error("Failed to open room database");
    }

    roomFile << newRoom.roomNumber << " "
             << newRoom.hasAirConditioning << " "
             << newRoom.comfortLevel << " "
             << newRoom.roomSize << " "
             << newRoom.dailyRent << "\n";
    roomFile.close();

    cout << "Room successfully added to inventory.\n";
    return newRoom;
}

void Room::searchRoom(int roomNumber) {
    for (int i = 0; i < currentRoomCount; ++i) {
        if (roomInventory[i].roomNumber == roomNumber) {
            cout << "\n=== Room Details ===" << endl;
            roomInventory[i].displayRoomDetails();
            return;
        }
    }
    cout << "Room #" << roomNumber << " not found in inventory.\n";
}

void Room::displayRoomDetails() const {
    cout << "Room Number: " << roomNumber << "\n"
         << "Air Conditioning: " << (hasAirConditioning ? "Yes" : "No") << "\n"
         << "Comfort Level: " << getComfortDescription() << "\n"
         << "Size: " << getRoomSizeDescription() << "\n"
         << "Daily Rate: $" << dailyRent << "\n"
         << "Status: " << (isOccupied ? "Occupied" : "Available") << "\n"
         << "----------------------------\n";
}

string Room::getRoomSizeDescription() const {
    switch (toupper(roomSize)) {
        case 'S': return "Small (1-2 persons)";
        case 'M': return "Medium (3-4 persons)";
        case 'L': return "Large (5+ persons)";
        default: return "Unknown Size";
    }
}

string Room::getComfortDescription() const {
    switch (toupper(comfortLevel)) {
        case 'S': return "Standard";
        case 'D': return "Deluxe";
        default: return "Unknown Comfort Level";
    }
}
