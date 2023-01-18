#include "./woodyWoodPacker.h"

void printStats(struct stat *sb){
	printf("ID du périphérique contenant le fichier: %ld\n",sb->st_dev);
	printf("Numéro inœud: %ld\n", sb->st_ino);
	printf("Protection: %d\n", sb->st_mode);
	printf("Nb liens matériels: %ld\n", sb->st_nlink);
	printf("UID propriétaire: %d\n", sb->st_uid);
	printf("GID propriétaire: %d\n", sb->st_gid);
	printf("ID périphérique (si fichier spécial): %ld\n", sb->st_rdev);
	printf("Taille totale en octets: %ld\n", sb->st_size);
	printf("Taille de bloc pour E/S: %ld\n", sb->st_blksize);
	printf("Nombre de blocs alloués: %ld\n", sb->st_blocks);
	printf("Heure dernier accès: %ld\n", sb->st_atime);
	printf("Heure dernière modification: %ld\n", sb->st_mtime);
	printf("Heure dernier changement état: %ld\n", sb->st_ctime);
}

void printFileHexa(char *file, size_t size){
	char	*lala;
	
	lala = (char *)file;
  for (size_t i = 0; i < size; i++)
    printf("%x", lala[i]);
  printf("\n");
}

void printHeader(Elf64_Ehdr  *hdr){
	printf("HEADER\n");
	printf("e_ident: %x\n", hdr->e_ident[0]); // 7f
	printf("e_ident: %x\n", hdr->e_ident[1]); // 'E'
	printf("e_ident: %x\n", hdr->e_ident[2]); // 'L'
	printf("e_ident: %x\n", hdr->e_ident[3]); // 'F'
	printf("e_ident: %d\n", hdr->e_ident[4]); // 2
	printf("e_ident: %d\n", hdr->e_ident[5]);
	printf("e_ident: %d\n", hdr->e_ident[6]);
	printf("e_ident: %d\n", hdr->e_ident[7]);
	printf("e_ident: %d\n", hdr->e_ident[8]);
	printf("e_ident: %d\n", hdr->e_ident[9]);
	printf("e_ident: %d\n", hdr->e_ident[10]);
	printf("e_ident: %d\n", hdr->e_ident[11]);
	printf("e_ident: %d\n", hdr->e_ident[12]);
	printf("e_ident: %d\n", hdr->e_ident[13]);
	printf("e_ident: %d\n", hdr->e_ident[14]);
	printf("e_ident: %d\n", hdr->e_ident[15]);
	printf("taille de e_indent: %d\n", EI_NIDENT);
}
