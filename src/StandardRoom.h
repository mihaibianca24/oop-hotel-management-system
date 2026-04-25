#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_STANDARDROOM_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_STANDARDROOM_H

#include <iostream>
#include <string>
#include "Accommodation.h"
class StandardRoom : public Accommodation{
    std::string bedtype;
    bool hasBalcony;
    int floor;
    public:
    StandardRoom();
    StandardRoom(int roomNumber,double price,std::string description,std::string bedtype, bool hasBalcony, int floor);
    StandardRoom(const StandardRoom &obj);
    StandardRoom &operator=(const StandardRoom &obj);
    ~StandardRoom();

    std::string getBedType() const;
    bool getHasBalcony() const;
    int getFloor() const;

    void setBedType(const std::string &bedtype);
    void setHasBalcony(bool hasBalcony);
    void setFloor(int floor);

    std::string getRoomType() override;
    double calculatePrice(int nights) override;
    void displayInfo() override;
    StandardRoom* clone() const override;
};


#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_STANDARDROOM_H