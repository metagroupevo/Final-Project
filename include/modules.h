#ifndef MODULES_H
#define MODULES_H
#include "models.h"
void initializeCity(CityData& city, int utilityCapacity);
void roadMenu(CityData& city);
void facilityMenu(CityData& city);
void emergencyMenu(CityData& city);
void utilityMenu(CityData& city);
void requestMenu(CityData& city);
void showStatistics(const CityData& city);
void searchSortMenu(CityData& city);
void showSystemInformation(const CityData& city);
void releaseCity(CityData& city);
#endif
