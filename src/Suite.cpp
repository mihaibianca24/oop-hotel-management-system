#include "Suite.h"
#include "Accommodation.h"
using namespace std;

Suite :: Suite() : Accommodation() {
    this->suiteType=2;
    this->hasJacuzzi=false;
    this->hasPrivatePool=false;
    this->floor=0;
}

Suite :: Suite(int roomNumber, double pricePerNight,const std::string &description,
        int suiteType, bool hasJacuzzi, bool hasPrivatePool, int floor) :
        Accommodation(roomNumber, pricePerNight, description) {
    this->suiteType=suiteType;
    this->hasJacuzzi=hasJacuzzi;
    this->hasPrivatePool=hasPrivatePool;
    this->floor=floor;
}

Suite :: Suite(const Suite &obj) : Accommodation(obj) {
    this->suiteType=obj.suiteType;
    this->hasJacuzzi=obj.hasJacuzzi;
    this->hasPrivatePool=obj.hasPrivatePool;
    this->floor=obj.floor;
}

Suite &Suite :: operator=(const Suite &obj) {
    if (this == &obj)
        return *this;
    Accommodation::operator=(obj);
    this->suiteType=obj.suiteType;
    this->hasJacuzzi=obj.hasJacuzzi;
    this->hasPrivatePool=obj.hasPrivatePool;
    this->floor=obj.floor;
    return *this;
}

Suite::~Suite(){}

int Suite::getSuiteType() const {
    return suiteType;
}

bool Suite::getHasJacuzzi() const{
    return hasJacuzzi;
}
bool Suite::getHasPrivatePool() const {
    return hasPrivatePool;
}

int Suite::getFloor() const {
    return floor;
}

void Suite::setSuiteType(int suiteType) {
    if (suiteType >= 2 && suiteType <= 4)
        this->suiteType = suiteType;
    else
        this->suiteType = 2;
}

void Suite::setHasJacuzzi(bool hasJacuzzi) {
    this->hasJacuzzi=hasJacuzzi;
}

void Suite::setHasPrivatePool(bool hasPrivatePool) {
    this->hasPrivatePool=hasPrivatePool;
}

void Suite::setFloor(int floor) {
    this->floor=floor;
}

std::string Suite::getRoomType() {
    return "Suite";
}

double Suite::calculatePrice(int nights) {
    double price = getPricePerNight() * suiteType;
    if (hasJacuzzi)
        price += 0.30 * getPricePerNight();
    if (hasPrivatePool)
        price += 0.50 * getPricePerNight();
    return price * nights;
}

void Suite::displayInfo() {
    cout << *this;
    cout<< "Suite Type: " << getSuiteType() << " rooms" <<endl;
    cout << "Has Jacuzzi: " << (hasJacuzzi ? "Yes" : "No") << endl;
    cout << "Has Private Pool: " << (hasPrivatePool ? "Yes" : "No") << endl;
    cout << "Floor: " << floor << endl;
}
Suite* Suite::clone() const {
    return new Suite(*this);
}