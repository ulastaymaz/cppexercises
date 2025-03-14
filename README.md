# cppexercises
Several exercises for practice. 
## Library Management 
Created admin and user panel. Books, users and admin info is saved in local text file. Nothing fancy, just trying to get used to OOP structures.

## Linear Algebra
Second exercise for OOP practice. Created Matrix class and added severeal linear algebra tool.

*Features*
- **LU Decomposition**: It doesn't work; however, I kept it for future implementations.
- **QR Decomposition**: I implemented QR decomposition, however for N x N matrices where N > 100, it doesn't produce a good result.
- **Random Matrix Generation**: For testing, pseudo-random matrices with elements between -10.0 and 10.0 are generated.
- **Error Calculation**: Calculates the error of the decompositions by taking the element-wise difference.

I created a test for random matrices' QR decomposition errors. 

## MiniShell File Manager

MiniShell File Manager is a command-line-based file management tool. It allows users to perform various file system operations such as navigating directories, creating and deleting files or folders, renaming files, copying and pasting files or folders, and searching for specific files or folders.

*Features*

- **Navigate Directories**:
  - `-enter` or `-e`: Enter a folder in the current directory.
  - `-up` or `-u`: Move to the parent directory.

- **File and Folder Management**:
  - `-list` or `-l`: List all files in the current directory.
  - `-listdir` or `-ld`: List all directories in the current directory.
  - `-create` or `-cr`: Create a new folder.
  - `-delete` or `-d`: Delete a file or folder.
  - `-rename` or `-rm`: Rename a file or folder.

- **Copy and Paste**:
  - `-copy` or `-cd`: Copy a file or folder.
  - `-paste` or `-pd`: Paste the copied file or folder to the current directory.

- **Search**:
  - `-search` or `-sr`: Search for a file or folder starting from the root directory. I use BFS search for file searching.
