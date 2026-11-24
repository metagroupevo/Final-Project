#include "modules.h"
#include "input.h"
#include <iostream>
#include <iomanip>

const std::string TRAFFIC[] = {"Low", "Medium", "High"};
const std::string ROAD_CONDITION[] = {"Good", "Fair", "Poor", "Closed"};
const std::string FACILITY_STATUS[] = {"Operational", "Maintenance", "Closed"};
const std::string AVAILABILITY[] = {"Available", "Unavailable"};
const std::string RESPONSE_STATUS[] = {"Ready", "Responding", "Returning"};
const std::string UTILITY_STATUS[] = {"Normal", "Warning", "Outage"};
const std::string PRIORITY[] = {"Low", "Medium", "High", "Critical"};
const std::string REQUEST_STATUS[] = {"Pending", "In Progress", "Resolved"};

void initializeCity(CityData& c, int capacity) {
    c.roadCount = c.facilityCount = c.emergencyCount = c.utilityCount = c.requestCount = 0;
    c.utilityCapacity = capacity;
    c.utilities = new Utility[capacity];
    c.districts[0] = "D1-Central";
    c.districts[1] = "D2-North";
    c.districts[2] = "D3-South";
    c.districts[3] = "D4-East";
    c.districts[4] = "D5-West";
    for (int row = 0; row < DISTRICT_COUNT; row++)
        for (int column = 0; column < DISTRICT_COUNT; column++)
            c.matrix[row][column] = 0;
}

int findRoad(const CityData& c, int id) {
    for (int i = 0; i < c.roadCount; i++)
        if (c.roads[i].id == id)
            return i;
    return -1;
}
int findFacility(const CityData& c, int id) {
    for (int i = 0; i < c.facilityCount; i++)
        if (c.facilities[i].id == id)
            return i;
    return -1;
}
int findEmergency(const CityData& c, int id) {
    for (int i = 0; i < c.emergencyCount; i++)
        if (c.emergencies[i].id == id)
            return i;
    return -1;
}
int findUtility(const CityData& c, int id) {
    for (int i = 0; i < c.utilityCount; i++)
        if (c.utilities[i].id == id)
            return i;
    return -1;
}
int findRequest(const CityData& c, int id) {
    for (int i = 0; i < c.requestCount; i++)
        if (c.requests[i].id == id)
            return i;
    return -1;
}

int menu(const std::string& title, bool matrix) {
    std::cout << "\n=== " << title
              << " ===\n[1] Add\n[2] Display All\n[3] Update\n[4] Delete\n[5] Search by ID\n";
    if (matrix)
        std::cout << "[6] District Connectivity Matrix\n";
    std::cout << "[0] Back\n";
    return readInt("Choice: ", 0, matrix ? 6 : 5);
}

void printRoad(const Road& r) {
    std::cout << r.id << " | " << r.name << " | " << r.location << " | " << r.traffic << " | "
              << r.condition << '\n';
}
void printFacility(const Facility& r) {
    std::cout << r.id << " | " << r.name << " | " << r.type << " | " << r.location << " | "
              << r.capacity << " | " << r.status << '\n';
}
void printEmergency(const Emergency& r) {
    std::cout << r.id << " | " << r.type << " | " << r.location << " | " << r.availability << " | "
              << r.responseStatus << '\n';
}
void printUtility(const Utility& r) {
    std::cout << r.id << " | " << r.type << " | " << r.area << " | " << r.status << " | " << r.usage
              << "%\n";
}
void printRequest(const Request& r) {
    std::cout << r.id << " | " << r.requester << " | " << r.category << " | " << r.location << " | "
              << r.priority << " | " << r.status << '\n';
}

void matrixMenu(CityData& c) {
    while (true) {
        std::cout << "\nRows and columns are fixed district identifiers. 0=no direct connection; "
                     "1=direct connection.\n"
                  << "[1] Display Matrix\n[2] Update Connection\n[3] Count Each Row's "
                     "Connections\n[0] Back\n";
        int choice = readInt("Choice: ", 0, 3);
        if (choice == 0)
            return;
        if (choice == 1) {
            std::cout << std::setw(14) << "";
            for (int col = 0; col < DISTRICT_COUNT; col++)
                std::cout << std::setw(4) << col;
            std::cout << '\n';
            for (int row = 0; row < DISTRICT_COUNT; row++) {
                std::cout << std::setw(14) << c.districts[row];
                for (int col = 0; col < DISTRICT_COUNT; col++)
                    std::cout << std::setw(4) << c.matrix[row][col];
                std::cout << '\n';
            }
            std::cout << "Nested loops visit rows then columns, matching C++ row-major storage.\n";
        } else if (choice == 2) {
            for (int i = 0; i < DISTRICT_COUNT; i++)
                std::cout << i << " = " << c.districts[i] << '\n';
            int a = readInt("First district index: ", 0, DISTRICT_COUNT - 1),
                b = readInt("Second district index: ", 0, DISTRICT_COUNT - 1);
            if (a == b) {
                std::cout << "A district cannot connect to itself.\n";
                continue;
            }
            int value = readInt("Connection (0 or 1): ", 0, 1);
            c.matrix[a][b] = value;
            c.matrix[b][a] = value;
            std::cout << "Both symmetric cells were updated.\n";
        } else {
            for (int row = 0; row < DISTRICT_COUNT; row++) {
                int total = 0;
                for (int col = 0; col < DISTRICT_COUNT; col++)
                    total += c.matrix[row][col];
                std::cout << c.districts[row] << ": " << total << " direct connection(s)\n";
            }
            std::cout << "One row costs O(D); processing all rows costs O(D^2).\n";
        }
    }
}

void roadMenu(CityData& c) {
    while (true) {
        int choice = menu("ROAD & TRANSPORTATION", true);
        if (choice == 0)
            return;
        if (choice == 1) {
            if (c.roadCount == MAX_RECORDS) {
                std::cout << "Road array is full.\n";
                continue;
            }
            Road r;
            r.id = readInt("Road ID: ", 1, 999999);
            if (findRoad(c, r.id) >= 0) {
                std::cout << "Duplicate ID rejected.\n";
                continue;
            }
            r.name = readRequired("Road name: ");
            r.location = readRequired("Location: ");
            r.traffic = readChoice("Traffic (Low/Medium/High): ", TRAFFIC, 3);
            r.condition = readChoice("Condition (Good/Fair/Poor/Closed): ", ROAD_CONDITION, 4);
            int position = readInt("Insertion position (1 to count+1): ", 1, c.roadCount + 1) - 1;
            for (int i = c.roadCount; i > position; i--)
                c.roads[i] = c.roads[i - 1];
            c.roads[position] = r;
            c.roadCount++;
            std::cout << "Road inserted; later records shifted right.\n";
        } else if (choice == 2) {
            if (c.roadCount == 0)
                std::cout << "No roads.\n";
            else
                for (int i = 0; i < c.roadCount; i++)
                    printRoad(c.roads[i]);
        } else if (choice == 3) {
            int id = readInt("ID to update: ", 1, 999999), i = findRoad(c, id);
            if (i < 0) {
                std::cout << "Road not found.\n";
                continue;
            }
            Road* pointer = &c.roads[i];
            std::cout << "Address (&record): " << pointer
                      << "; dereferenced ID ((*pointer).id): " << (*pointer).id << '\n';
            pointer->name = readRequired("New name: ");
            pointer->location = readRequired("New location: ");
            pointer->traffic = readChoice("Traffic: ", TRAFFIC, 3);
            pointer->condition = readChoice("Condition: ", ROAD_CONDITION, 4);
            std::cout << "Road updated.\n";
        } else if (choice == 4) {
            int id = readInt("ID to delete: ", 1, 999999), index = findRoad(c, id);
            if (index < 0) {
                std::cout << "Road not found.\n";
                continue;
            }
            for (int i = index; i < c.roadCount - 1; i++)
                c.roads[i] = c.roads[i + 1];
            c.roadCount--;
            std::cout << "Road deleted; later records shifted left.\n";
        } else if (choice == 5) {
            int i = findRoad(c, readInt("ID to search: ", 1, 999999));
            if (i < 0)
                std::cout << "Road not found.\n";
            else
                printRoad(c.roads[i]);
        } else
            matrixMenu(c);
    }
}

void facilityMenu(CityData& c) {
    while (true) {
        int choice = menu("PUBLIC FACILITIES", false);
        if (!choice)
            return;
        if (choice == 1) {
            if (c.facilityCount == MAX_RECORDS) {
                std::cout << "Facility array is full.\n";
                continue;
            }
            Facility r;
            r.id = readInt("Facility ID: ", 1, 999999);
            if (findFacility(c, r.id) >= 0) {
                std::cout << "Duplicate ID rejected.\n";
                continue;
            }
            r.name = readRequired("Facility name: ");
            r.type = readRequired("Type: ");
            r.location = readRequired("Location: ");
            r.capacity = readInt("Capacity: ", 0, 1000000);
            r.status = readChoice("Status (Operational/Maintenance/Closed): ", FACILITY_STATUS, 3);
            c.facilities[c.facilityCount++] = r;
            std::cout << "Facility added.\n";
        } else if (choice == 2) {
            if (!c.facilityCount)
                std::cout << "No facilities.\n";
            else
                for (int i = 0; i < c.facilityCount; i++)
                    printFacility(c.facilities[i]);
        } else {
            int id = readInt(choice == 3   ? "ID to update: "
                             : choice == 4 ? "ID to delete: "
                                           : "ID to search: ",
                             1, 999999),
                i = findFacility(c, id);
            if (i < 0) {
                std::cout << "Facility not found.\n";
                continue;
            }
            if (choice == 3) {
                Facility& r = c.facilities[i];
                r.name = readRequired("New name: ");
                r.type = readRequired("New type: ");
                r.location = readRequired("New location: ");
                r.capacity = readInt("New capacity: ", 0, 1000000);
                r.status = readChoice("New status: ", FACILITY_STATUS, 3);
                std::cout << "Facility updated.\n";
            } else if (choice == 4) {
                for (int j = i; j < c.facilityCount - 1; j++)
                    c.facilities[j] = c.facilities[j + 1];
                c.facilityCount--;
                std::cout << "Facility deleted.\n";
            } else
                printFacility(c.facilities[i]);
        }
    }
}

void emergencyMenu(CityData& c) {
    while (true) {
        int choice = menu("EMERGENCY SERVICES", false);
        if (!choice)
            return;
        if (choice == 1) {
            if (c.emergencyCount == MAX_RECORDS) {
                std::cout << "Emergency array is full.\n";
                continue;
            }
            Emergency r;
            r.id = readInt("Unit ID: ", 1, 999999);
            if (findEmergency(c, r.id) >= 0) {
                std::cout << "Duplicate ID rejected.\n";
                continue;
            }
            r.type = readRequired("Unit type: ");
            r.location = readRequired("Location: ");
            r.availability = readChoice("Availability (Available/Unavailable): ", AVAILABILITY, 2);
            r.responseStatus =
                readChoice("Response (Ready/Responding/Returning): ", RESPONSE_STATUS, 3);
            c.emergencies[c.emergencyCount++] = r;
            std::cout << "Unit added.\n";
        } else if (choice == 2) {
            if (!c.emergencyCount)
                std::cout << "No emergency units.\n";
            else
                for (int i = 0; i < c.emergencyCount; i++)
                    printEmergency(c.emergencies[i]);
        } else {
            int id = readInt(choice == 3   ? "ID to update: "
                             : choice == 4 ? "ID to delete: "
                                           : "ID to search: ",
                             1, 999999),
                i = findEmergency(c, id);
            if (i < 0) {
                std::cout << "Unit not found.\n";
                continue;
            }
            if (choice == 3) {
                Emergency& r = c.emergencies[i];
                r.type = readRequired("New type: ");
                r.location = readRequired("New location: ");
                r.availability = readChoice("Availability: ", AVAILABILITY, 2);
                r.responseStatus = readChoice("Response: ", RESPONSE_STATUS, 3);
                std::cout << "Unit updated.\n";
            } else if (choice == 4) {
                for (int j = i; j < c.emergencyCount - 1; j++)
                    c.emergencies[j] = c.emergencies[j + 1];
                c.emergencyCount--;
                std::cout << "Unit deleted.\n";
            } else
                printEmergency(c.emergencies[i]);
        }
    }
}

void utilityMenu(CityData& c) {
    while (true) {
        int choice = menu("UTILITY MONITORING (DYNAMIC ARRAY)", false);
        if (!choice)
            return;
        if (choice == 1) {
            if (c.utilityCount == c.utilityCapacity) {
                std::cout << "Dynamic array is full. Its allocated capacity remains fixed until "
                             "explicitly reallocated.\n";
                continue;
            }
            Utility r;
            r.id = readInt("Utility ID: ", 1, 999999);
            if (findUtility(c, r.id) >= 0) {
                std::cout << "Duplicate ID rejected.\n";
                continue;
            }
            r.type = readRequired("Utility type: ");
            r.area = readRequired("Area: ");
            r.status = readChoice("Status (Normal/Warning/Outage): ", UTILITY_STATUS, 3);
            r.usage = readDouble("Usage (0-100): ", 0, 100);
            *(c.utilities + c.utilityCount) = r;
            c.utilityCount++;
            std::cout << "Added using pointer arithmetic: *(utilities + index).\n";
        } else if (choice == 2) {
            if (!c.utilityCount)
                std::cout << "No utility records.\n";
            else
                for (int i = 0; i < c.utilityCount; i++) {
                    Utility* p = c.utilities + i;
                    std::cout << "Address " << p << " -> ";
                    printUtility(*p);
                }
        } else {
            int id = readInt(choice == 3   ? "ID to update: "
                             : choice == 4 ? "ID to delete: "
                                           : "ID to search: ",
                             1, 999999),
                i = findUtility(c, id);
            if (i < 0) {
                std::cout << "Utility not found.\n";
                continue;
            }
            if (choice == 3) {
                Utility* r = c.utilities + i;
                r->type = readRequired("New type: ");
                r->area = readRequired("New area: ");
                r->status = readChoice("New status: ", UTILITY_STATUS, 3);
                r->usage = readDouble("New usage: ", 0, 100);
                std::cout << "Utility updated through pointer access.\n";
            } else if (choice == 4) {
                for (int j = i; j < c.utilityCount - 1; j++)
                    *(c.utilities + j) = *(c.utilities + j + 1);
                c.utilityCount--;
                std::cout << "Utility deleted.\n";
            } else
                printUtility(*(c.utilities + i));
        }
    }
}

void requestMenu(CityData& c) {
    while (true) {
        int choice = menu("CITIZEN SERVICE REQUESTS", false);
        if (!choice)
            return;
        if (choice == 1) {
            if (c.requestCount == MAX_RECORDS) {
                std::cout << "Request array is full.\n";
                continue;
            }
            Request r;
            r.id = readInt("Request ID: ", 1, 999999);
            if (findRequest(c, r.id) >= 0) {
                std::cout << "Duplicate ID rejected.\n";
                continue;
            }
            r.requester = readRequired("Requester name: ");
            r.category = readRequired("Category: ");
            r.location = readRequired("Location: ");
            r.priority = readChoice("Priority (Low/Medium/High/Critical): ", PRIORITY, 4);
            r.status = readChoice("Status (Pending/In Progress/Resolved): ", REQUEST_STATUS, 3);
            c.requests[c.requestCount++] = r;
            std::cout << "Request added.\n";
        } else if (choice == 2) {
            if (!c.requestCount)
                std::cout << "No requests.\n";
            else
                for (int i = 0; i < c.requestCount; i++)
                    printRequest(c.requests[i]);
        } else {
            int id = readInt(choice == 3   ? "ID to update: "
                             : choice == 4 ? "ID to delete: "
                                           : "ID to search: ",
                             1, 999999),
                i = findRequest(c, id);
            if (i < 0) {
                std::cout << "Request not found.\n";
                continue;
            }
            if (choice == 3) {
                Request& r = c.requests[i];
                r.requester = readRequired("New requester: ");
                r.category = readRequired("New category: ");
                r.location = readRequired("New location: ");
                r.priority = readChoice("New priority: ", PRIORITY, 4);
                r.status = readChoice("New status: ", REQUEST_STATUS, 3);
                std::cout << "Request updated.\n";
            } else if (choice == 4) {
                for (int j = i; j < c.requestCount - 1; j++)
                    c.requests[j] = c.requests[j + 1];
                c.requestCount--;
                std::cout << "Request deleted.\n";
            } else
                printRequest(c.requests[i]);
        }
    }
}

void showStatistics(const CityData& c) {
    int high = 0, available = 0, pending = 0, progress = 0, resolved = 0;
    for (int i = 0; i < c.roadCount; i++)
        if (c.roads[i].traffic == "High")
            high++;
    for (int i = 0; i < c.emergencyCount; i++)
        if (c.emergencies[i].availability == "Available")
            available++;
    for (int i = 0; i < c.requestCount; i++) {
        if (c.requests[i].status == "Pending")
            pending++;
        else if (c.requests[i].status == "In Progress")
            progress++;
        else if (c.requests[i].status == "Resolved")
            resolved++;
    }
    std::cout << "\nTotal roads: " << c.roadCount << "\nHigh-traffic roads: " << high
              << "\nTotal public facilities: " << c.facilityCount
              << "\nTotal emergency units: " << c.emergencyCount
              << "\nAvailable units: " << available << "\nTotal utility records: " << c.utilityCount
              << "\nPending requests: " << pending << "\nIn Progress requests: " << progress
              << "\nResolved requests: " << resolved << '\n';
}

void showSystemInformation(const CityData& c) {
    std::cout
        << "\nStructures store complete city records. Fixed arrays have capacity 100.\n"
        << "Utility Monitoring uses new[] with count/capacity " << c.utilityCount << '/'
        << c.utilityCapacity << ".\n"
        << "Utility base address: " << static_cast<const void*>(c.utilities) << "\n"
        << "array[i] and *(array+i) access the same element. Pointer arithmetic advances by one "
           "complete Utility object.\n"
        << "new creates one object and uses delete; new[] creates an array and must use delete[].\n"
        << "Using memory after delete[] is invalid. Forgetting delete[] causes a memory leak.\n"
        << "Traffic: Low/Medium/High. Request status: Pending/In Progress/Resolved.\n";
}

void releaseCity(CityData& c) {
    delete[] c.utilities;
    c.utilities = nullptr;
    c.utilityCount = 0;
    c.utilityCapacity = 0;
}
