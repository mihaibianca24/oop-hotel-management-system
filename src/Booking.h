//
// Created by Bianca Mihai on 24.04.2026.
//

#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_BOOKING_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_BOOKING_H
#include <string>
#include "Guest.h"
#include "Accommodation.h"
#include "Date.h"

class Booking {
private:
    std::string bookingID;
    static int noBookings;
    int nights;
    Guest guest;
    Accommodation* room;
    Date checkin;
    Date checkout;
    double totalCost;
    std::string status;
    public:
    Booking();
    Booking(Guest guest, Accommodation* room, Date checkin, Date checkout);
    Booking(const Booking &obj);
    Booking &operator=(const Booking &obj);
    ~Booking();

    std::string getBookingID() const;
    int getNights() const;
    Guest getGuest() const;
    Accommodation* getRoom() const;
    Date getCheckin() const;
    Date getCheckout() const;
    double getTotalCost() const;
    std::string getStatus() const;

    void setBookingID(const std::string &bookingID);
    void setNights(int nights);
    void setGuest(const Guest &guest);
    void setCheckin(const Date &checkin);
    void setCheckout(const Date &checkout);
    void setTotalCost(double totalCost);
    void setStatus(const std::string &status);

    double calculateTotalCost() const;
    void confirmBooking();
    void cancelBooking();
    int calculateNights() const;
    bool hasDateConflict(const Date& newCheckIn, const Date& newCheckOut) const;
    void displaySummary();
    static int getNoBookings();

    friend std::ostream &operator<<(std::ostream &os, const Booking &obj);
    friend std::istream &operator>>(std::istream &os, Booking &obj);
};


#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_BOOKING_H