#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_SUITE_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_SUITE_H
#include "Accommodation.h"

class Suite : public Accommodation{
    int suiteType;
    bool hasJacuzzi;
    bool hasPrivatePool;
    int floor;
    public:
    Suite();
    Suite(int roomNumber, double pricePerNight,const std::string &description,
        int suiteType, bool hasJacuzzi, bool hasPrivatePool, int floor);
    Suite(const Suite &obj);
    Suite &operator=(const Suite &obj);
    ~Suite();

    int getSuiteType() const;
    bool getHasJacuzzi() const;
    bool getHasPrivatePool() const;
    int getFloor() const;

    void setSuiteType(int suiteType);
    void setHasJacuzzi(bool hasJacuzzi);
    void setHasPrivatePool(bool hasPrivatePool);
    void setFloor(int floor);

    std::string getRoomType() override;
    double calculatePrice(int nights) override;
    void displayInfo() override;
    Suite* clone() const override;

};
#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_SUITE_H