
#include "ConfirmationSender.h"

namespace sdds {
    // Destructor
    ConfirmationSender::~ConfirmationSender() { delete[] m_reservations; }

    // Default Constructor
    ConfirmationSender::ConfirmationSender() {
        ; // Intentionally blank
    }

    // Copy constructor
    ConfirmationSender::ConfirmationSender(const ConfirmationSender& cs) {
        *this = cs;
    }

    // Move constructor
    ConfirmationSender::ConfirmationSender(ConfirmationSender&& cs) {
        *this = std::move(cs);
    }

    // Copy assignment operator
    ConfirmationSender&
        ConfirmationSender::operator=(const ConfirmationSender& cs) {
        if (this != &cs) {
            delete[] m_reservations;
            m_count = cs.m_count;
            m_reservations = new const Reservation * [m_count];
            for (size_t i = 0; i < m_count; i++) {
                m_reservations[i] = cs.m_reservations[i];
            }
        }
        return *this;
    }

    // Move assignment operator
    ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& cs) {
        if (this != &cs) {
            delete[] m_reservations;
            m_count = cs.m_count;
            m_reservations = cs.m_reservations;
            cs.m_reservations = nullptr;
            cs.m_count = 0;
        }
        return *this;
    }

    // Add a reservation to the array of reservation pointers if the address doesn't
    // already exist in the array. Resizes the array to fit.
    ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
        bool exists = false;
        // Check if the address already exists in the array
        for (size_t i = 0; i < m_count && !exists; i++) {
            if (m_reservations[i] == &res) {
                exists = true;
            }
        }
        // If it doesn't already exist, add it
        if (!exists) {
            const Reservation** temp = new const Reservation * [m_count + 1];
            for (size_t i = 0; i < m_count; i++) {
                temp[i] = m_reservations[i];
            }
            temp[m_count++] = &res;
            delete[] m_reservations;
            m_reservations = temp;
        }
        return *this;
    }

    // Remove a reservation from the array of reservation pointers. Shuffle the
    // pointers in the queue after removal and reduce the size of the array by 1.
    ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {
        bool exists = false;
        size_t i;
        // Check if the address already exists
        for (i = 0; i < m_count && !exists; i++) {
            if (m_reservations[i] == &res) {
                exists = true;
            }
        }
        // resized array.
        if (exists) {
            const Reservation** temp = new const Reservation * [m_count - 1];
            i--;
            --m_count;
            for (size_t j = i; j < m_count; j++) {
                m_reservations[j] = m_reservations[j + 1];
            }
            for (size_t j = 0; j < m_count; j++) {
                temp[j] = m_reservations[j];
            }
            delete[] m_reservations;
            m_reservations = temp;
        }

        return *this;
    }

    // Insertion operator overload, displayed formatted output
    std::ostream& operator<<(std::ostream& os, const ConfirmationSender& cs) {
        os << "--------------------------\nConfirmations to "
            "Send\n--------------------------\n";
        if (cs.m_count > 0) {
            for (size_t i = 0; i < cs.m_count; i++) {
                os << *cs.m_reservations[i];
            }
        }
        else {
            os << "There are no confirmations to send!\n";
        }
        os << "--------------------------\n";

        return os;
    }
}
