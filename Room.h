#ifndef ROOM_H
#define ROOM_H

#include "Customer.h"
#include <string>

/**
 * @class Room
 * @brief Represents a hotel room with complete attributes and management functions
 *
 * This class models a physical hotel room, containing its properties,
 * current status, and guest information when occupied. It provides
 * core functionality for room management operations.
 */
class Room {
public:
    // Room Properties
    int roomNumber;             ///< Unique numeric identifier (1-9999)
    bool hasAirConditioning;    ///< Climate control availability flag
    char comfortLevel;          ///< 'S'tandard or 'D'eluxe classification
    char roomSize;              ///< 'S'mall, 'M'edium, or 'L'arge capacity
    int dailyRent;              ///< Price per night in local currency
    bool isOccupied;            ///< Current occupancy status flag
    Customer guest;             ///< Guest details when occupied

    // Room Management Functions

    /**
     * @brief Creates and adds a new room to inventory
     * @param roomNumber Unique identifier for the new room
     * @return Room object with all properties initialized
     * @note Automatically persists the new room to storage
     */
    Room addRoom(int roomNumber);

    /**
     * @brief Searches for a room by number
     * @param roomNumber The room identifier to search for
     * @note Displays complete room details if found
     */
    void searchRoom(int roomNumber);

    /**
     * @brief Displays formatted room information
     * @note Shows all attributes including translated enums
     */
    void displayRoomDetails() const;

    /**
     * @brief Converts room size code to descriptive string
     * @return Human-readable size description
     */
    std::string getRoomSizeDescription() const;

    /**
     * @brief Converts comfort level code to descriptive string
     * @return Human-readable comfort description
     */
    std::string getComfortDescription() const;
};

#endif // ROOM_H
