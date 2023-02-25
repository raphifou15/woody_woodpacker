#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int get_file_size(int fd){
    struct stat _info;
    fstat(fd, &_info);
    return (_info.st_size);
}

int elfi_open_and_map(char *fname, void **data, int *len){
    int size = 0;
    int fd = 0;
    
    if ((fd = open(fname, O_APPEND | O_RDWR, 0)) < 0)
        return (fd);
    size = get_file_size(fd);
    if ((*data = mmap(0, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0)) == MAP_FAILED){
        close(fd);
        return (-1);
    }
    printf("File mapped (%d bytes) at %p\n", size, data);
    *len = size;
    return (fd);
}

int main(int argc, char **argv){
    void        *d = NULL;
    void        *d1 = NULL;
    int         target_fd = 0;
    int         payload_fd = 0;
    int         fsize = 0;
    int         fsize1 = 0;
    // Elf64_Phdr  *t_text_seg;
    printf("Segment Padding infector\n");

    if (argc != 3){
        fprintf(stderr, "usage:\n %s elf_file payload\n", argv[0]);
        return(1);
    }
    if ((target_fd = elfi_open_and_map(argv[1], &d, &fsize)) < 0)
        return(1);
    if ((payload_fd = elfi_open_and_map(argv[2], &d1, &fsize1)) < 0){
        close(target_fd);
        munmap(d, fsize);
        return(1);
    }

    munmap(d, fsize);
    munmap(d1, fsize1);
    close(target_fd);
    close(payload_fd);
    return(0);
}