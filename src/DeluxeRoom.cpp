#include "DeluxeRoom.h"
#include "StandardRoom.h"
using namespace std;
DeluxeRoom::DeluxeRoom() : StandardRoom(){
    this->hasSeaView=false;
}

DeluxeRoom::DeluxeRoom(int roomNumber, double price, const std::string &description,
    const std::string &bedType, bool hasBalcony,
    int floor, bool hasSeaView) : StandardRoom(roomNumber, price,
        description,bedType,hasBalcony,floor){

    this->hasSeaView=hasSeaView;
}

DeluxeRoom::DeluxeRoom(const DeluxeRoom &obj) : StandardRoom(obj){
    this->hasSeaView = obj.hasSeaView;
}
DeluxeRoom & DeluxeRoom::operator=(const DeluxeRoom &obj) {
    if (this == &obj)
        return *this;
    StandardRoom::operator=(obj);
    this->hasSeaView = obj.hasSeaView;
    return *this;
}

DeluxeRoom :: ~DeluxeRoom(){}

bool DeluxeRoom::getHasSeaView() const{
    return hasSeaView;
}

void DeluxeRoom::setHasSeaView(bool hasSeaView) {
    this->hasSeaView = hasSeaView;
}

std::string DeluxeRoom::getRoomType() {
    return "Deluxe Room";
}

double DeluxeRoom::calculatePrice(int nights) {
    double price = getPricePerNight();
    if (getHasBalcony())
        price += 0.20 * getPricePerNight();
    if (hasSeaView)
        price += 0.25 * getPricePerNight();
    return price * nights;
}

void DeluxeRoom::displayInfo() {
    cout << *this;
    cout << "Room Type: " << getRoomType() << endl;
    cout << "Bed Type: " << getBedType() << endl;
    cout << "Floor: " << getFloor() << endl;
    cout << "Has Balcony: " << (getHasBalcony() ? "Yes" : "No") << endl;
    cout << "Has Sea View: " << (hasSeaView ? "Yes" : "No") << endl;
}