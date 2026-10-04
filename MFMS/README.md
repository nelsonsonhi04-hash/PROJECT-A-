# Municipal Financial Management System (MFMS) — Project A

**Course:** PAP521S – Programming in Practice
**Group number:** _[fill in your group number]_
**Group members:**
- _[Name 1 — Student number — Employee Management]_
- _[Name 2 — Student number — Budget Management]_
- _[Name 3 — Student number — Supplier Management]_
- _[Name 4 — Student number — Asset Management]_
- _[Name 5 — Student number — Reports]_
- _[Name 6 — Student number — Functions, integration and validation]_
- _[Name 7 — Student number — Testing, documentation and Git coordination]_

## Project description

A menu-driven foundation system for managing a municipality's employees,
departmental budgets, suppliers and assets, written in ANSI C (C99).
This is Project A — the foundation version — which will be extended in
Project B.

## System features

- **Employee Management** — add, display, search employees; calculate
  gross/net salary with allowances, tax and pension deductions.
- **Budget Management** — enter departmental budgets, record expenditure,
  calculate remaining budget, flag departments that exceed their budget.
- **Supplier Management** — add, display, search/compare suppliers
  (ID, name, email, phone, town) with email and phone validation.
- **Asset Management** — register municipal assets (vehicles, computers,
  buildings, equipment, furniture) with purchase value, department and
  condition; search and display the asset register.
- **Reports** — employee report (total/average/highest/lowest salary),
  budget report (totals and over-budget departments), supplier report,
  asset report.
- Input validation throughout (no negative salaries/budgets, no empty
  names, invalid menu choices are rejected and re-prompted).

## Program design

Each module has its own `.c`/`.h` pair with its own struct, a fixed-size
array + count for storage, and `add` / `display` / `search` functions.
`utils.c/.h` holds shared input-validation helpers (`readInt`,
`readDouble`, `readNonEmpty`, `containsIgnoreCase`, `isValidEmail`,
`isValidPhone`) used by every module. `main.c` only shows the top menu
and calls each module's own menu function — there is no single large
`main()`.

## Compilation instructions

With `make` (Linux/macOS/WSL/MinGW with make installed):
```
make
```

Without `make` (plain gcc):
```
gcc -std=c99 -Wall -Wextra -pedantic -o mfms main.c utils.c employees.c budget.c suppliers.c assets.c reports.c
```

## How to run

```
./mfms        # Linux/macOS
mfms.exe      # Windows
```

Follow the on-screen menu (1–6) to navigate between modules.

## Individual responsibilities

| Member | Responsibility |
|---|---|
| Student 1 | Employee Management (`employees.c/.h`) |
| Student 2 | Budget Management (`budget.c/.h`) |
| Student 3 | Supplier Management (`suppliers.c/.h`) |
| Student 4 | Asset Management (`assets.c/.h`) |
| Student 5 | Reports (`reports.c/.h`) |
| Student 6 | Shared utilities, `main.c`, integration, validation |
| Student 7 | Testing, documentation, GitHub coordination |
