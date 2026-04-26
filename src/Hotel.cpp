//
// Created by Bianca Mihai on 25.04.2026.
//

#include "Hotel.h"
#include"DeluxeRoom.h"
#include"Suite.h"
#include "StandardRoom.h"
#include <algorithm>
#include <vector>
#include <fstream>
Hotel::Hotel() {
    this->hotelName="";
    this->address="";
    this->starRating=1;
}
Hotel::Hotel(const std::string &hotelName,const std::string &adress,int starRating) {
    this->hotelName=hotelName;
    this->address=adress;
    this->starRating=starRating;
}
Hotel::Hotel(const Hotel &obj){
    this->hotelName=obj.hotelName;
    this->address=obj.address;
    this->starRating=obj.starRating;
    this->guests=obj.guests;
    this->bookings=obj.bookings;
    for (auto room : obj.rooms)
        this->rooms.push_back(room->clone());
}
Hotel &Hotel::operator=(const Hotel &obj) {
    if (this == &obj) return *this;
    for (auto room : rooms)
        delete room;
    rooms.clear();
    this->hotelName = obj.hotelName;
    this->address = obj.address;
    this->starRating = obj.starRating;
    this->guests = obj.guests;
    this->bookings = obj.bookings;
    for (auto room : obj.rooms)
        this->rooms.push_back(room->clone());
    return *this;
}
Hotel::~Hotel() {
    for (auto room : rooms)
        delete room;
    rooms.clear();
}

std::string Hotel::getHotelName() const {
    return hotelName;
}
void Hotel::setHotelName(std::string hotelName) {
    this->hotelName=hotelName;
}
std::string Hotel::getAddress() const {
    return address;
}
void Hotel::setAddress(std::string address) {
    this->address=address;
}
int Hotel::getStarRating() const {
    return starRating;
}
void Hotel::setStarRating(int starRating) {
    this->starRating=starRating;
}
std::vector<Accommodation*> Hotel::getRooms() const {
    return rooms;
}
void Hotel::setRooms(std::vector<Accommodation*> rooms) {
    this->rooms=rooms;
}
std::vector<Guest> Hotel::getGuests() const {
    return guests;
}
void Hotel::setGuests(std::vector<Guest> guests) {
    this->guests=guests;
}
std::vector<Booking> Hotel::getBookings() const {
    return bookings;
}
void Hotel::setBookings(std::vector<Booking> bookings) {
    this->bookings=bookings;
}

void Hotel::addRoom(Accommodation *room) {
    if (findRoom(room->getRoomNumber()) != nullptr) {
        throw std::runtime_error("Room with this number already exists!");
    }
    this->rooms.push_back(room);
}
Accommodation* Hotel::findRoom(int roomNumber) {
    for (auto room : rooms)
        if (room->getRoomNumber() == roomNumber)
            return room;
    return nullptr;
}

void Hotel::removeRoom(int roomNumber) {
    auto it = std::find_if(rooms.begin(), rooms.end(),
        [roomNumber](Accommodation* room) {
            return room->getRoomNumber() == roomNumber;
        });
    if (it == rooms.end())
        throw std::runtime_error("Room not found!");
    delete *it;
    rooms.erase(it);
}

void Hotel::displayAllRooms() {
    if (rooms.empty())
        throw std::runtime_error("No rooms!");
    std::cout << "All Rooms :" << std::endl;
    for (auto room : rooms) {
        room->displayInfo();
        std::cout << "-------------------" << std::endl;
    }
}

void Hotel::displayAvailableRooms() {
    if (rooms.empty())
        throw std::runtime_error("No rooms available!");
    std::cout << "Available Rooms :" << std::endl;
    bool found = false;
    for (auto room : rooms) {
        if (room->getIsAvailable()) {
            room->displayInfo();
            std::cout << "-------------------" << std::endl;
            found = true;
        }
    }
    if (found==false) std::cout <<"No rooms available at the moment!" << std::endl;
}
std::vector<Accommodation*> Hotel::getAvailableRooms(Date checkIn,Date checkOut) {
    std::vector<Accommodation*> availableRooms;

    for (auto room : rooms) {
        bool hasConflict = false;

        for (auto& booking : bookings) {
            if (booking.getRoom()->getRoomNumber() == room->getRoomNumber()
                && booking.getStatus() != "CANCELLED"
                && booking.hasDateConflict(checkIn, checkOut)) {
                hasConflict = true;
                break;
                }
        }

        if (!hasConflict)
            availableRooms.push_back(room);
    }
    return availableRooms;
}
Guest* Hotel::findGuest(int guestId) {
    for (auto& guest : guests)
        if (guest.getGuestId() == guestId)
            return &guest;
    return nullptr;
}
void Hotel::addGuest(const Guest &guest) {
    if (findGuest(guest.getGuestId()) != nullptr) {
        throw std::runtime_error("Guest already exists!");
    }
    this->guests.push_back(guest);
}
void Hotel::displayAllGuests() {
    if (guests.empty())
        throw std::runtime_error("No guests available!");
    std::cout <<"All Guests:" << std::endl;
    for (auto &guest : guests) {
        std::cout<<guest;
        std::cout << "------------------" << std::endl;
    }

}

Booking *Hotel::makeBooking(int guestId, int roomNumber, Date checkIn, Date checkOut) {
    Guest* guest = findGuest(guestId);
    if (guest == nullptr)
        throw std::runtime_error("Guest not found!");

    Accommodation* room = findRoom(roomNumber);
    if (room == nullptr)
        throw std::runtime_error("Room not found!");

    if (checkOut <= checkIn)
        throw std::runtime_error("Invalid dates!");

    std::vector<Accommodation*> available = getAvailableRooms(checkIn, checkOut);
    bool roomAvailable = false;
    for (auto r : available)
        if (r->getRoomNumber() == roomNumber) {
            roomAvailable = true;
            break;
        }
    if (!roomAvailable)
        throw std::runtime_error("Room not available!");

    bookings.push_back(Booking(*guest, room, checkIn, checkOut));

    if (guest->getIsVip()) {
        double discountedCost = bookings.back().getTotalCost() * 0.90;
        bookings.back().setTotalCost(discountedCost);
        std::cout << "VIP discount applied! 10% off!" << std::endl;
    }

    guest->incrementBookings();

    return &bookings.back();
}

int Hotel::getTotalRooms() {
    return rooms.size();
}

Booking *Hotel::findBooking(const std::string &bookingID) {
    for (auto &booking : bookings) {
        if (booking.getBookingID() == bookingID)
            return &booking;
    }
    return nullptr;
}

void Hotel::confirmBooking(const std::string &bookingID) {
    Booking* booking=findBooking(bookingID);
    if (booking == nullptr)
        throw std::runtime_error("Booking not found!");
    if (booking->getStatus()=="CONFIRMED")
        throw std::runtime_error("Booking already confirmed!");
    if (booking->getStatus()=="CANCELLED")
        throw std::runtime_error("Booking already canceled!");
    booking->confirmBooking();
}
void Hotel::cancelBooking(const std::string &bookingID) {
    Booking* booking=findBooking(bookingID);
    if (booking == nullptr)
        throw std::runtime_error("Booking not found!");
    if (booking->getStatus()=="CANCELLED")
        throw std::runtime_error("Booking already canceled!");
    booking->cancelBooking();
}

void Hotel::displayAllBookings() {
    if (bookings.empty())
        throw std::runtime_error("No bookings found!");
    std::cout <<"All bookings:" << std::endl;
    for (auto &booking : bookings) {
        std::cout<<booking;
        std::cout <<"------------------" << std::endl;
    }
}

void Hotel::displayGuestBookings(int guestId) {
    if (findGuest(guestId) == nullptr)
        throw std::runtime_error("Guest not found!");
    if (bookings.empty())
        throw std::runtime_error("No bookings found!");
    bool found = false;
    std::cout <<"Guest's Bookings:" << std::endl;
    for (auto &booking : bookings) {
        if (booking.getGuest().getGuestId() == guestId) {
            std::cout<<booking;
            std::cout <<"------------------" << std::endl;
            found=true;
        }
    }
    if (!found)
        std::cout << "No bookings found for this guest!" << std::endl;
}
void Hotel::displayOccupancyReport() {
    if (rooms.empty())
        throw std::runtime_error("No rooms available!");

    int totalRooms = rooms.size();
    int occupiedRooms = 0;
    double totalRevenue = 0.0;
    int standardOccupied = 0;
    int deluxeOccupied = 0;
    int suiteOccupied = 0;

    for (auto& booking : bookings) {
        if (booking.getStatus() == "CONFIRMED") {
            totalRevenue += booking.getTotalCost();
        }
    }

    for (auto room : rooms) {
        if (!room->getIsAvailable()) {
            occupiedRooms++;
            if (dynamic_cast<DeluxeRoom*>(room) != nullptr)
                deluxeOccupied++;
            else if (dynamic_cast<StandardRoom*>(room) != nullptr)
                standardOccupied++;
            else if (dynamic_cast<Suite*>(room) != nullptr)
                suiteOccupied++;
        }
    }

    double occupancyRate = 0.0;
    if (totalRooms > 0)
        occupancyRate = static_cast<double>(occupiedRooms) / totalRooms * 100;

    std::cout << "Occupancy Report:" << std::endl;
    std::cout << "Total rooms: " << totalRooms << std::endl;
    std::cout << "Occupied rooms: " << occupiedRooms << std::endl;
    std::cout << "Available rooms: " << totalRooms - occupiedRooms << std::endl;
    std::cout << "Occupancy rate: " << occupancyRate << "%" << std::endl;
    std::cout << "Total revenue: " << totalRevenue << " RON" << std::endl;
    std::cout << "By room type :" << std::endl;
    std::cout << "Standard: " << standardOccupied << " occupied" << std::endl;
    std::cout << "Deluxe: " << deluxeOccupied << " occupied" << std::endl;
    std::cout << "Suite: " << suiteOccupied << " occupied" << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Hotel& obj) {
    out << "Hotel: " << obj.hotelName << std::endl;
    out << "Address: " << obj.address << std::endl;
    out << "Star Rating: " << obj.starRating << std::endl;
    out << "Total Rooms: " << obj.rooms.size() << std::endl;
    out << "Total Guests: " << obj.guests.size() << std::endl;
    out << "Total Bookings: " << obj.bookings.size() << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Hotel& obj) {
    std::cout << "Enter hotel name: ";
    std::getline(in, obj.hotelName);
    std::cout << "Enter address: ";
    std::getline(in, obj.address);
    std::cout << "Enter star rating (1-5): ";
    in >> obj.starRating;
    in.ignore();
    return in;
}
void Hotel::saveToFiles() {
    std::ofstream roomsFile("rooms.txt");
    if (!roomsFile.is_open())
        throw std::runtime_error("Cannot open rooms.txt!");
    for (auto room : rooms) {
        roomsFile << room->getRoomType() << "\n";
        roomsFile << room->getRoomNumber() << "\n";
        roomsFile << room->getPricePerNight() << "\n";
        roomsFile << room->getDescription() << "\n";
        roomsFile << room->getIsAvailable() << "\n";

        DeluxeRoom* deluxe = dynamic_cast<DeluxeRoom*>(room);
        StandardRoom* standard = dynamic_cast<StandardRoom*>(room);
        Suite* suite = dynamic_cast<Suite*>(room);

        if (deluxe != nullptr) {
            roomsFile << deluxe->getBedType() << "\n";
            roomsFile << deluxe->getHasBalcony() << "\n";
            roomsFile << deluxe->getFloor() << "\n";
            roomsFile << deluxe->getHasSeaView() << "\n";
        } else if (standard != nullptr) {
            roomsFile << standard->getBedType() << "\n";
            roomsFile << standard->getHasBalcony() << "\n";
            roomsFile << standard->getFloor() << "\n";
        } else if (suite != nullptr) {
            roomsFile << suite->getSuiteType() << "\n";
            roomsFile << suite->getHasJacuzzi() << "\n";
            roomsFile << suite->getHasPrivatePool() << "\n";
            roomsFile << suite->getFloor() << "\n";
        }
    }
    roomsFile.close();

    std::ofstream guestsFile("guests.txt");
    if (!guestsFile.is_open())
        throw std::runtime_error("Cannot open guests.txt!");

    for (auto& guest : guests) {
        guestsFile << guest.getGuestId() << "\n";
        guestsFile << guest.getName() << "\n";
        guestsFile << guest.getEmail() << "\n";
        guestsFile << guest.getPhone() << "\n";
        guestsFile << guest.getNationality() << "\n";
        guestsFile << guest.getTotalBookings() << "\n";
        guestsFile << guest.getIsVip() << "\n";
    }
    guestsFile.close();

    std::ofstream bookingsFile("bookings.txt");
    if (!bookingsFile.is_open())
        throw std::runtime_error("Cannot open bookings.txt!");

    for (auto& booking : bookings) {
        bookingsFile << booking.getBookingID() << "\n";
        bookingsFile << booking.getGuest().getGuestId() << "\n";
        bookingsFile << booking.getRoom()->getRoomNumber() << "\n";
        bookingsFile << booking.getCheckin().getDay() << "\n";
        bookingsFile << booking.getCheckin().getMonth() << "\n";
        bookingsFile << booking.getCheckin().getYear() << "\n";
        bookingsFile << booking.getCheckout().getDay() << "\n";
        bookingsFile << booking.getCheckout().getMonth() << "\n";
        bookingsFile << booking.getCheckout().getYear() << "\n";
        bookingsFile << booking.getStatus() << "\n";
    }
    bookingsFile.close();
}

void Hotel::loadFromFiles() {
    for (auto room : rooms)
        delete room;
    rooms.clear();
    guests.clear();
    bookings.clear();

    std::ifstream roomsFile("rooms.txt");
    if (!roomsFile.is_open()) {
        return;
    }
    std::string type;
    while (std::getline(roomsFile, type)) {
        int roomNumber;
        double price;
        std::string description;
        bool isAvailable;

        roomsFile >> roomNumber;
        roomsFile >> price;
        roomsFile.ignore();
        std::getline(roomsFile, description);
        roomsFile >> isAvailable;
        roomsFile.ignore();

        if (type == "Standard Room") {
            std::string bedType;
            bool hasBalcony;
            int floor;
            std::getline(roomsFile, bedType);
            roomsFile >> hasBalcony >> floor;
            roomsFile.ignore();
            StandardRoom* room = new StandardRoom(roomNumber, price, description, bedType, hasBalcony, floor);
            room->setIsAvailable(isAvailable);
            rooms.push_back(room);
        } else if (type == "Deluxe Room") {
            std::string bedType;
            bool hasBalcony, hasSeaView;
            int floor;
            std::getline(roomsFile, bedType);
            roomsFile >> hasBalcony >> floor >> hasSeaView;
            roomsFile.ignore();
            DeluxeRoom* room = new DeluxeRoom(roomNumber, price, description, bedType, hasBalcony, floor, hasSeaView);
            room->setIsAvailable(isAvailable);
            rooms.push_back(room);
        } else if (type == "Suite") {
            int suiteType, floor;
            bool hasJacuzzi, hasPrivatePool;
            roomsFile >> suiteType >> hasJacuzzi >> hasPrivatePool >> floor;
            roomsFile.ignore();
            Suite* room = new Suite(roomNumber, price, description, suiteType, hasJacuzzi, hasPrivatePool, floor);
            room->setIsAvailable(isAvailable);
            rooms.push_back(room);
        }
    }
    roomsFile.close();

    std::ifstream guestsFile("guests.txt");
    if (!guestsFile.is_open())
        return;

    int guestId, totalBookings;
    bool isVip;
    std::string name, email, phone, nationality;

    while (guestsFile >> guestId) {
        guestsFile.ignore();
        std::getline(guestsFile, name);
        guestsFile >> email >> phone;
        guestsFile.ignore();
        std::getline(guestsFile, nationality);
        guestsFile >> totalBookings >> isVip;
        guestsFile.ignore();
        guests.push_back(Guest(guestId, name, email, phone, nationality, totalBookings, isVip));
    }
    guestsFile.close();

    std::ifstream bookingsFile("bookings.txt");
    if (!bookingsFile.is_open())
        return;

    std::string bookingID, status;
    int roomNumber;
    int checkInDay, checkInMonth, checkInYear;
    int checkOutDay, checkOutMonth, checkOutYear;

    while (std::getline(bookingsFile, bookingID)) {
        bookingsFile >> guestId >> roomNumber;
        bookingsFile >> checkInDay >> checkInMonth >> checkInYear;
        bookingsFile >> checkOutDay >> checkOutMonth >> checkOutYear;
        bookingsFile.ignore();
        std::getline(bookingsFile, status);

        Guest* guest = findGuest(guestId);
        Accommodation* room = findRoom(roomNumber);

        if (guest != nullptr && room != nullptr) {
            Date checkIn(checkInDay, checkInMonth, checkInYear);
            Date checkOut(checkOutDay, checkOutMonth, checkOutYear);
            Booking booking(bookingID, *guest, room, checkIn, checkOut, status);
            bookings.push_back(booking);
        }
    }
    bookingsFile.close();
    int maxId = 0;
    for (auto& booking : bookings) {
        std::string id = booking.getBookingID();
        int num = std::stoi(id.substr(1));
        if (num > maxId)
            maxId = num;
    }
}