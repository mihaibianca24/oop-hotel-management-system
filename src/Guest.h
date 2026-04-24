#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_GUEST_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_GUEST_H

#include <iostream>
#include <string>
#include <vector>
class Guest {
private:
    int guestId;
    std::string name;
    std::string email;
    std::string phone;
    std::string nationality;
    int totalBookings;
    bool isVip;
public:
    Guest();
    Guest(int guestId,const std::string &name,const std::string &email,const std::string &phone,
        const std::string &nationality,int totalBookings,bool isVip);
    Guest(const Guest &obj);
    Guest &operator=(const Guest &obj);
    ~Guest();

    int getGuestId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getNationality() const;
    int getTotalBookings() const;
    bool getIsVip() const;

    void setGuestId(int guestId);
    void setName(const std::string &name);
    void setEmail(const std::string &email);
    void setPhone(const std::string &phone);
    void setNationality(const std::string &nationality);
    void setTotalBookings(int totalBookings);
    void setIsVip(bool isVip);

    void incrementBookings();

    friend std::ostream &operator<<(std::ostream &out, const Guest &obj);
    friend std::istream &operator>>(std::istream &in, Guest &obj);
};


#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_GUEST_H