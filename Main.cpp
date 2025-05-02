#include <iostream>
#include <fstream>
#include <limits>
#include "Room.h"
#include "HotelManagement.h"
#include "Global.h"
using namespace std;

Room roomInventory[MAX_ROOMS];
int currentRoomCount = 0;

void loadRoomsFromFile() {
    ifstream file("RoomList.txt");
    if (!file) {
        cerr << "Error: Could not open RoomList.txt" << endl;
        return;
    }

    Room r;
    while (file >> r.roomNumber >> r.hasAirConditioning >> r.comfortLevel >> r.roomSize >> r.dailyRent) {
        r.isOccupied = false;
        if (currentRoomCount < MAX_ROOMS) {
            roomInventory[currentRoomCount++] = r;
        } else {
            cerr << "Warning: Maximum room capacity reached" << endl;
            break;
        }
    }
    file.close();
}

void manageRooms() {
    Room r;
    int choice, rno;
    do {
        cout << "\n1. Add Room\n2. Search Room\n3. Back\nChoice: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        if (choice == 1) {
            cout << "\nEnter room number: ";
            while (!(cin >> rno)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }
            try {
                if (currentRoomCount < MAX_ROOMS) {
                    roomInventory[currentRoomCount++] = r.addRoom(rno);
                } else {
                    cout << "Error: Maximum room capacity reached" << endl;
                }
            } catch (const runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
        } else if (choice == 2) {
            cout << "\nEnter room number to search: ";
            while (!(cin >> rno)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }
            r.searchRoom(rno);
        }
    } while (choice != 3);
}

int main() {
    HotelManagement hm;
    int opt, rno;
    string name;

    loadRoomsFromFile();

    do {
        cout << "\n--- Hotel Management Menu ---";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In";
        cout << "\n3. Check-Out";
        cout << "\n4. Available Rooms";
        cout << "\n5. Search Guest";
        cout << "\n6. Guest Summary";
        cout << "\n7. Generate Daily Report";
        cout << "\n8. Exit";
        cout << "\nChoice: ";
        while (!(cin >> opt)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }

        switch (opt) {
            case 1:
                manageRooms();
                break;
            case 2:
                hm.checkIn();
                break;
            case 3:
                cout << "\nEnter room number: ";
                while (!(cin >> rno)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number: ";
                }
                hm.checkOut(rno);
                break;
            case 4:
                hm.showAvailableRooms();
                break;
            case 5:
                cout << "\nEnter guest name: ";
                cin.ignore();
                getline(cin, name);
                hm.searchGuest(name);
                break;
            case 6:
                hm.guestSummary();
                break;
            case 7:
                hm.generateDailyReport();
                break;
            case 8:
                cout << "\nExiting...";
                break;
            default:
                cout << "\nInvalid option!";
        }
    } while (opt != 8);

    return 0;
}