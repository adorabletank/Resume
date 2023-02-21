
#ifndef SDDS_RESERVATION_H
#define SDDS_RESERVATION_H

#include <iostream>
#include <string>

constexpr int ID_SIZE{ 11 }; // Size of 11 because reservation IDs are meant to be
                           // printed into a field of size 10.

namespace sdds {

    class Reservation
    {
        char m_id[ID_SIZE];
        std::string m_name;
        std::string m_email;
        unsigned m_guestCount;
        unsigned char m_day;  // Number between 1-28
        unsigned char m_hour; // Number between 1-24
    public:
        Reservation();
        Reservation(const std::string& res);
        void update(int day, int time);
        friend std::ostream& operator<<(std::ostream&, const Reservation&);
    };

} // namespace sdds

#endif
