# 🏦 Bank Management System (C++)

Console-based banking application with account creation, balance inquiry, deposit,
withdrawal and transaction history, persisted in plain text files.

Part of the [Network Static Toolkit](../README.md) repository.

## Quick start

```bash
g++ -std=c++17 -Wall main.cpp -o bank
./bank          # Windows: bank.exe
```

On first run the program creates `accounts.txt` and `transactions.txt` next to the
executable. See the [main README](../README.md#-project-1-bank-management-system)
for the full documentation, data formats and architecture notes.

## Files in this folder

| Path | Role |
|------|------|
| `bank-management/main.cpp` | Complete application source |
| `bank-management/README.md` | This file |
| `accounts.txt` | Created at runtime — account records |
| `transactions.txt` | Created at runtime — transaction log |

## License

[Creative Commons Attribution 4.0 International (CC BY 4.0)](../LICENSE)
— © Sadhik Ali. Credit this repository if you reuse or adapt the code.
