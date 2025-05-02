#ifndef HOTEL_MANAGEMENT_H
#define HOTEL_MANAGEMENT_H

#include <string>

/**
 * @class HotelManagement
 * @brief Provides core hotel operations and guest management functionality
 *
 * This class serves as the main interface for all hotel operations including
 * guest check-in/check-out, room management, and reporting. It works with
 * the global room inventory to maintain hotel state.
 */
class HotelManagement {
public:
    /**
     * @brief Handles the guest check-in process
     * @note Guides user through entering guest details
     * @note Updates room status and creates check-in log entry
     */
    void checkIn();

    /**
     * @brief Handles the guest check-out process
     * @param roomNumber The room being vacated
     * @note Calculates final bill and updates room status
     * @note Generates checkout report with payment details
     */
    void checkOut(int roomNumber);

    /**
     * @brief Displays all currently available rooms
     * @note Shows detailed information for each vacant room
     */
    void showAvailableRooms();

    /**
     * @brief Searches for guest by name
     * @param name Full or partial name of guest to search for
     * @note Performs case-sensitive substring search
     * @note Displays room assignment if guest is found
     */
    void searchGuest(const std::string& name);

    /**
     * @brief Shows summary of all current guests
     * @note Displays compact list of occupied rooms
     * @note Includes room numbers, guest names, check-in, and check-out dates
     */
    void guestSummary();

    /**
     * @brief Generates daily occupancy report
     * @note Creates formatted report showing:
     *       - Total occupied/vacant rooms
     *       - Revenue projection
     *       - Guest list with check-out dates
     */
    void generateDailyReport();
};

#endif // HOTEL_MANAGEMENT_H
