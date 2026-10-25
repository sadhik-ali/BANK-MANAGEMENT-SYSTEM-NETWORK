<div align="center">

# 🏦 Network Static Toolkit

[![License: CC BY 4.0](https://img.shields.io/badge/License-CC_BY_4.0-lightgrey.svg)](LICENSE)
![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Compiler](https://img.shields.io/badge/g++-required-9cf.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-informational)
[![Build C++ Projects](https://github.com/sadhik-ali/NEWTWORK-STTC/actions/workflows/build.yml/badge.svg)](https://github.com/sadhik-ali/NEWTWORK-STTC/actions/workflows/build.yml)
![PRs](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)

*A learning-focused repository: no frameworks, no hidden magic — just standard C++ and file handling.*
</div>
---

## 📖 Table of Contents

- [About The Repository](#-about-the-repository)
- [Projects](#-projects)
- [Project 1: Bank Management System](#-project-1-bank-management-system)
  - [Key Features](#-key-features)
  - [Uploaded File Paths](#-uploaded-file-paths)
  - [Getting Started](#-getting-started)
  - [Sample Session](#-sample-session)
  - [Data File Formats](#-data-file-formats)
  - [Code Architecture](#-code-architecture)
- [Repository Layout](#-repository-layout)
- [Roadmap](#-roadmap)
- [Contributing](#-contributing)
- [License](#-license)
- [Contact](#-contact)

---

## About The Repository

This repository groups small, self-contained systems projects written the **long way on purpose** — every feature is implemented with plain language constructs so a beginner can read top to bottom and understand exactly what happens.

Each project:
- Lives in its **own folder** at the repository root
- Persists data in **plain text files** (no database to install)
- Ships with **build instructions that work on any OS**
- Is licensed under **Creative Commons Attribution 4.0 International**

---

## 🗂️ Projects

| # | Project | Language | Concepts Used | Status |
|---|---------|----------|---------------|--------|
| 1 | [Bank Management System](bank-management/) | C++17 | File handling, strings, structs-free data parsing, menus, validation | ✅ Available |
| 2 | Network Static Analysis (Python → NestJS migration) | TypeScript | Traffic monitoring, security checks | 🔜 Planned |

---

# 🏦 Project 1: Bank Management System

A console-based banking application with **account creation, balance inquiry, deposit, withdrawal and full transaction history** — all stored locally in text files.

**Source location:** [`bank-management/main.cpp`](bank-management/main.cpp)

## ✨ Key Features

| Feature | Menu Option | What It Does |
|---------|-------------|--------------|
| ➕ Create Account | `1` | Registers an account number, holder name and opening balance. Duplicate account numbers are rejected. |
| 💰 Balance Inquiry | `2` | Looks up an account and prints its name and current balance. |
| 📥 Deposit | `3` | Adds money to an account, rejecting zero and negative amounts. |
| 📤 Withdraw | `4` | Removes money with an **insufficient-balance guard**. |
| 🧾 Transaction History | `5` | Prints every `OPEN`, `DEPOSIT` and `WITHDRAW` entry for an account with a timestamp. |
| 🚪 Exit | `6` | Leaves the menu loop cleanly. |

**Built with beginner concepts only:** `#include`, `using namespace std`, `if/else`, `while`, `switch`, `for`, functions, `string`, `ifstream`, `ofstream`, `getline`, `ios::app`, `setw`, `setprecision`.

## 📁 Uploaded File Paths

Every file added to GitHub for this project, with its exact repository path:

```
NEWTWORK-STTC/
├── .github/
│   └── workflows/
│       └── build.yml              # CI: compiles every C++ project on push
├── bank-management/
│   ├── main.cpp                   # ⭐ Full application (menu + file handling)
│   └── README.md                  # Project-level quick start
├── LICENSE                        # Creative Commons Attribution 4.0 International
├── .gitignore                     # Build output + runtime data files
└── README.md                      # You are here
```

> **Note:** `accounts.txt` and `transactions.txt` are **created by the program at runtime** in the folder you launch it from. They are intentionally *not* committed, so the repository stays clean and every user starts fresh.

## 🚀 Getting Started

### Prerequisites

| Tool | Why | Check |
|------|-----|-------|
| A C++ compiler (MinGW `g++`, Clang, or MSVC) | Compiles the source | `g++ --version` |

<details>
<summary><b>Windows: install MinGW-w64 in two steps</b></summary>

1. Download **MSYS2** from [msys2.org](https://www.msys2.org/).
2. In the MSYS2 terminal run:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```
3. Add `C:\msys64\mingw64\bin` to your `PATH`, then open a new terminal and confirm with `g++ --version`.
</details>

### Build & Run

```bash
# 1. Move into the project folder
cd bank-management

# 2. Compile (any of these works)
g++ -std=c++17 main.cpp -o bank          # Linux / macOS / MinGW
g++ -std=c++17 -Wall main.cpp -o bank.exe # Windows, with warnings enabled

# 3. Run
./bank       # Linux / macOS
bank.exe     # Windows
```

No libraries to install, no build system to configure — one command, one binary.

## 🖥️ Sample Session

```
===== BANK MANAGEMENT SYSTEM =====
1. Create Account
2. View Balance
3. Deposit
4. Withdraw
5. Transaction History
6. Exit
Choose an option: 1

Enter account number: 1001
Enter account holder name: Sadhik Ali
Enter initial balance: 5000
Account created successfully!

Choose an option: 3

Enter account number: 1001
Enter deposit amount: 250.50
Deposited successfully. New balance: 5250.50

Choose an option: 4

Enter account number: 1001
Enter withdrawal amount: 9000
Insufficient balance!

Choose an option: 5

Enter account number: 1001

--- Transaction History ---
OPEN        5000.00       2026-10-25 11:42:07
DEPOSIT     250.50        2026-10-25 11:42:19
```

## 🗄️ Data File Formats

Both files use the `|` character as a field separator, so you can open them in any text editor and read them by eye.

**`accounts.txt`** — one line per account

```
accountNumber|holderName|balance
1001|Sadhik Ali|5250.50
```

**`transactions.txt`** — append-only log, one line per movement

```
accountNumber|type|amount|timestamp
1001|OPEN|5000.00|2026-10-25 11:42:07
1001|DEPOSIT|250.50|2026-10-25 11:42:19
```

| Field | Meaning |
|-------|---------|
| `type` | `OPEN`, `DEPOSIT` or `WITHDRAW` |
| `amount` | Money moved, always positive |
| `timestamp` | Written by the program as `YYYY-MM-DD HH:MM:SS` |

## 🧠 Code Architecture

Everything lives in `bank-management/main.cpp`, organised bottom-up: the file helpers are declared first, the menu features use them, and `main()` only runs the loop.

```
                    ┌──────────────────────┐
                    │        main()        │   menu loop + input validation
                    └───────────┬──────────┘
        ┌───────────┬───────────┼───────────┬────────────┐
        ▼           ▼           ▼           ▼            ▼
 createAccount  viewAccount  deposit   withdraw   showHistory
        │           │           │           │            │
        └───────────┴─────┬─────┴───────────┘            │
                          ▼                              ▼
                   findAccount()                 TRANSACTIONS_FILE
                   updateBalance()               (read line by line)
                          │
                          ▼
                   getCurrentTime()
                   saveTransaction()
                          │
                          ▼
                   accounts.txt / transactions.txt
```

| Function | Responsibility |
|----------|----------------|
| `getCurrentTime()` | Formats the system clock as `YYYY-MM-DD HH:MM:SS` for log entries. |
| `trimNewline()` | Strips trailing `\n` / `\r` so parsed fields are clean. |
| `findAccount()` | Scans `accounts.txt`, splits each line on `|`, returns the matching balance and name. |
| `updateBalance()` | Rewrites `accounts.txt` with one account's new balance — a safe read-all-then-write-all pattern. |
| `saveTransaction()` | Appends a single `acc\|type\|amount\|time` line to `transactions.txt`. |
| `createAccount()` | Menu 1 — validates uniqueness, then appends the new record. |
| `viewAccount()` | Menu 2 — read-only balance inquiry. |
| `deposit()` | Menu 3 — rejects non-positive amounts, then updates and logs. |
| `withdraw()` | Menu 4 — rejects non-positive amounts and overdrafts. |
| `showHistory()` | Menu 5 — filters the log by account number and prints a column-aligned table. |
| `main()` | Endless menu loop; `cin.clear()` / `cin.ignore()` recover from non-numeric input instead of crashing. |

### Known limitations (by design)

These are deliberate trade-offs that keep the code readable for a first project:

- **No password / PIN** — anyone with the account number can transact.
- **Fixed 1000-line buffer** in `updateBalance()` — fine for a demo, replace with a `vector<string>` for real volume.
- **Names must not contain `|`** — the delimiter would break parsing.
- **Not concurrent-safe** — run one instance at a time.

---

## 📦 Repository Layout

```
.
├── .github/workflows/build.yml   # Automated compile check on every push
├── bank-management/              # C++ console project (see above)
├── .gitignore
├── LICENSE                       # CC BY 4.0
└── README.md
```

## 🛣️ Roadmap

- [ ] PIN / password protection per account
- [ ] Replace the fixed array with `std::vector`
- [ ] Transfer between two accounts in one operation
- [ ] Monthly statement export
- [ ] Network static analysis module (Python → NestJS migration)

## 🤝 Contributing

Contributions are welcome — this project exists to be learned from.

1. Fork the repository and create a branch from `master`.
2. Keep the code beginner-readable: simple functions, explicit names, no external libraries.
3. Make sure the CI build passes (the workflow compiles every `.cpp` in the repo).
4. Open a pull request describing *what* changed and *why*.

## 📜 License

This project is licensed under the **Creative Commons Attribution 4.0 International** license
(**CC BY 4.0**) — full legal text in the [`LICENSE`](LICENSE) file.

🔗 Official deed: <https://creativecommons.org/licenses/by/4.0/>

You are free to **share** and **adapt** this material for any purpose, even commercially, as long as you give appropriate credit.

> **Attribution — please credit as:**
>
> *Network Static Toolkit* by **Sadhik Ali**, licensed under **CC BY 4.0**.
> Source: <https://github.com/sadhik-ali/NEWTWORK-STTC>

⚠️ A note for developers: Creative Commons itself recommends a software license such as MIT or GPL for code, because CC BY 4.0 does not include a patent grant or a copyleft clause. CC BY 4.0 is used here at the author's request and remains a valid choice for educational material.

## 📬 Contact

**Sadhik Ali** — [@sadhik-ali](https://github.com/sadhik-ali)

Repository: <https://github.com/sadhik-ali/NEWTWORK-STTC>

---

<div align="center">

*If this repository helped you learn, consider giving it a ⭐ — it helps other beginners find it.*

</div>
