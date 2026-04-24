#include "Guest.h"
using namespace std;
Guest::Guest() {
    this->guestId=0;
    this->name="";
    this->email="";
    this->phone="";
    this->nationality="";
    this->totalBookings=0;
    this->isVip=false;
}

Guest::Guest(int guestId,const std::string &name,const std::string &email,const std::string &phone,
        const std::string &nationality,int totalBookings,bool isVip) {
    this->guestId=guestId;
    this->name=name;
    this->email=email;
    this->phone=phone;
    this->nationality=nationality;
    this->totalBookings=totalBookings;
    this->isVip=isVip;
}

Guest::Guest(const Guest &obj) {
    this->guestId=obj.guestId;
    this->name=obj.name;
    this->email=obj.email;
    this->phone=obj.phone;
    this->nationality=obj.nationality;
    this->totalBookings=obj.totalBookings;
    this->isVip=obj.isVip;
}

Guest &Guest::operator=(const Guest &obj) {
    if (this == &obj)
        return *this;
    this->guestId=obj.guestId;
    this->name=obj.name;
    this->email=obj.email;
    this->phone=obj.phone;
    this->nationality=obj.nationality;
    this->totalBookings=obj.totalBookings;
    this->isVip=obj.isVip;
    return *this;
}

Guest::~Guest(){}

int Guest::getGuestId() const {
    return guestId;
}

std::string Guest::getName() const {
    return name;
}
std::string Guest::getEmail() const {
    return email;
}
std::string Guest::getPhone() const {
    return phone;
}
std::string Guest::getNationality() const {
    return nationality;
}
int Guest::getTotalBookings() const {
    return totalBookings;
}
bool Guest::getIsVip() const{
    return isVip;
}
void Guest::setGuestId(int guestId) {
    this->guestId=guestId;
}
void Guest::setName(const std::string &name) {
    this->name=name;
}
void Guest::setEmail(const std::string &email) {
    this->email=email;
}
void Guest::setPhone(const std::string &phone) {
    this->phone=phone;
}
void Guest::setNationality(const std::string &nationality) {
    this->nationality=nationality;
}
void Guest::setTotalBookings(int totalBookings) {
    this->totalBookings=totalBookings;
}
void Guest::setIsVip(bool vip) {
    this->isVip=vip;
}

void Guest::incrementBookings() {
    totalBookings++;
    if (totalBookings >= 5)
        isVip = true;
}

ostream &operator<<(ostream &out,const Guest &obj) {
    out << "Name:" << obj.getName() << endl;
    out << "Email:" << obj.getEmail() << endl;
    out << "Phone Number:" << obj.getPhone() << endl;
    out << "Nationality:" << obj.getNationality() << endl;
    out << "Total Bookings:" << obj.getTotalBookings() << endl;
    out << "IsVip:" << (obj.getIsVip() ? "Yes" : "No") << endl;
    return out;
}

istream &operator>>(istream &in,Guest &obj) {
    cout<<"Enter Guest ID:";
    in >> obj.guestId;

    cout <<"Enter Name:";
    in.ignore();
    getline(in, obj.name);

    cout << "Enter Email:";
    in >> obj.email;

    cout << "Enter Phone Number:";
    in >> obj.phone;

    cout << "Enter Nationality:";
    in.ignore();
    getline(in, obj.nationality);

    return in;
}