# OS Project 3 --- Process Information Merger

------------------------------------------------------------------------

## Objective

To create a program that: 1. Collects process information using Linux
`ps` commands. 2. Stores process data into structured memory. 3. Merges
multiple process datasets using a common key (PID). 4. Produces a
unified process report.

------------------------------------------------------------------------

## Features

-   Executes Linux process monitoring commands automatically.
-   Parses output files generated from:
    -   `ps aux`
    -   `ps -eLf`
-   Uses PID as a linking attribute to merge datasets.
-   Structured storage using a custom `ProcessInfo` structure.
-   Generates a formatted merged report.
-   Automatically cleans temporary files after execution.

------------------------------------------------------------------------

## Technologies Used

-   **Language:** C
-   **Platform:** Linux / WSL / Unix-like systems
-   **Concepts:** Operating Systems, Process Management, File Handling,
    Structs

------------------------------------------------------------------------

## Program Workflow

1.  The program runs:

    ``` bash
    ps aux > x1.txt
    ps -eLf > x2.txt
    ```

2.  Data from `ps aux` is read and stored into an array of structures.

3.  Data from `ps -eLf` is read line-by-line.

4.  The program matches processes using **PID**.

5.  Matching entries are merged and written into:

        merged.txt

6.  The merged result is displayed on the terminal.

7.  Temporary files (`x1.txt`, `x2.txt`) are deleted automatically.

------------------------------------------------------------------------

## Data Structure Used

``` c
typedef struct {
    int pid;
    char cpu[10];
    char mem[10];
    char vsz[16];
    char rss[16];
    char tty[16];
    char stat[10];
    char start[16];
    char time[16];
    char command[256];
} ProcessInfo;
```

This structure stores process-related fields extracted from `ps aux`.

------------------------------------------------------------------------

## Compilation Instructions

Use GCC compiler:

``` bash
gcc main.c -o main
```

------------------------------------------------------------------------

## Execution

Run the executable:

``` bash
./main
```

------------------------------------------------------------------------

## Output

The program generates:

    merged.txt

This file contains combined process information including: - UID - PID -
Parent Process ID - Thread details - CPU & Memory usage - Virtual and
Resident memory - Process state - Start time - Execution time - Command
name

------------------------------------------------------------------------

## Requirements

-   Linux operating system or WSL
-   GCC compiler
-   `ps` command availability

------------------------------------------------------------------------

## Limitations

-   Fixed array size (supports up to 10,000 processes).
-   Parsing depends on standard Linux `ps` output format.
-   Designed primarily for educational purposes.

------------------------------------------------------------------------

## Learning Outcomes

Through this project, students understand: - Interaction between user
programs and OS utilities. - Process inspection in Linux. - File parsing
and formatted data merging. - Practical application of Operating System
concepts.

------------------------------------------------------------------------

## Authors

PALURI VEERA DURGA VARA PRASAD --- 24CS8031

GOGULAMUDI PREM SANTHOSH --- 24CS8032

PRADIP GORAI --- 24CS8033

GUNTREDDI NEELAPRASANTH --- 24CS8034

DARLA POOJITHA --- 24CS8035

ANJALI SINGH --- 24CS8036

ANIKET HALDAR --- 24CS8037

ARPIT VERMA --- 24CS8038

HIMANSHU GUPTA --- 24CS8039

RAJ GURU --- 24CS8040


------------------------------------------------------------------------

