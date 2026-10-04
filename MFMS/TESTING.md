# MFMS — Project A: Test Plan and Results

All tests below were run against the compiled `mfms` executable
(`gcc -std=c99 -Wall -Wextra -pedantic`, zero warnings).

| # | Test case | Input | Expected result | Actual result | Pass/Fail |
|---|---|---|---|---|---|
| 1 | Invalid main menu choice | `9` at main menu | Rejected, re-prompted, valid range 1–6 shown | `Error: value must be between 1 and 6.` then re-prompted | Pass |
| 2 | Empty name rejected | Blank line for employee name | Rejected, re-prompted | `Error: this field cannot be empty.` then re-prompted | Pass |
| 3 | Negative salary rejected | `-500` for basic salary | Rejected, re-prompted | `Error: value cannot be less than 0.01.` then re-prompted | Pass |
| 4 | Duplicate employee ID rejected | Add `E001` twice in one session | Second attempt rejected, same ID can't be reused | `Error: an employee with ID 'E001' already exists.` | Pass |
| 5 | Negative budget rejected | `-1000` for allocated budget | Rejected, re-prompted | `Error: value cannot be less than 0.01.` then re-prompted | Pass |
| 6 | Budget exceeded detection | Allocate N$500000, spend N$620000 | Status shows EXCEEDED BUDGET, warning printed | `Remaining Budget: N$-120000.00` / `Status: EXCEEDED BUDGET` | Pass |
| 7 | Search with no matches | Search employees by name "ZZZ" | "No matching employee found." printed, no crash | `No matching employee found.` | Pass |
| 8 | Invalid supplier email rejected | `notanemail` | Rejected, re-prompted with example | `Error: invalid email (example: name@company.com).` | Pass |
| 9 | Invalid supplier phone rejected | `123` (too short) | Rejected, re-prompted | `Error: phone must be 7-15 digits (optional leading +).` | Pass |
| 10 | Empty employee/supplier/asset list display | Choose "Display" before adding any records | "No ... registered yet." message, no crash | Confirmed in employees, budgets, suppliers, assets modules | Pass |

## Notes for the report

- Validation is handled centrally in `utils.c` (`readInt`, `readDouble`,
  `readNonEmpty`) so every module rejects bad input the same way instead
  of each module reimplementing its own checks.
- Duplicate-ID checks use `strcmp()` against the existing array before a
  new record is accepted (see `findEmployeeById`, `findSupplierById`,
  `findAssetById`, `findBudgetByDepartment`).
- No test produced a crash or undefined behaviour; compiling with
  `-Wall -Wextra -pedantic` produced zero warnings.

## How to re-run these tests yourself

From the `MFMS` folder:
```
make
./mfms
```
Then manually repeat the inputs in the table above, or pipe them in
non-interactively, e.g.:
```
printf '1\n1\nE001\n\nJohn Doe\nFinance\nClerk\n-500\n15000\n3000\n1000\n5\n6\n6\n' | ./mfms
```
