#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>
#include <errno.h>
#include <string.h>

int get_file_size(int fd){
    struct stat _info;
    fstat(fd, &_info);
    return (_info.st_size);
}

int elfi_open_and_map(char *fname, void **data, int *len){
    int size = 0;
    int fd = 0;
    
    if ((fd = open(fname, O_APPEND | O_RDWR, 0)) < 0){
        int err = errno;
        printf("fd failed, %s\n", strerror(err));
        return (fd);
    }
    size = get_file_size(fd);
    if ((*data = mmap(0, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0)) == MAP_FAILED){
        close(fd);
        printf("map failed\n");
        return (-1);
    }
    printf("File mapped (%d bytes) at %p\n", size, data);
    *len = size;
    return (fd);
}

Elf64_Phdr *    elfi_find_gap(void *d, int fsize, int *p, int *len){
    Elf64_Ehdr  *elf_hdr = (Elf64_Ehdr *) d;
    Elf64_Phdr  *elf_seg;
    Elf64_Phdr  *text_seg;
    unsigned char *d1 = (char *)d;
    for (unsigned int i = 0; i < fsize; i++){
        printf("%x", d1[i]);
        if ((i > 0) && ((i % 8) == 1))
            printf(" ");
    }
    printf("\n");
    printf("%u\n", (unsigned int)elf_hdr->e_phoff);
    printf("-------------------");
    elf_seg = ((Elf64_Phdr *)((unsigned char *)elf_hdr + (unsigned int)elf_hdr->e_phoff));
    for (int i = 0; i < elf_hdr->e_phnum; i++){
        printf("%d", i);
        printf("  %-14s 0x%06lx 0x%08lx 0x%08lx 0x%06lx 0x%06lx 0x%03x 0x%lx\n",
            (elf_seg->p_type == PT_LOAD) ? "LOAD" :
            (elf_seg->p_type == PT_DYNAMIC) ? "DYNAMIC" :
            (elf_seg->p_type == PT_INTERP) ? "INTERP" :
            (elf_seg->p_type == PT_NOTE) ? "NOTE" :
            (elf_seg->p_type == PT_PHDR) ? "PHDR" :
            (elf_seg->p_type == PT_TLS) ? "TLS" :
            (elf_seg->p_type == PT_GNU_EH_FRAME) ? "GNU_EH_FRAME" :
            (elf_seg->p_type == PT_GNU_STACK) ? "GNU_STACK" :
            (elf_seg->p_type == PT_GNU_RELRO) ? "GNU_RELRO" :
            "UNKNOWN",
            elf_seg->p_offset,
            elf_seg->p_vaddr,
            elf_seg->p_paddr,
            elf_seg->p_filesz,
            elf_seg->p_memsz,
            elf_seg->p_flags,
            elf_seg->p_align);
        elf_seg = (Elf64_Phdr *)((unsigned char*)elf_seg + (unsigned int)elf_hdr->e_phentsize);
    }
    
}

int main(int argc, char **argv){
    void        *d = NULL;
    void        *d1 = NULL;
    int         target_fd = 0;
    int         payload_fd = 0;
    int         fsize = 0;
    int         fsize1 = 0;
    int         p = 0;
    int         len = 0;
    Elf64_Phdr  *t_text_seg;
    printf("Segment Padding infector\n");

    if (argc != 3){
        fprintf(stderr, "usage:\n %s elf_file payload\n", argv[0]);
        return(1);
    }
    if ((target_fd = elfi_open_and_map(argv[1], &d, &fsize)) < 0){
        printf("error1\n");
        return(1);
    }
    if ((payload_fd = elfi_open_and_map(argv[2], &d1, &fsize1)) < 0){
        printf("error2\n");
        close(target_fd);
        munmap(d, fsize);
        return(1);
    }
    t_text_seg = elfi_find_gap(d, fsize, &p, &len);
    munmap(d, fsize);
    munmap(d1, fsize1);
    close(target_fd);
    close(payload_fd);
    return(0);
}