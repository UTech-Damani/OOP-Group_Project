# KPFL corrected source

## Build with GCC / MinGW

From this directory, compile the application with:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp -o KPFL
```

On Windows, MinGW can use the same command and produce `KPFL.exe`.
You can also open `main.cbp` in Code::Blocks and build the Debug target.

The application creates/uses the `data` directory for CSV persistence.
Use the File Management menu to save and reload teams, people, fixtures,
stadiums, match results, and products. Ticket purchases and shop transactions
are recorded as they occur.
