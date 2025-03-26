#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define FILE_SIZE 4096 // Define the size of the shared memory region

int main()
{
    // Open or create a file named "shared_file.txt" with read/write permissions
    int fd = open("shared_file.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) // Check if the file was opened successfully
    {
        perror("open");
        return 1;
    }

    // Map the file into memory with read/write permissions
    char *mapped_memory = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED) // Check if memory mapping was successful
    {
        perror("mmap");
        close(fd); // Close the file descriptor before exiting
        return 1;
    }

    // Get input from keyboard
    char input[100];
    printf("Enter a message to write to the shared memory: ");
    fgets(input, 100, stdin);

    // Write a message to the shared memory
    strcpy(mapped_memory, input);

    // Print the message written to the shared memory
    printf("Writer wrote: %s", mapped_memory);

    // Unmap the memory and close the file descriptor
    munmap(mapped_memory, FILE_SIZE);
    close(fd);

    return 0; // Exit the program successfully
}
