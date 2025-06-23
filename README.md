# File I/O Utility Library (Custom Insert, Delete, and Extract)

**Project Type**: Systems Programming / File Manipulation  
**Languages Used**: C (System Call Interface)  
**Date Completed**: March 2025  

## Overview

This project implements a low-level file I/O utility library in C that allows inserting, deleting, and extracting bytes at arbitrary positions within a file—something not natively supported by the standard UNIX file system interface. It was developed as part of my coursework in systems programming, where the focus was on direct use of system calls without relying on high-level stdio libraries.

## Features

- `insert(int fd, void *buf, size_t bytes, size_t offset)`  
  Inserts bytes into a file at a specific offset without overwriting existing data.

- `delete(int fd, size_t bytes, size_t offset)`  
  Deletes a specified number of bytes from a given position in the file.

- `extract(int fd, void *buf, size_t bytes, size_t offset)`  
  Similar to delete, but stores the removed data into a buffer for reuse.

These functions manipulate files using low-level system calls like `read`, `write`, `lseek`, and `ftruncate`, providing behavior similar to in-place editing of files.

## Technical Highlights

- Uses UNIX system calls (`open`, `read`, `write`, `lseek`, `ftruncate`)
- Avoids stdio (`fopen`, `fread`, etc.) for lower-level control
- Validates offset boundaries and handles edge cases
- Efficient data shifting (no byte-by-byte processing)

## File Structure

- `insert.c` — Implements the `insert()` function
- `delete.c` — Implements the `delete()` function
- `extract.c` — Implements the `extract()` function
- `ufsext.h` — Header file for API declarations
- `test.c` — Test suite
- `Makefile` — Build and test automation
- `README.md` — Project documentation (this file)

## How to Run

```bash
make           # Builds insert.o, delete.o, extract.o
make run       # Compiles and runs the test program
