#include "modules.h"
#include "input.h"
#include <iostream>

int main() {
    std::cout << "Smart City Infrastructure System\n";
    int capacity = readInt("Enter Utility Monitoring capacity (1-100): ", 1, MAX_RECORDS);
    CityData city;
    initializeCity(city, capacity);

    while (true) {
        std::cout << "\n=== MAIN DASHBOARD ===\n"
                  << "[1] Road & Transportation Management\n"
                  << "[2] Public Facility Management\n"
                  << "[3] Emergency Service Management\n"
                  << "[4] Utility Monitoring\n"
                  << "[5] Citizen Service Requests\n"
                  << "[6] City Statistics\n"
                  << "[7] Search and Sort Records\n"
                  << "[8] System Information\n"
                  << "[0] Exit\n";
        int choice = readInt("Choice: ", 0, 8);
        if (choice == 1)
            roadMenu(city);
        else if (choice == 2)
            facilityMenu(city);
        else if (choice == 3)
            emergencyMenu(city);
        else if (choice == 4)
            utilityMenu(city);
        else if (choice == 5)
            requestMenu(city);
        else if (choice == 6)
            showStatistics(city);
        else if (choice == 7)
            searchSortMenu(city);
        else if (choice == 8)
            showSystemInformation(city);
        else {
            releaseCity(city);
            std::cout
                << "Utility array released with delete[] and pointer set to nullptr. Goodbye!\n";
            break;
        }
    }
    return 0;
}
