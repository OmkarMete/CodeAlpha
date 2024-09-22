#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void listFiles(const string& path) {
    cout << "Contents of directory: " << path << endl;
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << (entry.is_directory() ? "[DIR]  " : "[FILE] ") << entry.path().filename() << endl;
    }
}

void createDirectory(const string& path) {
    if (fs::create_directory(path)) {
        cout << "Directory created: " << path << endl;
    } else {
        cout << "Failed to create directory." << endl;
    }
}

void copyFile(const string& source, const string& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        cout << "File copied from " << source << " to " << destination << endl;
    } catch (fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void moveFile(const string& source, const string& destination) {
    try {
        fs::rename(source, destination);
        cout << "File moved from " << source << " to " << destination << endl;
    } catch (fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void deleteFileOrDirectory(const string& path) {
    try {
        if (fs::remove_all(path)) {
            cout << "Deleted: " << path << endl;
        } else {
            cout << "Failed to delete: " << path << endl;
        }
    } catch (fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main() {
    string command, path, source, destination;
    
    while (true) {
        cout << "\n=== Basic File Manager ===" << endl;
        cout << "1. List files and directories\n2. Create directory\n3. Copy file\n4. Move file\n5. Delete file/directory\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> command;

        if (command == "1") {
            cout << "Enter the directory path: ";
            cin >> path;
            listFiles(path);
        } else if (command == "2") {
            cout << "Enter the directory path to create: ";
            cin >> path;
            createDirectory(path);
        } else if (command == "3") {
            cout << "Enter source file path: ";
            cin >> source;
            cout << "Enter destination file path: ";
            cin >> destination;
            copyFile(source, destination);
        } else if (command == "4") {
            cout << "Enter source file path: ";
            cin >> source;
            cout << "Enter destination file path: ";
            cin >> destination;
            moveFile(source, destination);
        } else if (command == "5") {
            cout << "Enter the file/directory path to delete: ";
            cin >> path;
            deleteFileOrDirectory(path);
        } else if (command == "6") {
            cout << "Exiting the file manager." << endl;
            break;
        } else {
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}
