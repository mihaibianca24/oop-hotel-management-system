#include "StandardRoom.h"
#include "Accommodation.h"
using namespace std;
StandardRoom::StandardRoom() : Accommodation(){
   this->bedtype="";
   this->hasBalcony = false;
   this->floor=0;
}

StandardRoom::StandardRoom(int roomNumber, double price, std::string description, std::string bedtype, bool hasBalcony, int floor) : Accommodation(roomNumber,price,description) {
   this->bedtype=bedtype;
   this->hasBalcony=hasBalcony;
   this->floor=floor;
}

StandardRoom:: StandardRoom(const StandardRoom & obj) : Accommodation(obj) {
   this->bedtype=obj.bedtype;
   this->hasBalcony=obj.hasBalcony;
   this->floor=obj.floor;
}

StandardRoom & StandardRoom::operator=(const StandardRoom & obj) {
   if (this==&obj) return *this;
   Accommodation::operator=(obj);
   this->bedtype=obj.bedtype;
   this->hasBalcony=obj.hasBalcony;
   this->floor=obj.floor;
   return *this;
}

StandardRoom :: ~StandardRoom() {}

std::string StandardRoom::getBedType() const {
   return bedtype;
}

bool StandardRoom::getHasBalcony() const {
   return hasBalcony;
}

int StandardRoom::getFloor() const {
   return floor;
}

void StandardRoom::setBedType(const std::string &bedtype) {
   this->bedtype=bedtype;
}

void StandardRoom::setHasBalcony(bool hasBalcony) {
   this->hasBalcony=hasBalcony;
}

void StandardRoom::setFloor(int floor) {
   this->floor=floor;
}

std::string StandardRoom::getRoomType() {
   return "StandardRoom";
}

double StandardRoom::calculatePrice(int nights) {
   if (hasBalcony) {
      double price= (getPricePerNight()+0.2*getPricePerNight())*nights;
      return price;
   }
   return getPricePerNight()*nights;
}

void StandardRoom::displayInfo() {
   cout << *this;
   cout << "Room Type: " << getRoomType() << endl;
   cout << "Bed Type: " << bedtype << endl;
   cout << "Has Balcony: " << (hasBalcony ? "Yes" : "No") << endl;
   cout << "Floor: " << floor << endl;
}
StandardRoom* StandardRoom::clone() const {
   return new StandardRoom(*this);
}