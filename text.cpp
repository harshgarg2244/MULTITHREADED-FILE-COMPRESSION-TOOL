#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;

// Function to compress data using Run-Length Encoding (RLE)
string compressRLE(const string& data) {
    string compressed = "";
    int n = data.size();
    
    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i < n - 1 && data[i] == data[i + 1]) {
            count++;
            i++;
        }
        compressed += data[i] + to_string(count);
    }
    return compressed;
}

// Function to decompress data using Run-Length Encoding (RLE)
string decompressRLE(const string& data) {
    string decompressed = "";
    int n = data.size();
    
    for (int i = 0; i < n; i++) {
        char ch = data[i];
        string countStr = "";
        i++;
        while (i < n && isdigit(data[i])) {
            countStr += data[i];
            i++;
        }
        i--;
        int count = stoi(countStr);
        decompressed.append(count, ch);
    }
    return decompressed;
}

// Multithreaded function to compress a file
void compressFile(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in) {
        cerr << "Error opening input file!" << endl;
        return;
    }
    
    ofstream out(outputFile, ios::binary);
    if (!out) {
        cerr << "Error opening output file!" << endl;
        return;
    }
    
    string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    int chunkSize = data.size() / 4;
    vector<string> compressedChunks(4);
    vector<thread> threads;
    
    auto compressChunk = [&](int start, int stop, int index) {
        compressedChunks[index] = compressRLE(data.substr(start, stop - start));
    };
    
    // Adjust chunking to avoid breaking sequences
    for (int i = 0; i < 4; i++) {
        int start = i * chunkSize;
        int stop = (i == 3) ? data.size() : start + chunkSize;
        while (stop < data.size() && data[stop] == data[stop - 1]) stop++;
        threads.emplace_back(compressChunk, start, stop, i);
    }
    
    for (auto& t : threads) t.join();
    
    // Synchronized writing
    for (const auto& chunk : compressedChunks) {
        lock_guard<mutex> lock(mtx);
        out << chunk;
    }
    
    cout << "Compression completed." << endl;
}

// Multithreaded function to decompress a file
void decompressFile(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in) {
        cerr << "Error opening input file!" << endl;
        return;
    }
    
    ofstream out(outputFile, ios::binary);
    if (!out) {
        cerr << "Error opening output file!" << endl;
        return;
    }
    
    string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    int chunkSize = data.size() / 4;
    vector<string> decompressedChunks(4);
    vector<thread> threads;
    
    auto decompressChunk = [&](int start, int stop, int index) {
        decompressedChunks[index] = decompressRLE(data.substr(start, stop - start));
    };
    
    // Adjust chunking to avoid breaking sequences
    for (int i = 0; i < 4; i++) {
        int start = i * chunkSize;
        int stop = (i == 3) ? data.size() : start + chunkSize;
        while (stop < data.size() && isdigit(data[stop])) stop++;
        threads.emplace_back(decompressChunk, start, stop, i);
    }
    
    for (auto& t : threads) t.join();
    
    // Synchronized writing
    for (const auto& chunk : decompressedChunks) {
        lock_guard<mutex> lock(mtx);
        out << chunk;
    }
    
    cout << "Decompression completed." << endl;
}

int main() {
    string inputFile = "input.txt";
    string compressedFile = "compressed.rle";
    string decompressedFile = "output.txt";
    
    cout << "Compressing file..." << endl;
    compressFile(inputFile, compressedFile);
    
    cout << "Decompressing file..." << endl;
    decompressFile(compressedFile, decompressedFile);
    
    return 0;
}
