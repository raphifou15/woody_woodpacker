#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>

static int  get_file_size(int fd){
  struct stat  _info;
  fstat(fd, &_info);
  return(_info.st_size);
}

int elfi_open_and_map(char *fname, void **data, int *len){
  int size;
  int fd;
  if (!(fd = open(fname, O_APPEND | O_RDWR, 0))){
    perror("open");
    exit(1);
  }
  size = get_file_size(fd);
  if ((*data = mmap(0, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0)) == MAP_FAILED){
    perror("mmap:");
    exit(1);
  }
  printf("+ File mapped (%d bytes ) at %p\n", size, data);
  *len = size;
  return(fd);
}

int main(int argc, char *argv[]){
  void        *d;
  void        *d1;
  int         target_fd;
  int         payload_fd;
  int         fsize;
  int         fsize1;
  Elf64_Ehdr* elf_hdr;
  Elf64_Addr  ep;
  
  printf("Segment Padding Infector for 0x00 pico \n\n");
  if (argc != 3){
    fprintf(stderr, "Usage:\n %s elf_file payload\n", argv[0]);
    exit(1);
  }
  target_fd = elfi_open_and_map(argv[1], &d, &fsize);
  payload_fd = elfi_open_and_map(argv[2], &d1, &fsize1);
  (void)target_fd;
  (void)payload_fd;
  elf_hdr = (Elf64_Ehdr *) d;
  ep = elf_hdr->e_entry;
  printf("+ Target Entry point: %p\n", (void *) ep);
  return(0);
}
