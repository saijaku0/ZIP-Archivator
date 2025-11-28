# **Huffman Archiver**

## **🌟 Project Description**

Huffman Archiver is a command-line utility written in C++20 that uses the Huffman Coding Algorithm for lossless file compression and decompression.

The project is designed as an educational example to explore the fundamentals of data compression algorithms and modern C++20 features (file handling, smart pointers, classes).

## **🚀 Algorithm Used**

### The project implements Lossless Compression:

1. Frequency Counting: Determines the frequency of occurrence for each byte in the source file.

2. Huffman Tree Construction: An optimal binary tree is built based on the calculated frequencies.

3. Encoding: Each byte is assigned a variable-length binary code (the more frequent the byte, the shorter its code).

4. File Format: The compressed file (.huf) contains a header (the code table/reconstructed tree) and the compressed data body.

### 🛠️ Project Structure

The project is organized using a modular approach:

| File / Class | Description |
|--------------|-------------|
| main.cpp | Entry Point. Handles user input (interactive mode). |
| ArchiverCore.h/.cpp | Archiver Core. Contains the main compress and decompress methods, as well as the logic for reading/writing the header.|
| Huffman.h | Contains the HuffmanNode and CodeTable structures, and the Huffman class for tree construction and code generation (Steps 2 and 3). |
| BitStream.h | Contains the BitWriter and BitReader classes for efficient bitwise writing and reading of data (critical for Steps 4 and 5). |

### ⚙️ Building the Project (Using CMake)

1. The project requires a compiler with C++20 support (e.g., GCC 10+ or Visual Studio 2019+).

Clone the repository:
```
git clone https://github.com/saijaku0/ZIP-Archivator.git
cd HuffmanArchiver
```

2. Build the project:
```
mkdir build
cd build
cmake ..
make
```
- After a successful build, the executable file archiver will be located in the build directory.

### 🚀 Interactive Usage

Since you are using the interactive version of main.cpp for debugging convenience, the program will prompt you for input.

Step 1: Preparation

Create a test file, e.g., ```test.txt```, in the same folder as the ```archiver``` executable (usually the build or Debug directory in Visual Studio).

Step 2: Running the Program

Run ```archiver.exe``` and follow the instructions:
```
=== Huffman Archiver ===
Select action:
1. Compress file
2. Decompress file
Your choice (1 or 2): 1 

Enter input filename (e.g. test.txt): test.txt
Enter output filename (e.g. result.huf): archive.huf

--- Starting process ---
✅ File successfully compressed: archive.huf

```

Step 3: Decompression

To decompress, select ```2``` and use the compressed file as the input:
```
=== Huffman Archiver ===
Select action:
...
Your choice (1 or 2): 2

Enter input filename (e.g. test.txt): archive.huf
Enter output filename (e.g. result.huf): test_restored.txt

--- Starting process ---
✅ File successfully decompressed: test_restored.txt
```

