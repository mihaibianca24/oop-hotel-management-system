//
// Created by Bianca Mihai on 26.04.2026.
//

#ifndef OOP_HOTEL_MANAGEMENT_SYSTEM_CONFIGLOADER_H
#define OOP_HOTEL_MANAGEMENT_SYSTEM_CONFIGLOADER_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>

class ConfigLoader {
private:
    std::map<std::string , std::string>config;
    void loadFromFile(const std::string &filename);
public:
    ConfigLoader(const std::string &filename);
    ConfigLoader(const ConfigLoader &obj);
    ConfigLoader &operator=(const ConfigLoader &obj);
    ~ConfigLoader();

    double getDouble(const std::string& key, double defaultValue) const;
    std::string getString(const std::string& key, const std::string& defaultValue) const;
    int getInt(const std::string& key, int defaultValue) const;

    friend std::ostream& operator<<(std::ostream &out ,const ConfigLoader &obj);
    friend std::istream& operator>>(std::istream &in, ConfigLoader &obj);
};


#endif //OOP_HOTEL_MANAGEMENT_SYSTEM_CONGIFLOADER_H