//
// Created by Bianca Mihai on 25.04.2026.
//

#include "Menu.h"
#include "StandardRoom.h"
#include "DeluxeRoom.h"
#include "Suite.h"
#include "ConfigLoader.h"
#include <iostream>

using namespace std;

Menu::Menu() {}

void Menu::run() {
    hotel.loadFromFiles();
    int choice;
    do {
        cout << "\n Hotel Management System :" << endl;
        cout << "1. Room Management" << endl;
        cout << "2. Guest Management" << endl;
        cout << "3. Booking Management" << endl;
        cout << "4. Reports" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: roomManagement(); break;
            case 2: guestManagement(); break;
            case 3: bookingManagement(); break;
            case 4: reports(); break;
            case 0:
                hotel.saveToFiles();
                cout << "Progress saved. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    } while (choice != 0);
}

void Menu::roomManagement() {
    int choice;
    do {
        cout << "\n Room Management" << endl;
        cout << "1. Add Room" << endl;
        cout << "2. Remove Room" << endl;
        cout << "3. Display All Rooms" << endl;
        cout << "4. Display Available Rooms" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: addRoom(); break;
            case 2: removeRoom(); break;
            case 3:
                try {
                    hotel.displayAllRooms();
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 4:
                try {
                    hotel.displayAvailableRooms();
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 0: break;
            default: cout << "Invalid option!" << endl;
        }
    } while (choice != 0);
}

void Menu::addRoom() {
    ConfigLoader config("config.txt");

    int type;
    cout << "\n Add Room " << endl;
    cout << "1. Standard Room" << endl;
    cout << "2. Deluxe Room" << endl;
    cout << "3. Suite" << endl;
    cout << "Choice: ";
    cin >> type;
    cin.ignore();

    int roomNumber;
    cout << "Room number: ";
    cin >> roomNumber;
    cin.ignore();

    try {
        if (type == 1) {
            double price = config.getDouble("standard_price", 150.0);
            string bedType, description;
            bool hasBalcony;
            int floor;
            cout << "Description: ";
            getline(cin, description);
            cout << "Bed type (Single/Double/King): ";
            getline(cin, bedType);
            cout << "Has balcony (1/0): ";
            cin >> hasBalcony;
            cout << "Floor: ";
            cin >> floor;
            cin.ignore();
            hotel.addRoom(new StandardRoom(roomNumber, price, description, bedType, hasBalcony, floor));
            cout << "Standard Room added! Price: " << price << " RON/night" << endl;
        } else if (type == 2) {
            double price = config.getDouble("deluxe_price", 250.0);
            string bedType, description;
            bool hasBalcony, hasSeaView;
            int floor;
            cout << "Description: ";
            getline(cin, description);
            cout << "Bed type (Single/Double/King): ";
            getline(cin, bedType);
            cout << "Has balcony (1/0): ";
            cin >> hasBalcony;
            cout << "Has sea view (1/0): ";
            cin >> hasSeaView;
            cout << "Floor: ";
            cin >> floor;
            cin.ignore();
            hotel.addRoom(new DeluxeRoom(roomNumber, price, description, bedType, hasBalcony, floor, hasSeaView));
            cout << "Deluxe Room added! Price: " << price << " RON/night" << endl;
        } else if (type == 3) {
            double price = config.getDouble("suite_price", 400.0);
            int suiteType, floor;
            bool hasJacuzzi, hasPrivatePool;
            string description;
            cout << "Description: ";
            getline(cin, description);
            cout << "Suite type (2/3/4 rooms): ";
            cin >> suiteType;
            cout << "Has jacuzzi (1/0): ";
            cin >> hasJacuzzi;
            cout << "Has private pool (1/0): ";
            cin >> hasPrivatePool;
            cout << "Floor: ";
            cin >> floor;
            cin.ignore();
            hotel.addRoom(new Suite(roomNumber, price, description, suiteType, hasJacuzzi, hasPrivatePool, floor));
            cout << "Suite added! Price: " << price << " RON/night" << endl;
        } else {
            cout << "Invalid room type!" << endl;
        }
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Menu::removeRoom() {
    int roomNumber;
    cout << "\n Remove Room" << endl;
    cout << "Room number: ";
    cin >> roomNumber;
    cin.ignore();
    try {
        hotel.removeRoom(roomNumber);
        cout << "Room removed successfully!" << endl;
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Menu::guestManagement() {
    int choice;
    do {
        cout << "\n Guest Management " << endl;
        cout << "1. Add Guest" << endl;
        cout << "2. Display All Guests" << endl;
        cout << "3. Display Guest Bookings" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: addGuest(); break;
            case 2:
                try {
                    hotel.displayAllGuests();
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 3: {
                int guestId;
                cout << "Guest ID: ";
                cin >> guestId;
                cin.ignore();
                try {
                    hotel.displayGuestBookings(guestId);
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 0: break;
            default: cout << "Invalid option!" << endl;
        }
    } while (choice != 0);
}

void Menu::addGuest() {
    int guestId;
    string name, email, phone, nationality;
    cout << "\n=== Add Guest ===" << endl;
    cout << "Guest ID: ";
    cin >> guestId;
    cin.ignore();
    cout << "Name: ";
    getline(cin, name);
    cout << "Email: ";
    cin >> email;
    cout << "Phone: ";
    cin >> phone;
    cin.ignore();
    cout << "Nationality: ";
    getline(cin, nationality);
    try {
        hotel.addGuest(Guest(guestId, name, email, phone, nationality, 0, false));
        cout << "Guest added successfully!" << endl;
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Menu::bookingManagement() {
    int choice;
    do {
        cout << "\n=== Booking Management ===" << endl;
        cout << "1. Make Booking" << endl;
        cout << "2. Confirm Booking" << endl;
        cout << "3. Cancel Booking" << endl;
        cout << "4. Display All Bookings" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: makeBooking(); break;
            case 2: confirmBooking(); break;
            case 3: cancelBooking(); break;
            case 4:
                try {
                    hotel.displayAllBookings();
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 0: break;
            default: cout << "Invalid option!" << endl;
        }
    } while (choice != 0);
}

void Menu::makeBooking() {
    int guestId, roomNumber;
    cout << "\n=== Make Booking ===" << endl;
    cout << "Guest ID: ";
    cin >> guestId;
    cout << "Room number: ";
    cin >> roomNumber;
    cin.ignore();

    cout << "Check-in date:" << endl;
    Date checkIn;
    cin >> checkIn;

    cout << "Check-out date:" << endl;
    Date checkOut;
    cin >> checkOut;

    try {
        Booking* booking = hotel.makeBooking(guestId, roomNumber, checkIn, checkOut);
        cout << "Booking created successfully!" << endl;
        cout << "Booking ID: " << booking->getBookingID() << endl;
        cout << "Total Cost: " << booking->getTotalCost() << " RON" << endl;
        booking->displaySummary();
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Menu::confirmBooking() {
    string bookingID;
    cout << "\n=== Confirm Booking ===" << endl;
    cout << "Booking ID: ";
    getline(cin, bookingID);
    try {
        hotel.confirmBooking(bookingID);
        cout << "Booking confirmed successfully!" << endl;
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Menu::cancelBooking() {
    string bookingID;
    cout << "\n=== Cancel Booking ===" << endl;
    cout << "Booking ID: ";
    getline(cin, bookingID);
    try {
        hotel.cancelBooking(bookingID);
        cout << "Booking cancelled successfully!" << endl;
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void Menu::reports() {
    int choice;
    do {
        cout << "\n=== Reports ===" << endl;
        cout << "1. Occupancy Report" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                try {
                    hotel.displayOccupancyReport();
                } catch (exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 0: break;
            default: cout << "Invalid option!" << endl;
        }
    } while (choice != 0);
}
