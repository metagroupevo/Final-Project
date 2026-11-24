#include "modules.h"
#include "input.h"
#include <iostream>

// mode 1 = ID, 2 = name-equivalent, 3 = status-equivalent
bool beforeRoad(const Road& a, const Road& b, int mode) {
    if (mode == 1)
        return a.id <= b.id;
    if (mode == 2)
        return toLower(a.name) <= toLower(b.name);
    return toLower(a.condition) <= toLower(b.condition);
}
bool beforeFacility(const Facility& a, const Facility& b, int mode) {
    if (mode == 1)
        return a.id <= b.id;
    if (mode == 2)
        return toLower(a.name) <= toLower(b.name);
    return toLower(a.status) <= toLower(b.status);
}
bool beforeEmergency(const Emergency& a, const Emergency& b, int mode) {
    if (mode == 1)
        return a.id <= b.id;
    if (mode == 2)
        return toLower(a.type) <= toLower(b.type);
    return toLower(a.responseStatus) <= toLower(b.responseStatus);
}
bool beforeUtility(const Utility& a, const Utility& b, int mode) {
    if (mode == 1)
        return a.id <= b.id;
    if (mode == 2)
        return toLower(a.type) <= toLower(b.type);
    return toLower(a.status) <= toLower(b.status);
}
bool beforeRequest(const Request& a, const Request& b, int mode) {
    if (mode == 1)
        return a.id <= b.id;
    if (mode == 2)
        return toLower(a.requester) <= toLower(b.requester);
    return toLower(a.status) <= toLower(b.status);
}

void mergeRoad(Road a[], int left, int mid, int right, int mode) {
    int n1 = mid - left + 1, n2 = right - mid;
    Road* L = new Road[n1];
    Road* R = new Road[n2];
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (beforeRoad(L[i], R[j], mode))
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
    delete[] L;
    delete[] R;
    L = nullptr;
    R = nullptr;
}
void mergeSortRoad(Road a[], int left, int right, int mode) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSortRoad(a, left, mid, mode);
    mergeSortRoad(a, mid + 1, right, mode);
    mergeRoad(a, left, mid, right, mode);
}

void mergeFacility(Facility a[], int left, int mid, int right, int mode) {
    int n1 = mid - left + 1, n2 = right - mid;
    Facility* L = new Facility[n1];
    Facility* R = new Facility[n2];
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (beforeFacility(L[i], R[j], mode))
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
    delete[] L;
    delete[] R;
    L = nullptr;
    R = nullptr;
}
void mergeSortFacility(Facility a[], int left, int right, int mode) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSortFacility(a, left, mid, mode);
    mergeSortFacility(a, mid + 1, right, mode);
    mergeFacility(a, left, mid, right, mode);
}

void mergeEmergency(Emergency a[], int left, int mid, int right, int mode) {
    int n1 = mid - left + 1, n2 = right - mid;
    Emergency* L = new Emergency[n1];
    Emergency* R = new Emergency[n2];
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (beforeEmergency(L[i], R[j], mode))
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
    delete[] L;
    delete[] R;
    L = nullptr;
    R = nullptr;
}
void mergeSortEmergency(Emergency a[], int left, int right, int mode) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSortEmergency(a, left, mid, mode);
    mergeSortEmergency(a, mid + 1, right, mode);
    mergeEmergency(a, left, mid, right, mode);
}

void mergeUtility(Utility a[], int left, int mid, int right, int mode) {
    int n1 = mid - left + 1, n2 = right - mid;
    Utility* L = new Utility[n1];
    Utility* R = new Utility[n2];
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (beforeUtility(L[i], R[j], mode))
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
    delete[] L;
    delete[] R;
    L = nullptr;
    R = nullptr;
}
void mergeSortUtility(Utility a[], int left, int right, int mode) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSortUtility(a, left, mid, mode);
    mergeSortUtility(a, mid + 1, right, mode);
    mergeUtility(a, left, mid, right, mode);
}

void mergeRequest(Request a[], int left, int mid, int right, int mode) {
    int n1 = mid - left + 1, n2 = right - mid;
    Request* L = new Request[n1];
    Request* R = new Request[n2];
    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (beforeRequest(L[i], R[j], mode))
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < n1)
        a[k++] = L[i++];
    while (j < n2)
        a[k++] = R[j++];
    delete[] L;
    delete[] R;
    L = nullptr;
    R = nullptr;
}
void mergeSortRequest(Request a[], int left, int right, int mode) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSortRequest(a, left, mid, mode);
    mergeSortRequest(a, mid + 1, right, mode);
    mergeRequest(a, left, mid, right, mode);
}

int countFor(const CityData& c, int module) {
    if (module == 1)
        return c.roadCount;
    if (module == 2)
        return c.facilityCount;
    if (module == 3)
        return c.emergencyCount;
    if (module == 4)
        return c.utilityCount;
    return c.requestCount;
}
void sortModule(CityData& c, int module, int mode) {
    if (module == 1)
        mergeSortRoad(c.roads, 0, c.roadCount - 1, mode);
    else if (module == 2)
        mergeSortFacility(c.facilities, 0, c.facilityCount - 1, mode);
    else if (module == 3)
        mergeSortEmergency(c.emergencies, 0, c.emergencyCount - 1, mode);
    else if (module == 4)
        mergeSortUtility(c.utilities, 0, c.utilityCount - 1, mode);
    else
        mergeSortRequest(c.requests, 0, c.requestCount - 1, mode);
}
int idAt(const CityData& c, int module, int index) {
    if (module == 1)
        return c.roads[index].id;
    if (module == 2)
        return c.facilities[index].id;
    if (module == 3)
        return c.emergencies[index].id;
    if (module == 4)
        return c.utilities[index].id;
    return c.requests[index].id;
}

int linearSearch(const CityData& c, int module, int target) {
    int count = countFor(c, module);
    for (int i = 0; i < count; i++)
        if (idAt(c, module, i) == target)
            return i;
    return -1;
}
int binarySearch(const CityData& c, int module, int target) {
    int low = 0, high = countFor(c, module) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int middleId = idAt(c, module, mid);
        if (middleId == target)
            return mid;
        if (target < middleId)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

void searchSortMenu(CityData& c) {
    while (true) {
        std::cout << "\n=== SEARCH AND SORT CENTER ===\n[1] Linear Search\n[2] Binary Search\n[3] "
                     "Sort by ID\n[4] Sort by Name\n[5] Sort by Status\n[0] Back\n";
        int action = readInt("Choice: ", 0, 5);
        if (action == 0)
            return;
        std::cout << "Modules: [1] Roads [2] Facilities [3] Emergency [4] Utilities [5] Requests "
                     "[0] Cancel\n";
        int module = readInt("Module: ", 0, 5);
        if (module == 0)
            continue;
        int count = countFor(c, module);
        if (count == 0) {
            std::cout << "Selected module is empty.\n";
            continue;
        }
        if (action == 1) {
            int target = readInt("Target ID: ", 1, 999999);
            int result = linearSearch(c, module, target);
            if (result < 0)
                std::cout << "Not found.\n";
            else
                std::cout << "Found at zero-based index " << result << ".\n";
            std::cout << "Sequential Linear Search is O(n).\n";
        } else if (action == 2) {
            sortModule(c, module, 1);
            int target = readInt("Target ID: ", 1, 999999);
            int result = binarySearch(c, module, target);
            if (result < 0)
                std::cout << "Not found.\n";
            else
                std::cout << "Found at zero-based index " << result << ".\n";
            std::cout << "ID Merge Sort preparation is O(n log n); iterative Binary Search itself "
                         "is O(log n).\n";
        } else {
            int mode = action - 2;
            if (mode == 2) {
                if (module == 3)
                    std::cout << "Name-equivalent field: Unit Type.\n";
                else if (module == 4)
                    std::cout << "Name-equivalent field: Utility Type.\n";
                else if (module == 5)
                    std::cout << "Name-equivalent field: Requester Name.\n";
            }
            if (mode == 3) {
                if (module == 1)
                    std::cout << "Status-equivalent field: Road Condition.\n";
                else if (module == 3)
                    std::cout << "Status field: Response Status.\n";
            }
            sortModule(c, module, mode);
            std::cout << "Complete records sorted by Merge Sort in O(n log n) time using O(n) "
                         "temporary auxiliary memory.\n";
        }
    }
}
