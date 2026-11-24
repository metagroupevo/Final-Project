#ifndef MODELS_H
#define MODELS_H
#include <string>

const int MAX_RECORDS = 100;
const int DISTRICT_COUNT = 5;

struct Road {
    int id;
    std::string name, location, traffic, condition;
};
struct Facility {
    int id;
    std::string name, type, location;
    int capacity;
    std::string status;
};
struct Emergency {
    int id;
    std::string type, location, availability, responseStatus;
};
struct Utility {
    int id;
    std::string type, area, status;
    double usage;
};
struct Request {
    int id;
    std::string requester, category, location, priority, status;
};

struct CityData {
    Road roads[MAX_RECORDS];
    int roadCount;
    Facility facilities[MAX_RECORDS];
    int facilityCount;
    Emergency emergencies[MAX_RECORDS];
    int emergencyCount;
    Utility* utilities;
    int utilityCount;
    int utilityCapacity;
    Request requests[MAX_RECORDS];
    int requestCount;
    int matrix[DISTRICT_COUNT][DISTRICT_COUNT];
    std::string districts[DISTRICT_COUNT];
};
#endif
