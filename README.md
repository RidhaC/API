[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/nMS2JiQY)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=18625488)
# CYCS 3240 Project 3: I/O

**Due Date**: March 18, 2025 at 8:00 am  
**Collaboration Policy**:  Empty Hands

## Motivation
The UNIX file abstraction makes it difficult to remove data or insert data into a file except at the current end of file. In the UNIX abstraction, when data is written to a file anywhere except at the end, existing data is overwritten. In this project, you will create an API that allows users to easily insert or remove data at an arbitrary location in an existing file. This project will give you experience with routine use of the system call interface for file I/O.

## Requirements
You will write three functions: `insert`, which inserts data at a specified location within a file, `extract` which removes data from a specified location and returns the removed data to the caller, and `delete` which removes data from a specified location. A detailed specification for each routine follows.

### `int insert(int fd, void *buf, size_t bytes, size_t offset)`
Inserts `bytes` bytes read from the memory location `buf` into the file associated with `fd`. The bytes are inserted at an offset `offset` from the start of the file. For example, if the offset value is 0, then the data is inserted at the start of the file. If the offset is 2, then the data is inserted after the second byte of the file.

**All data in the file prior to the insertion must be in the file after the insertion.** No bytes are overwritten or deleted. When executed successfully, the file size will be increased by `bytes` bytes. A negative offset or an offset that is greater than the current file size is an error. The return value is the number of bytes actually written, or a negative value on error. On return, the current position for `fd` should be at `offset + size` (immediately after the last byte that was inserted).

### `int delete(int fd, size_t bytes, size_t offset)`
Deletes data at the specified location. The parameter `bytes` contains the number of bytes that should be deleted. When executed successfully, the file size will be reduced by `bytes` bytes. The parameter `offset` indicates the offset at which the delete should begin. An offset of zero indicates the first byte deleted is the first byte of the file. A negative offset is an error. The value of `offset + bytes` cannot be greater than the size of the file prior to the delete. The return value is the number of bytes actually deleted, or a negative value on error. On return, the current position for `fd` should be at `offset` (immediately preceding the first byte that was deleted).

### `int extract(int fd, void *buf, size_t bytes, size_t offset)`
Operates like `delete` except that the data removed from the file is written to the memory location given by `buf`. The return value is the number of bytes deleted or a negative value on error.

## Notes
- Assume that `fd` is the return value from an earlier successful call to open. Your routines should return an error if the file specified by `fd` cannot be read or written as required by the specified operation. Note that calls to `read` and `write` will detect this error and return a value that can be propagated to the user. Do not open files within the routines.
- Assume that `buf` has been allocated previously. It is not required to detect whether the input value for `buf` is valid. Do not allocate memory within these routines that is not also deallocated within the routine.
- Errors from system calls made within these routines should result in an error return from your library routine.
- You do not need to consider the effects of multiple processes operating on a file that is modified by these routines.
- Consider the time it takes to execute a system call as you write these routines. **Do not process data character by character.**
- Offset 0 precedes the first byte of the file. Offset 1 follows the first byte of the file.
- The size of a file can be modified using the `truncate` and `ftruncate` system calls. These are described in section two of the manual pages.
- If a file has 10 bytes, an insert at offset 10 (at current end of file) is successful. An insert at offset 11 is an error.
- You must use the system call file interface. **Use of the stdio library (fopen, fread, fwrite etc.) is not allowed and will result in a grade of 0.** If you think you have to use a routine that is not part of the system call interface, get in touch with me before using the routine.

## Makefile
Each routine should be implemented in a separate file, `insert()` in `insert.c`, `delete()` in `delete.c`, and `extract()` in `extract.c`.

The header file named `ufsext.h` is included to define the API given above. The header containes function declarations for the API. You may add to, but not delete from, this file.

A `makefile` is provided. The default target (i.e., typing just `make`) builds `insert.o`, `delete.o`, `extract.o`. The command `make run` compiles the test routine `test.c`, links it against your files, and runs the testing code. 

## Notes

**Pay close attention to the subroutine and file names given in this specification, as well as the specified order of parameters.** If the grader cannot link a test against your routines, or a test fails because your implementation deviates from this specification in some obvious way, the test grade may be zero. These requirements are likely to be strictly enforced due to the class size.

The submission is due on March 18 at 8am. Include a single README that describes each file in your project directory.

## Collaboration
Empty hands discussions are allowed for this project.

