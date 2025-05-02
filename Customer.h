#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

/**
 * @class Customer
 * @brief Represents a hotel guest with complete personal and booking information
 *
 * This class serves as a data structure to store all relevant details about
 * hotel guests, facilitating reservation management and guest services.
 * All member variables are public for direct access by the Room class.
 */
class Customer {
public:
    string fullName;        ///< Complete legal name of the guest (first + last)
    string address;         ///< Full street address including city and country
    string phoneNumber;     ///< Contact number with country/area code
    string checkInDate;     ///< Arrival date in ISO 8601 format (YYYY-MM-DD)
    string checkOutDate;    ///< Departure date in ISO 8601 format (YYYY-MM-DD)
    float advancePayment;   ///< Amount paid in advance (positive currency value)
    int bookingId;          ///< Unique reservation identifier (6-digit number)

    // Optional: constructor for better initialization if desired
    Customer() : advancePayment(0), bookingId(0) {}

    /**
     * @note No methods are provided as this is purely a data container
     * @note All data validation should be handled by the Room or management logic
     */
};

#endif // CUSTOMER_H
