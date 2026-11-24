# Testing and Peer Code Audit Report

## Execution status

On November 24, 2026, the project was compiled using MSYS2 g++ 16.2.0 with `-std=c++17 -Wall -Wextra -pedantic`. The compiler initially failed because `C:\msys64\ucrt64\bin` was absent from PATH, causing its backend to exit with Windows error `0xC0000135` (missing DLL). Adding that directory to PATH corrected the toolchain environment. The complete build then succeeded with no compiler diagnostics.

| Test case | Input or steps | Expected output | Actual output | Result |
|---|---|---|---|---|
| Empty collection | Road > Display | `No roads.`; menu continues | — | NOT RUN |
| One record | Add one road at position 1; display/search | Record appears at index 0 and is found | Record ID 30 added and displayed | PASS |
| Right-shift insertion | Add ID 30, then insert ID 10 at position 1 | Display order 10, 30 | Display order was 10, 30 | PASS |
| Left-shift deletion | Delete ID 20 from above | 30 shifts left; count becomes 2 | — | NOT RUN |
| Duplicate ID | Add an existing module ID | Rejected; count unchanged | — | NOT RUN |
| Missing ID | Update/delete/search ID 999 | Not-found message; data unchanged | — | NOT RUN |
| Invalid numeric input | Enter letters, negative/out-of-range, then valid | Invalid entries rejected; no infinite loop | — | NOT RUN |
| Empty required text | Enter blank then valid spaced text | Blank rejected; full text retained | — | NOT RUN |
| Utility capacity lower bound | Startup capacity 1; add 2 utilities | First accepted, second reports full | — | NOT RUN |
| Utility pointer display | Add utility, display | Address plus correct dereferenced record | — | NOT RUN |
| Fixed array full | Populate 100 roads; attempt another | Full message, no out-of-bounds write | — | NOT RUN |
| Linear Search | Add unsorted IDs; search present/absent IDs | Correct index/not-found; original order remains | — | NOT RUN |
| Binary Search | Add reverse IDs 30, 10; search for 30 | ID sort occurs; result correct | Found at zero-based index 1 after Merge Sort | PASS |
| Already sorted Merge Sort | Sort ascending records by ID | Order remains correct | — | NOT RUN |
| Reverse Merge Sort | Sort descending IDs | Ascending complete records | — | NOT RUN |
| Name sort | Sort requests by Requester Name | Alphabetical requester order | — | NOT RUN |
| Status sort then binary | Status sort; then search by ID | Automatic ID re-sort; correct result | — | NOT RUN |
| Matrix symmetry | Set Central–East to 1; display | Both mirrored cells equal 1 | — | NOT RUN |
| Matrix diagonal | Try Central–Central | Rejected; diagonal remains 0 | — | NOT RUN |
| Matrix row count | Add two Central connections | Central count is 2 | — | NOT RUN |
| Statistics | Add 2 roads (1 High) and 1 utility | Totals exactly match live records | Roads 2, High 1, Utilities 1 | PASS |
| Normal cleanup | Add utility, perform Merge Sort, exit | Main and temporary arrays released | Normal exit message printed; process exit code 0 | PASS |

## Peer audit checklist

- Compilation: PASS with MSYS2 g++ 16.2.0 and strict warning flags.
- No STL containers/search/sort, templates, lambdas, inheritance, or external libraries: static source check completed.
- Focused input-process-output functions and meaningful record names: source check completed.
- Loop termination and bounds: loops use counts/capacities; menu readers repeat only until valid.
- Memory ownership: utility array released on normal exit; every merge temporary released.
- Readability: module headers, separate files, consistent menu/value messages, and explanatory comments included.

For memory verification on a compiler-equipped machine:

```bash
g++ -std=c++17 -g -fsanitize=address,undefined src/*.cpp -Iinclude -o smart_city_test
./smart_city_test
```
