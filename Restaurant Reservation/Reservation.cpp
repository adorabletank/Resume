#define _CRT_SECURE_NO_WARNINGS
#include "Reservation.h"
#include <cstring>

namespace sdds {
    // Default constructor
    Reservation::Reservation() {
        ; // intentionally empty
    }

    // Function used to trim whitespace from both ends of a string
    std::string& trim(std::string& str) {
        bool trimmed = false;

        while (!trimmed) {
            trimmed = true;
            if (str.find(' ') == 0) {
                trimmed = false;
                str.erase(str.begin());
            }
            if (str.substr(str.size() - 1, 1).find(' ') != std::string::npos) {
                str.erase(str.end() - 1);
                trimmed = false;
            }
        }
        return str;
    }

    // Parameterized constructor accepts a line of data from the data
    // file representing a reservation formatted as such:
    // ID:NAME,EMAIL,PARTY_SIZE,DAY,HOUR
    // Stores the data in the member variables.
    Reservation::Reservation(const std::string& res) {
        std::string temp = res; // Make a mutable copy to use .empty()

        size_t left = 0;             // Left side of the current token
        size_t right = res.find(":"); // Right side of the current token
        std::string id = temp.substr(left, right - left); // Extract id
        id = trim(id); // Temporary step due to m_id being a c string
        strcpy(m_id, id.c_str());
        // Step to the next token
        left = right;
        right = res.find(",", left + 1);
        m_name = res.substr(left + 1, right - left - 1); // Extract name
        m_name = trim(m_name);                           // Trim whitespace
        left = right;
        right = res.find(",", left + 1); // Step to next token
        m_email = res.substr(left + 1, right - left - 1);
        m_email = trim(m_email);
        left = right;
        right = res.find(",", left + 1);
        m_guestCount = std::stoi(res.substr(
            left + 1, right - left - 1)); // stoi can trim whitespace on its own
        left = right;
        right = res.find(",", left + 1);
        m_day = std::stoi(res.substr(left + 1, right - left - 1));
        left = right;
        right = res.find('\n', left + 1);
        m_hour = std::stoi(res.substr(left + 1));
    }

    // A setter for the day and hour member variables
    void Reservation::update(int day, int time) {
        m_day = day;
        m_hour = time;
    }

    std::ostream& operator<<(std::ostream& os, const Reservation& res) {
        os << "Reservation ";
        os.width(10);
        os << std::right << res.m_id << ": ";
        os.width(20);
        os << std::right << res.m_name;
        os << std::left << "  <" << std::left << res.m_email << "> ";
        for (int i = res.m_email.length(); i <= 20; i++) {
            os << " ";
        }

        if (res.m_hour >= 6 && res.m_hour <= 9) {
            os << "Breakfast ";
        }
        else if (res.m_hour >= 11 && res.m_hour <= 15) {
            os << "Lunch ";
        }
        else if (res.m_hour >= 17 && res.m_hour <= 21) {
            os << "Dinner ";
        }
        else {
            os << "Drinks ";
        }
        os << "on day " << (int)res.m_day << " @ " << (int)res.m_hour << ":00 for "
            << res.m_guestCount
            << (res.m_guestCount == 1 ? " person.\n" : " people.\n");
        return os;
    }
}
