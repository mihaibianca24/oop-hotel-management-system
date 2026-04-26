//
// Created by Bianca Mihai on 26.04.2026.
//

#include "ConfigLoader.h"
#include <iostream>
using namespace std;
void ConfigLoader::loadFromFile(const std::string &filename) {
    ifstream file(filename);
    if (!file.is_open())
        throw runtime_error("Cannot open config file: " + filename);

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        int pos = line.find('=');
        if (pos == string::npos) continue;

        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);
        config[key] = value;
    }
    file.close();
}
ConfigLoader::ConfigLoader(const string& filename) {
    loadFromFile(filename);
}
ConfigLoader::ConfigLoader(const ConfigLoader& obj) {
    this->config = obj.config;
}
ConfigLoader& ConfigLoader::operator=(const ConfigLoader& obj) {
    if (this == &obj) return *this;
    this->config = obj.config;
    return *this;
}

ConfigLoader::~ConfigLoader() {}

double ConfigLoader::getDouble(const string& key, double defaultValue) const {
    auto it = config.find(key);
    if (it == config.end())
        return defaultValue;
    return stod(it->second);
}

string ConfigLoader::getString(const string& key, const string& defaultValue) const {
    auto it = config.find(key);
    if (it == config.end())
        return defaultValue;
    return it->second;
}

int ConfigLoader::getInt(const string& key, int defaultValue) const {
    auto it = config.find(key);
    if (it == config.end())
        return defaultValue;
    return stoi(it->second);
}

ostream& operator<<(ostream& out, const ConfigLoader& obj) {
    for (auto& pair : obj.config)
        out << pair.first << "=" << pair.second << endl;
    return out;
}
istream& operator>>(istream& in, ConfigLoader& obj) {
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        int pos = line.find('=');
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);
        obj.config[key] = value;
    }
    return in;
}
