#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_ACCOMMODATION_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_ACCOMMODATION_H

#include<iostream>
#include<string>
class Accommodation {
private:
    int roomNumber;
    double pricePerNight;
    bool isAvailable;
    std::string description;
public:
    Accommodation();
    Accommodation(int roomNumber, double pricePerNight, std::string description);
    Accommodation(const Accommodation &obj);
    Accommodation &operator=(const Accommodation &obj);
    virtual ~Accommodation();

    int getRoomNumber() const;
    double getPricePerNight() const;
    std::string getDescription() const;
    bool getIsAvailable() const;

    void setRoomNumber(int roomNumber);
    void setPricePerNight(double pricePerNight);
    void setDescription(const std::string &description);
    void setIsAvailable(bool available);

    virtual std::string getRoomType() = 0;
    virtual double calculatePrice(int nights) = 0;
    virtual void displayInfo() = 0;

    friend std::ostream &operator<<(std::ostream &os, const Accommodation &obj);
    friend std::istream &operator>>(std::istream &is, Accommodation &obj);
};


#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_ACCOMMODATION_H