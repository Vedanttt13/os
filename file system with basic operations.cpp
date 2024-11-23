#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

#define MAX_BLOCKS 100 // Maximum number of storage blocks for simplicity

// Structure for an inode to store file metadata
struct Inode {
    string name;
    int size;
    vector<int> blocks; // List of blocks allocated to the file
};

// Simple File Allocation Table (FAT) array to track block usage
int FAT[MAX_BLOCKS];

// FileSystem class to manage files and operations
class FileSystem {
    map<string, Inode> files;  // Mapping of file names to inodes
public:
    FileSystem() {
        // Initialize FAT to -1 (indicating all blocks are free)
        for (int i = 0; i < MAX_BLOCKS; i++) {
            FAT[i] = -1;
        }
    }

    // Create a file with a given name and size (in blocks)
    bool createFile(const string& name, int size) {
        if (files.find(name) != files.end()) {
            cout << "File already exists.\n";
            return false;
        }

        Inode inode = { name, size, {} };
        int blocksAllocated = 0;

        // Allocate blocks for the file
        for (int i = 0; i < MAX_BLOCKS && blocksAllocated < size; i++) {
            if (FAT[i] == -1) {  // Free block found
                FAT[i] = 1;  // Mark block as used
                inode.blocks.push_back(i);
                blocksAllocated++;
            }
        }

        if (blocksAllocated < size) {
            cout << "Not enough space.\n";
            return false;
        }

        files[name] = inode;
        cout << "File created: " << name << "\n";
        return true;
    }

    // Delete a file by name
    bool deleteFile(const string& name) {
        map<string, Inode>::iterator it = files.find(name);
        if (it == files.end()) {
            cout << "File not found.\n";
            return false;
        }

        // Free blocks used by the file
        for (size_t i = 0; i < it->second.blocks.size(); i++) {
            FAT[it->second.blocks[i]] = -1;  // Mark block as free
        }

        files.erase(it);
        cout << "File deleted: " << name << "\n";
        return true;
    }

    // Read a file by name
    void readFile(const string& name) {
        map<string, Inode>::iterator it = files.find(name);
        if (it == files.end()) {
            cout << "File not found.\n";
            return;
        }

        cout << "Reading file: " << name << ", Size: " << it->second.size << " blocks\n";
    }

    // Write additional data to a file by name (in blocks)
    bool writeFile(const string& name, int additionalSize) {
        map<string, Inode>::iterator it = files.find(name);
        if (it == files.end()) {
            cout << "File not found.\n";
            return false;
        }

        int blocksAllocated = 0;
        for (int i = 0; i < MAX_BLOCKS && blocksAllocated < additionalSize; i++) {
            if (FAT[i] == -1) {
                FAT[i] = 1;
                it->second.blocks.push_back(i);
                blocksAllocated++;
            }
        }

        if (blocksAllocated < additionalSize) {
            cout << "Not enough space to write additional data.\n";
            return false;
        }

        it->second.size += additionalSize;
        cout << "Data written to file: " << name << ", New Size: " << it->second.size << " blocks\n";
        return true;
    }
};

// Main function to demonstrate the file system operations
int main() {
    FileSystem fs;

    // Perform basic file operations
    fs.createFile("file1", 10);  // Create a file with 10 blocks
    fs.readFile("file1");  // Read the file
    fs.writeFile("file1", 5);  // Write additional 5 blocks
    fs.deleteFile("file1");  // Delete the file

    return 0;
}

