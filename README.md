# MULTITHREADED-FILE-COMPRESSION-TOOL
COMPANY : CODTECH IT SOLUTIONS  
NAME: HARSH GARG  
INTERN ID: CT04WP68  
DOMAIN: C++ PROGRAMMING  
DURATION: 4WEEKS  
MENTOR: NEELA SANTOSH  
DESCRIPTION:  
A **Multithreaded File Compression Tool** is a high-performance C++ application designed to efficiently compress and decompress files using **multithreading** for improved speed and resource utilization. This project leverages parallel computing to process large files by splitting them into multiple chunks, allowing simultaneous compression or decompression operations to maximize CPU usage. The tool employs **Run-Length Encoding (RLE)** or other compression algorithms to reduce file size while maintaining data integrity. Using the **fstream** library, the program reads files in binary mode, processes data using multiple threads, and writes the compressed output to a new file. The decompression process follows a similar approach, restoring the original content by reconstructing the data. The project implements **mutex locks** to handle concurrent writes and avoid race conditions, ensuring that multiple threads do not interfere with each other's output. Users interact with the application through a **command-line interface (CLI)**, selecting between compression and decompression modes while specifying input and output file paths.   

The **performance optimization** comes from dividing files into smaller segments, where each thread processes a chunk independently, significantly reducing execution time compared to a single-threaded approach. If the file is too small, the tool dynamically adjusts the number of threads to prevent unnecessary overhead. The application includes error handling for **file I/O errors, invalid data formats, and thread synchronization issues**, making it robust and user-friendly. The compression method is designed to work efficiently with text files but can be extended to handle other file formats with different encoding techniques. The tool provides **real-time feedback** on compression ratios, processing time, and the number of threads used, making it a valuable utility for users handling large data files.   

This project demonstrates key concepts in **multithreading, concurrency control, and file handling**, making it an excellent learning experience for C++ programmers interested in **high-performance computing**. Future enhancements could include **support for advanced compression algorithms like Huffman coding or Lempel-Ziv-Welch (LZW), a graphical user interface (GUI), and cloud-based file processing**. This project serves as a **resume-worthy implementation** of **parallel processing** and **efficient file management**, highlighting the advantages of **multithreading in system-level programming**. By optimizing file compression speed while maintaining data accuracy, this C++ application showcases the power of **concurrent computing** in real-world applications.

OUTPUT:
