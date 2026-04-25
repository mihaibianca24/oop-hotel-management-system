//
// Created by Bianca Mihai on 25.04.2026.
//

#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_HOTEL_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_HOTEL_H
#include <vector>
#include "Accommodation.h"
#include "Guest.h"
#include "Booking.h"

class Hotel {
private:
    std::string hotelName;
    std::string address;
    int starRating;
    std::vector<Accommodation*> rooms;
    std::vector<Guest> guests;
    std::vector<Booking> bookings;
    public:
    Hotel();
    Hotel(const std::string &hotelName,const std::string &adress,int starRating);
    Hotel(const Hotel &hotel);
    Hotel &operator=(const Hotel &hotel);
    ~Hotel();

    std::string getHotelName() const;
    std::string getAddress() const;
    int getStarRating() const;
    std::vector<Accommodation*> getRooms() const;
    std::vector<Guest> getGuests() const;
    std::vector<Booking> getBookings() const;

    void setHotelName(std::string hotelName);
    void setAddress(std::string address);
    void setStarRating(int starRating);
    void setRooms(std::vector<Accommodation*> rooms);
    void setGuests(std::vector<Guest> guests);
    void setBookings(std::vector<Booking> bookings);

    void addRoom(Accommodation* room);
    void removeRoom(int roomNumber);
    Accommodation* findRoom(int roomNumber);
    void displayAllRooms();
    void displayAvailableRooms();
    std::vector<Accommodation*> getAvailableRooms(Date checkIn, Date checkOut);

    void addGuest(const Guest& guest);
    Guest* findGuest(int guestId);
    void displayAllGuests();

    Booking* makeBooking(int guestId, int roomNumber, Date checkIn, Date checkOut);
    void confirmBooking(const std::string& bookingID);
    void cancelBooking(const std::string& bookingID);
    Booking* findBooking(const std::string& bookingID);
    void displayAllBookings();
    void displayGuestBookings(int guestId);

    void saveToFiles();
    void loadFromFiles();

    void displayOccupancyReport();

    int getTotalRooms();

    friend std::ostream &operator<<(std::ostream &os, const Hotel &obj);
    friend std::istream &operator>>(std::istream &os, Hotel &obj);
};


#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_HOTEL_H