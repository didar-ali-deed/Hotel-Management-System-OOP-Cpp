#ifndef GLOBAL_H
#define GLOBAL_H

#include "Room.h"

/**
 * @file Global.h
 * @brief Contains global constants and declarations for room inventory management
 *
 * This header defines the maximum capacity of the hotel and provides external
 * declarations for the room inventory array and counter that are shared
 * across multiple compilation units.
 */

const int MAX_ROOMS = 100; ///< Maximum number of rooms the system can manage

extern Room roomInventory[MAX_ROOMS]; ///< Global array storing all room records
extern int currentRoomCount;          ///< Tracks number of rooms currently in inventory

/**
 * @note The room inventory is implemented as a fixed-size array for simplicity.
 * @note In a production environment, consider using std::vector or another dynamic container.
 */

#endif // GLOBAL_H
