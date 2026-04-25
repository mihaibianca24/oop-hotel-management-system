#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_DELUXEROOM_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_DELUXEROOM_H

#include<iostream>
#include<string>
#include "StandardRoom.h"
class DeluxeRoom : public StandardRoom {
    bool hasSeaView;
    public:
    DeluxeRoom();
    DeluxeRoom(int roomNumber, double price, const std::string &description,
           const std::string &bedType, bool hasBalcony, int floor,
           bool hasSeaView);
    DeluxeRoom(const DeluxeRoom &obj);
    DeluxeRoom &operator=(const DeluxeRoom &obj);
    ~DeluxeRoom();

    bool getHasSeaView() const;
    void setHasSeaView(bool hasSeaView);

    std::string getRoomType() override;
    double calculatePrice(int nights) override;
    void displayInfo() override;
    DeluxeRoom* clone() const override;
};
#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_DELUXEROOM_H