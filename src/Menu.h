//
// Created by Bianca Mihai on 25.04.2026.
//

#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_MENU_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_MENU_H
#include "Hotel.h"

class Menu {
private:
    Hotel hotel;
    void roomManagement();
    void guestManagement();
    void bookingManagement();
    void reports();
    void addRoom();
    void removeRoom();
    void addGuest();
    void makeBooking();
    void confirmBooking();
    void cancelBooking();
public:
    Menu();
    void run();
};


#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_MENU_H