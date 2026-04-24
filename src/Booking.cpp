//
// Created by Bianca Mihai on 24.04.2026.
//

#include "Booking.h"
#include "Guest.h"
#include "Accommodation.h"
#include<iostream>
#include <string>
using namespace std;

int Booking :: noBookings = 0;

Booking :: Booking() {
    noBookings++;
    bookingID = "B" + to_string(noBookings);
    nights = 0;
    room = nullptr;
    totalCost = 0.0;
    status = "PENDING";
}

Booking::Booking(Guest guest, Accommodation* room, Date checkin, Date checkout) {
    noBookings++;
    bookingID = "B" + to_string(noBookings);
    this->guest = guest;
    this->room = room;
    this->checkin = checkin;
    this->checkout = checkout;
    this->nights = calculateNights();
    this->totalCost = calculateTotalCost();
    this->status = "PENDING";
}

Booking::Booking(const Booking &obj) {
    this->bookingID = obj.bookingID;
    this->guest = obj.guest;
    this->room = obj.room;
    this->checkin = obj.checkin;
    this->checkout = obj.checkout;
    this->nights = obj.nights;
    this->totalCost = obj.totalCost;
    this->status = obj.status;
}
Booking &Booking::operator=(const Booking &obj) {
    if (this ==&obj)
        return *this;
    this->bookingID = obj.bookingID;
    this->guest = obj.guest;
    this->room = obj.room;
    this->checkin = obj.checkin;
    this->checkout = obj.checkout;
    this->nights = obj.nights;
    this->totalCost = obj.totalCost;
    this->status = obj.status;
    return *this;
}
Booking::~Booking() {
    noBookings--;
    room = nullptr;
}

std::string Booking::getBookingID() const {
    return bookingID;
}
int Booking::getNights() const {
    return nights;
}
Guest Booking::getGuest() const {
    return guest;
}
Accommodation* Booking::getRoom() const {
    return room;
}
Date Booking::getCheckin() const {
    return checkin;
}
Date Booking::getCheckout() const {
    return checkout;
}
double Booking::getTotalCost() const {
    return totalCost;
}
std::string Booking::getStatus() const{
    return status;
}
void Booking::setBookingID(const string& bookingID) {
    this->bookingID = bookingID;
}
void Booking::setNights(int nights) {
    this->nights = nights;
}
void Booking::setGuest(const Guest &guest) {
    this->guest = guest;
}
void Booking::setCheckin(const Date &checkin) {
    this->checkin = checkin;
}
void Booking::setCheckout(const Date &checkout) {
    this->checkout = checkout;
}
void Booking::setTotalCost(double totalCost) {
    this->totalCost = totalCost;
}
void Booking::setStatus(const std::string &status) {
    this->status = status;
}
int Booking::calculateNights() const {
    return checkout - checkin;
}

double Booking::calculateTotalCost() const {
    if (room == nullptr)
        return 0.0;
    return room->calculatePrice(nights);
}

void Booking::confirmBooking() {
    status = "CONFIRMED";
    room->setIsAvailable(false);
}

void Booking::cancelBooking() {
    status = "CANCELLED";
    room->setIsAvailable(true);
}
bool Booking :: hasDateConflict(const Date& newCheckIn, const Date& newCheckOut) const {
    return (newCheckIn < checkout && newCheckOut > checkin);
}

int Booking::getNoBookings() {
    return noBookings;
}

void Booking::displaySummary() {
    cout << "Booking ID: " << bookingID << endl;
    cout << "Guest: " << guest.getName() << endl;
    cout << "Room: " << room->getRoomType() << " - " << room->getRoomNumber() << endl;
    cout << "Check-in: " << checkin << endl;
    cout << "Check-out: " << checkout << endl;
    cout << "Nights: " << nights << endl;
    cout << "Total Cost: " << totalCost << " RON" << endl;
    cout << "Status: " << status << endl;
}
ostream& operator<<(ostream& out, const Booking& obj) {
    out << "Booking ID: " << obj.bookingID << endl;
    out << "Guest: " << obj.guest.getName() << endl;
    out << "Room: " << obj.room->getRoomType() << " - " << obj.room->getRoomNumber() << endl;
    out << "Check-in: " << obj.checkin << endl;
    out << "Check-out: " << obj.checkout << endl;
    out << "Nights: " << obj.nights << endl;
    out << "Total Cost: " << obj.totalCost << " RON" << endl;
    out << "Status: " << obj.status << endl;
    return out;
}
istream& operator>>(istream& in, Booking& obj) {
    cout << "Check-in date:" << endl;
    in >> obj.checkin;
    cout << "Check-out date:" << endl;
    in >> obj.checkout;
    obj.nights = obj.calculateNights();
    obj.totalCost = obj.calculateTotalCost();
    return in;
}
