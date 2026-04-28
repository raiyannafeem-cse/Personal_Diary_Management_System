<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c&logoColor=white" alt="C Language"/>
  <img src="https://img.shields.io/badge/Course-CSE115-green?style=for-the-badge" alt="CSE115"/>
  <img src="https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge" alt="Status"/>
</p>

# 📔 PIN-Protected Personal Diary

> A console-based personal diary application implemented in **C**, using core programming concepts from **CSE115 — Introduction to Programming**.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Entry Representation](#entry-representation)
- [How It Works](#how-it-works)
  - [PIN Authentication](#pin-authentication)
  - [Writing a Note](#writing-a-note)
  - [Searching & Reading Notes](#searching--reading-notes)
- [Project Structure](#project-structure)
- [Code Reference](#code-reference)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [File Format](#file-format)
- [Course Topics Applied](#course-topics-applied)
- [Constraints & Notes](#constraints--notes)
- [Team — Group 7](#team--group-7)

---

## Overview

A diary is a private record of dated entries. This project addresses three fundamental problems:

1. **Protecting** access to the diary using a hardcoded PIN with limited attempts.
2. **Recording** new notes with structured metadata (date, location, topic, description).
3. **Retrieving** past notes by either listing all entries or filtering by a search term.

All data is persisted to a plain-text file (`diary.txt`) so notes survive between sessions. The interface is fully terminal-driven and clears the screen between actions for a clean user experience.

---

## Features

| Feature | Status |
|---|---|
| PIN-protected access (3 attempts max) | ✅ Core |
| Write structured notes (date, location, topic, description) | ✅ Core |
| Append-mode persistence (no entries are overwritten) | ✅ Core |
| Search notes by any keyword (date, location, topic, etc.) | ✅ Core |
| View all entries when no search term is provided | ✅ Core |
| Menu-driven interface | ✅ Core |
| Screen clear between menu actions (`cls` / `clear`) | ✅ Core |
| Multi-word input support via `fgets()` | ✅ Core |
| Graceful handling of empty/missing diary file | ✅ Core |

---

## Entry Representation

Each diary entry is stored on a **single line** in `diary.txt` using the **pipe character (`|`)** as a field separator. This makes the file both human-readable and easily parseable for search.

```
<date> | <location> | <topic> | <description>
```

Each field is captured into its own fixed-size character buffer in memory:

| Field | Buffer | Size | Example |
|---|---|---|---|
| Date | `char date[15]` | 15 | `12/04/2026` |
| Location | `char location[50]` | 50 | `NSU Library` |
| Topic | `char subject[100]` | 100 | `Midterm Prep` |
| Description | `char description[10000]` | 10,000 | Long-form note text |

> Newline characters captured by `fgets()` are stripped with `strcspn()` before writing, so each entry stays on exactly one line in the file.

### Example (saved file view)

```
12/04/2026 | NSU Library | Midterm Prep | Reviewed loops and arrays for CSE 115.
13/04/2026 | Home | Reflection | Felt productive today, finished MAT 116 problems.
14/04/2026 | Cafeteria | Random Thoughts | Coffee was good, conversation was better.
```

When searching for `NSU`, the first line is matched and printed. When searching for `MAT`, the second line is matched. Pressing Enter without typing a term displays every entry.

---

## How It Works

### PIN Authentication

Access is gated behind a `for` loop that runs up to **3 times**:

1. The screen is cleared and the user is prompted for a PIN.
2. `fgets()` captures the input (so spaces are handled safely) and `strcspn()` strips the trailing newline.
3. `strcmp()` compares the input to the hardcoded PIN `"CSE115"`.
4. On match, control falls through to the main diary loop. On mismatch, the user is told the PIN was wrong and the loop iterates again.
5. After 3 failed attempts, the program prints a closing message and exits with `return 0`.

> Because the PIN is hardcoded as a string literal, any change requires recompiling the program — this is intentional for a course project.

### Writing a Note

Selecting option **1** opens `diary.txt` in **append mode** (`"a"`), so new entries never overwrite existing ones:

1. The user is prompted for **date**, **location**, **topic**, and **description** in turn.
2. Each field is read with `fgets()` (which preserves spaces) and the trailing `\n` is stripped using `strcspn()`.
3. `fprintf()` writes the four fields to the file separated by `|` and terminated with a newline.
4. `fclose()` flushes and closes the file so the entry is safely persisted before returning to the menu.

### Searching & Reading Notes

Selecting option **2** opens `diary.txt` in **read mode** (`"r"`):

1. If the file doesn't exist yet (`fp == NULL`), the program reports that the diary is empty and returns to the menu.
2. The user is asked for a search term — pressing Enter without typing anything triggers "view all" mode.
3. `fgets()` reads the file **one line at a time** until EOF.
4. For each line, `strstr()` checks whether the search term appears anywhere in that line. If the search string is empty (`strlen(search) == 0`), every line is printed.
5. A `found` flag tracks whether at least one match was printed; if it stays `0`, a "Not found!" message is shown.
6. `fclose()` closes the file when reading is complete.

```
Authentication → 3 attempts using strcmp() against hardcoded PIN.
Write          → fopen("a") → fgets() × 4 → fprintf() with '|' separators → fclose().
Search         → fopen("r") → fgets() per line → strstr() match → print → fclose().
```

This approach uses only **selection, loops, arrays, strings, and file I/O** — all core CSE115 topics.

---

## Project Structure

Everything lives in a **single source file**. All logic runs inside `main()` using nested loops and a `switch` statement:

```
project/
├── dairy.c      # All code: authentication, menu, write, search
├── dairy.exe    # Compiled binary (after running gcc)
├── diary.txt    # Auto-created on first write; stores all entries
└── README.md
```

---

## Code Reference

All logic is contained within `main()` in `dairy.c`. The structure can be broken down into the following logical blocks:

### Authentication Block

```c
for (int i = 1; i <= 3; i++) {
    // Prompt for PIN, read with fgets(), strip newline.
    // Compare against "CSE115" using strcmp().
    // On match: enter main menu loop.
    // On 3 failures: exit with closing message.
}
```

### Main Menu Loop

```c
while (1) {
    // Display menu and read user choice with scanf().
    // Flush leftover newline from input buffer.
    // Dispatch to the appropriate case via switch.
}
```

### Case 1 — Write a Note

```c
fp = fopen("diary.txt", "a");
// Read date, location, subject, description with fgets().
// Strip trailing newlines with strcspn().
// Write all four fields with fprintf() using '|' separators.
fclose(fp);
```

### Case 2 — Search & Read

```c
fp = fopen("diary.txt", "r");
// Handle missing-file case gracefully.
// Read search term; empty term means "view all".
// Loop with fgets() and test each line with strstr().
// Track matches with a 'found' flag.
fclose(fp);
```

### Case 3 — Exit

```c
return 0;  // Terminates the infinite menu loop and ends the program.
```

---

## Getting Started

### Prerequisites

- **GCC** or any standard C compiler.

### Compile

```bash
gcc dairy.c -o dairy
```

### Run

```bash
./dairy
```

---

## Usage

On launch, the program first asks for a PIN. After successful authentication, it presents the main menu:

```
======= MY Diary =======

1.Write a Note
2.Search and Read Notes
3.Exit

Choose One Number:
```

- **Write a Note** — prompts for date, location, topic, and the full note text, then appends the entry to `diary.txt`.
- **Search and Read Notes** — asks for a search term; press Enter to view every entry, or type a keyword (e.g. a date, a location, or a topic word) to filter.
- **Exit** — closes the program with a goodbye message.

> The default PIN is **`CSE115`**. After 3 wrong attempts the program closes automatically.

---

## File Format

Saved entries use a simple pipe-separated plain-text format. Each entry is exactly one line:

```
<date> | <location> | <topic> | <description>
```

Example (`diary.txt`):

```
12/04/2026 | NSU Library | Midterm Prep | Reviewed C loops and arrays.
13/04/2026 | Home | Reflection | Productive day, knocked out MAT 116 problems.
14/04/2026 | Cafeteria | Random | Coffee was good, conversation was better.
```

Because the file is opened in **append mode**, the order of entries always reflects the order they were written.

---

## Course Topics Applied

This project demonstrates practical application of the following **CSE115** concepts:

| Topic | Where It Appears in the Project |
|---|---|
| **Selection** (`if`, `switch`) | PIN check, menu dispatch, empty-file handling, search-match check |
| **Loops** (`for`, `while`) | 3-attempt PIN loop, infinite menu loop, line-by-line file reading, input-buffer flushing |
| **Arrays / Strings** | `char` buffers for date, location, topic, description, search term, PIN, and line buffer |
| **String Handling** (`strcmp`, `strcspn`, `strstr`, `strlen`) | PIN comparison, newline stripping, substring search, empty-search detection |
| **Standard I/O** (`printf`, `scanf`, `fgets`, `getchar`) | All user input/output, including buffer cleanup after `scanf()` |
| **File Handling** (`FILE*`, `fopen`, `fprintf`, `fgets`, `fclose`) | Persisting and reading diary entries to/from `diary.txt` |
| **System Calls** (`system()`) | Cross-platform screen clearing via `cls \|\| clear` |

---

## Constraints & Notes

- The PIN is hardcoded as `"CSE115"` and only 3 attempts are allowed per program run.
- The diary file (`diary.txt`) is created automatically on the first successful write.
- Field sizes are bounded: date (15), location (50), topic (100), description (10,000), line buffer (15,000), PIN input (70). Any input longer than the buffer is truncated by `fgets()`.
- `fgets()` is used everywhere instead of `scanf("%s")` so multi-word inputs (e.g. `NSU Library`) work correctly.
- After every `scanf()`, a `while (getchar() != '\n');` loop drains the leftover newline from `stdin` to prevent it from being captured by the next `fgets()`.
- Search is **case-sensitive** — `NSU` and `nsu` are treated as different terms.
- The `|` character is reserved as the field separator and should not be used inside a note's content, otherwise search and visual layout may become inconsistent.
- The terminal must support either `cls` (Windows) or `clear` (Unix) for the screen-clearing system call to render correctly. The `||` operator ensures one will work regardless of platform.
- All file pointers are closed via `fclose()` after each operation so no data is lost.
- Only **`stdio.h`**, **`stdlib.h`**, and **`string.h`** are required — no external libraries needed.
- The entire project compiles as a single file (`dairy.c`).

---

## Team — Group 7

| ID | Name |
|---|---|
| 2613859042 | Abu Sayed Abdul Adnan |
| 2533561642 | Taufiq Omar |
| 2614064042 | Shahriar Ahmed |
| 2612691642 | Nafeem Raiyan Hasan |

---

<p align="center">
  Made with ❤️ for CSE115 — Group 7
</p>
