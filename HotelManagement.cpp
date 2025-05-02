#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <stdexcept>
#include "HotelManagement.h"
#include "Global.h"

using namespace std;

const int MIN_YEAR = 2023;
const int MAX_YEAR = 2030;

int calculateNights(const string& checkIn, const string& checkOut) {
    try {
        int inYear = stoi(checkIn.substr(0, 4));
        int inMonth = stoi(checkIn.substr(5, 2));
        int inDay = stoi(checkIn.substr(8, 2));

        int outYear = stoi(checkOut.substr(0, 4));
        int outMonth = stoi(checkOut.substr(5, 2));
        int outDay = stoi(checkOut.substr(8, 2));

        return (outYear - inYear) * 365 + (outMonth - inMonth) * 30 + (outDay - inDay);
    } catch (...) {
        return 0;
    }
}

void HotelManagement::checkIn() {
    int roomNumber;
    cout << "\n=== Guest Check-In ===" << endl;
    cout << "Enter Room Number: ";

    while (!(cin >> roomNumber)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid input. Please enter a number: ";
    }

    Room* targetRoom = nullptr;
    for (int i = 0; i < currentRoomCount; ++i) {
        if (roomInventory[i].roomNumber == roomNumber) {
            targetRoom = &roomInventory[i];
            break;
        }
    }

    if (!targetRoom) {
        cerr << "Error: Room " << roomNumber << " does not exist." << endl;
        return;
    }
    if (targetRoom->isOccupied) {
        cerr << "Error: Room " << roomNumber << " is already occupied." << endl;
        return;
    }

    cout << "\nEnter Guest Details:" << endl;
    cout << "Booking ID (6 digits): ";
    while (!(cin >> targetRoom->guest.bookingId) ||
           targetRoom->guest.bookingId < 100000 ||
           targetRoom->guest.bookingId > 999999) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid ID. Enter 6-digit number: ";
    }
    cin.ignore();

    cout << "Full Name: ";
    getline(cin, targetRoom->guest.fullName);

    cout << "Address: ";
    getline(cin, targetRoom->guest.address);

    cout << "Phone Number: ";
    getline(cin, targetRoom->guest.phoneNumber);

    auto isValidDate = [](const string& date) {
        try {
            if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;
            int y = stoi(date.substr(0, 4));
            int m = stoi(date.substr(5, 2));
            int d = stoi(date.substr(8, 2));
            return (y >= MIN_YEAR && y <= MAX_YEAR) && (m >= 1 && m <= 12) && (d >= 1 && d <= 31);
        } catch (...) {
            return false;
        }
    };

    do {
        cout << "Check-In Date (YYYY-MM-DD): ";
        getline(cin, targetRoom->guest.checkInDate);
    } while (!isValidDate(targetRoom->guest.checkInDate));

    do {
        cout << "Check-Out Date (YYYY-MM-DD): ";
        getline(cin, targetRoom->guest.checkOutDate);
    } while (!isValidDate(targetRoom->guest.checkOutDate));

    cout << "Advance Payment: $";
    while (!(cin >> targetRoom->guest.advancePayment) || targetRoom->guest.advancePayment < 0) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid amount. Enter positive value: ";
    }

    targetRoom->isOccupied = true;

    ofstream logFile("CheckInLog.txt", ios::app);
    if (logFile) {
        time_t now = time(nullptr);
        logFile << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S") << " | "
                << "Room: " << setw(4) << roomNumber << " | "
                << "Guest: " << left << setw(30) << targetRoom->guest.fullName.substr(0, 30) << " | "
                << "Nights: " << setw(3) << calculateNights(targetRoom->guest.checkInDate,
                                                            targetRoom->guest.checkOutDate) << " | "
                << "Payment: $" << fixed << setprecision(2) << targetRoom->guest.advancePayment << endl;
        logFile.close();
    }

    cout << "\nCheck-in successful for Room " << roomNumber << endl;
}

void HotelManagement::checkOut(int roomNumber) {
    cout << "\n=== Guest Check-Out ===" << endl;

    Room* targetRoom = nullptr;
    for (int i = 0; i < currentRoomCount; ++i) {
        if (roomInventory[i].roomNumber == roomNumber) {
            targetRoom = &roomInventory[i];
            break;
        }
    }

    if (!targetRoom) {
        cerr << "Error: Room " << roomNumber << " does not exist." << endl;
        return;
    }
    if (!targetRoom->isOccupied) {
        cerr << "Error: Room " << roomNumber << " is not occupied." << endl;
        return;
    }

    int nightsStayed;
    cout << "Enter actual nights stayed: ";
    while (!(cin >> nightsStayed) || nightsStayed <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid input. Enter positive number: ";
    }

    float totalBill = nightsStayed * targetRoom->dailyRent;
    float balanceDue = totalBill - targetRoom->guest.advancePayment;

    cout << "\n=== Check-Out Receipt ===" << endl;
    cout << "Room Number: " << targetRoom->roomNumber << endl;
    cout << "Guest Name: " << targetRoom->guest.fullName << endl;
    cout << "Check-In Date: " << targetRoom->guest.checkInDate << endl;
    cout << "Nights Stayed: " << nightsStayed << endl;
    cout << "Daily Rate: $" << fixed << setprecision(2) << targetRoom->dailyRent << endl;
    cout << "Total Bill: $" << totalBill << endl;
    cout << "Advance Paid: $" << targetRoom->guest.advancePayment << endl;
    cout << "Balance Due: $" << max(0.0f, balanceDue) << endl;

    ofstream outFile("CheckOutReport.txt", ios::app);
    if (outFile) {
        time_t now = time(nullptr);
        outFile << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S") << " | "
                << "Room: " << setw(4) << roomNumber << " | "
                << "Guest: " << left << setw(30) << targetRoom->guest.fullName.substr(0, 30) << " | "
                << "Total: $" << fixed << setprecision(2) << setw(8) << totalBill << " | "
                << "Paid: $" << setw(8) << targetRoom->guest.advancePayment << " | "
                << "Due: $" << setw(8) << max(0.0f, balanceDue) << endl;
        outFile.close();
    }

    targetRoom->isOccupied = false;
    cout << "\nCheck-out completed for Room " << roomNumber << endl;
}

void HotelManagement::showAvailableRooms() {
    cout << "\n=== Available Rooms ===" << endl;
    bool found = false;

    for (int i = 0; i < currentRoomCount; ++i) {
        if (!roomInventory[i].isOccupied) {
            roomInventory[i].displayRoomDetails();
            found = true;
        }
    }

    if (!found) {
        cout << "No available rooms found." << endl;
    }
}

void HotelManagement::searchGuest(const string& name) {
    cout << "\n=== Guest Search ===" << endl;
    bool found = false;

    for (int i = 0; i < currentRoomCount; ++i) {
        if (roomInventory[i].isOccupied &&
            roomInventory[i].guest.fullName.find(name) != string::npos) {
            cout << "Found guest in Room " << roomInventory[i].roomNumber << endl;
            cout << "Details:" << endl;
            roomInventory[i].displayRoomDetails();
            found = true;
        }
    }

    if (!found) {
        cout << "No guests found matching '" << name << "'" << endl;
    }
}

void HotelManagement::guestSummary() {
    cout << "\n=== Guest Summary ===" << endl;
    int count = 0;

    for (int i = 0; i < currentRoomCount; ++i) {
        if (roomInventory[i].isOccupied) {
            cout << "Room " << setw(4) << roomInventory[i].roomNumber << " | "
                 << left << setw(30) << roomInventory[i].guest.fullName.substr(0, 30) << " | "
                 << "Check-In: " << roomInventory[i].guest.checkInDate << " | "
                 << "Check-Out: " << roomInventory[i].guest.checkOutDate << endl;
            count++;
        }
    }

    cout << "\nTotal Guests: " << count << endl;
}

void HotelManagement::generateDailyReport() {
    ofstream reportFile("DailyReport.txt");
    if (!reportFile) {
        cerr << "Error creating report file." << endl;
        return;
    }

    time_t now = time(nullptr);
    reportFile << "=== Daily Report ===\n"
               << "Date: " << put_time(localtime(&now), "%Y-%m-%d") << "\n\n";

    int occupied = 0;
    float totalRevenue = 0;

    for (int i = 0; i < currentRoomCount; ++i) {
        if (roomInventory[i].isOccupied) {
            occupied++;
            int nights = calculateNights(roomInventory[i].guest.checkInDate,
                                         roomInventory[i].guest.checkOutDate);
            totalRevenue += nights * roomInventory[i].dailyRent;
        }
    }

    reportFile << "Occupancy: " << occupied << "/" << currentRoomCount
               << " (" << fixed << setprecision(1)
               << (100.0 * occupied / currentRoomCount) << "%)\n";
    reportFile << "Projected Revenue: $" << fixed << setprecision(2) << totalRevenue << "\n\n";

    reportFile << "=== Guest List ===\n";
    for (int i = 0; i < currentRoomCount; ++i) {
        if (roomInventory[i].isOccupied) {
            reportFile << roomInventory[i].roomNumber << " | "
                       << left << setw(25) << roomInventory[i].guest.fullName.substr(0, 25) << " | "
                       << roomInventory[i].guest.checkOutDate << "\n";
        }
    }

    reportFile.close();
    cout << "Daily report generated successfully." << endl;
}
