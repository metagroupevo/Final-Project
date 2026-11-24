# System Architecture

`main.cpp` owns the `CityData` lifetime, obtains the dynamic utility capacity, allocates through `initializeCity`, routes dashboard actions, and releases memory on normal exit. `input.cpp` provides line-based validation. `modules.cpp` provides all CRUD menus, matrix operations, statistics, pointer demonstrations, and cleanup. `search.cpp` contains manual Merge Sort, Linear Search, and iterative Binary Search.

```text
main dashboard
  +-- five CRUD menus
  |     +-- fixed arrays: roads, facilities, emergency units, requests
  |     `-- dynamic array: utilities
  +-- road district matrix
  +-- statistics
  +-- search/sort center
  `-- system information
```

## Search/sort fields

| Module | ID | Name option | Status option |
|---|---|---|---|
| Roads | Road ID | Road Name | Road Condition |
| Facilities | Facility ID | Facility Name | Status |
| Emergency | Unit ID | Unit Type | Response Status |
| Utilities | Utility ID | Utility Type | Status |
| Requests | Request ID | Requester Name | Status |

Every selected module has a meaningful equivalent, so no option needs disabling. The menu explicitly announces nonliteral mappings.

District labels are fixed independently of road array indices. Therefore, sorting/deleting roads cannot change matrix meaning. Connection updates write `[a][b]` and `[b][a]` to preserve two-way symmetry.
