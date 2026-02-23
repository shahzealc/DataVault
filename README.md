# DataVault

A lightweight, command-line key-value database application written in C++ with persistent storage capabilities.

## Overview

DataVault is an interactive in-memory database engine that allows you to store and retrieve key-value pairs through a simple command-line interface. All data is automatically persisted to disk, ensuring no data loss after application restarts.

## Features

- **Key-Value Storage**: Store and retrieve data with string keys
- **Multiple Data Types**: Support for strings, integers, doubles, and booleans
- **Automatic Persistence**: Data is automatically saved to disk and loaded on startup
- **Interactive CLI**: User-friendly command-line interface with real-time feedback
- **Type Detection**: Automatic detection and conversion of data types

## Building the Project

### Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler (MSVC, GCC, Clang)

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build . --config Debug
```

## Running DataVault

After building, run the executable:

```bash
./DataVault
```

Or if built in the `build` directory:

```bash
./build/Debug/DataVault
```

## Command Reference

DataVault supports the following commands:

### SET
Store a key-value pair in the database.

```
SET <key> <value>
```

**Example:**
```
> SET user_count 42
> SET name "John Doe"
> SET temperature 98.6
> SET is_active true
```

### GET
Retrieve a value by its key.

```
GET <key>
```

**Example:**
```
> GET user_count
Success: 42
```

### DEL
Delete a key-value pair from the database.

```
DEL <key>
```

**Example:**
```
> DEL user_count
Success: Key deleted
```

### COUNT
Display the total number of entries in the database.

```
COUNT
```

**Example:**
```
> COUNT
Success: 3
```

### LIST
Display all key-value pairs in the database.

```
LIST
```

**Example:**
```
> LIST
Success: name=John Doe, user_count=42, temperature=98.6
```

### CLEAR
Delete all entries from the database.

```
CLEAR
```

**Example:**
```
> CLEAR
Success: Database cleared
```

### HELP
Display available commands.

```
HELP
```

### EXIT
Exit the application and save all changes.

```
EXIT
```

## Data Persistence

DataVault automatically saves all data to a file named `datastore.txt` in the build directory. This file is created automatically when the application runs. The data is:

- **Loaded** when the application starts
- **Saved** when the application exits
- **Persisted** across sessions
