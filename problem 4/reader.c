#include <stdio.h>    // For standard input/output functions
#include <stdlib.h>   // For general utility functions
#include <fcntl.h>    // For file control options (e.g., open)
#include <sys/mman.h> // For memory mapping functions
#include <unistd.h>   // For close function

#define FILE_SIZE 4096 // Define the size of the memory-mapped file

int main()
{
    // Open the file "shared_file.txt" in read-only mode
    int fd = open("shared_file.txt", O_RDONLY);
    if (fd == -1)
    { // Check if the file failed to open
        perror("open");
        return 1;
    }

    // Map the file into memory with read-only permissions
    char *mapped_memory = mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED)
    { // Check if memory mapping failed
        perror("mmap");
        close(fd); // Close the file descriptor before exiting
        return 1;
    }

    // Print the content of the memory-mapped file
    printf("Reader read: %s\n", mapped_memory);

    // Unmap the memory and release resources
    munmap(mapped_memory, FILE_SIZE);
    close(fd); // Close the file descriptor
    return 0;  // Exit the program successfully
}
