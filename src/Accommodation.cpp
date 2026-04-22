#include "Accommodation.h"
using namespace std;
Accommodation :: Accommodation() {
    this->roomNumber = 0;
    this->pricePerNight = 0;
    this->isAvailable = false;
    this->description = "";
}

Accommodation::Accommodation(int roomNumber, double pricePerNight,string description) {
    this->roomNumber = roomNumber;
    this->pricePerNight = pricePerNight;
    this->isAvailable = true;
    this->description = description;
}

Accommodation :: Accommodation(const Accommodation &obj) {
    this->roomNumber = obj.roomNumber;
    this->pricePerNight = obj.pricePerNight;
    this->isAvailable = obj.isAvailable;
    this->description = obj.description;
}
Accommodation &Accommodation :: operator=(const Accommodation &obj) {
    if (this == &obj)
        return *this;
    this->roomNumber = obj.roomNumber;
    this->pricePerNight = obj.pricePerNight;
    this->isAvailable = obj.isAvailable;
    this->description = obj.description;
    return *this;
}
Accommodation::~Accommodation(){}

void Accommodation :: setRoomNumber(int roomNumber) {
    this->roomNumber = roomNumber;
}

int Accommodation :: getRoomNumber() const {
    return this->roomNumber;
}

void Accommodation :: setPricePerNight(double pricePerNight) {
    this->pricePerNight = pricePerNight;
}

double Accommodation :: getPricePerNight() const {
    return this->pricePerNight;
}

void Accommodation :: setDescription(const string &description) {
    this->description = description;
}

string Accommodation :: getDescription() const {
    return this->description;
}

void Accommodation :: setIsAvailable(bool available) {
    this->isAvailable = available;
}

bool Accommodation :: getIsAvailable() const {
    return this->isAvailable;
}

ostream &operator<<(std::ostream &out, const Accommodation &obj) {
    out << "Room Number: " << obj.getRoomNumber() << endl;
    out<< "Price Per Night: " << obj.getPricePerNight() << endl;
    out <<"Availability: " << obj.getIsAvailable() << endl;
    out <<"Description: " << obj.getDescription() << endl;
    return out;
}
istream &operator>>(std::istream &in, Accommodation &obj) {
    cout << "Enter room number: ";
    in >> obj.roomNumber;

    cout << "Enter price per night: ";
    in >> obj.pricePerNight;

    cout << "Enter availability(1 yes/0 no): ";
    in >> obj.isAvailable;

    in.ignore();
    cout << "Enter description: ";
    getline(in, obj.description);

    return in;
}