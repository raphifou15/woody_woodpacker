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
	size_t	nb;
	size_t	nb2;
	
	(void)size;
	lala = (char *)file;
  for (size_t i = 0; i < 64; i++)
	{
		if (i == 0) printf("Elf64_Ehdr\n 16 byte e_ident: ");
		if (i == 16) printf("2 byte e_type: ");
		if (i == 18) printf("2 byte e_machine: ");
		if (i == 20) printf("4 byte e_version: ");
		if (i == 24) printf("8 byte e_entry: ");
		if (i == 32) printf("8 byte e_phoff: ");
		if (i == 40) printf("8 byte e_shoff: ");
		if (i == 48) printf("4 byte e_flags: ");
		if (i == 52) printf("2 byte e_ehsize: ");
		if (i == 54) printf("2 byte e_phentsize: ");
		if (i == 56) printf("2 byte e_phnum: ");
		if (i == 58) printf("2 byte e_shentsize: ");
		if (i == 60) printf("2 byte e_shnum: ");
		if (i == 62) printf("2 byte e_shstrndx: ");
		if (lala[i] < 16)
			printf("0");
    printf("%x ", lala[i]);
		if (i == 15 || i == 17 || i == 19 || i == 23 || i == 31 || i == 39 ||
				i == 47 || i == 51 || i == 53 || i == 55 || i == 57 || i == 59 ||
				i == 61 || i == 63) printf("\n");
	}
	printf("\n");
	printf("Print section header\n");
	nb = (size_t)file[52];
	nb2 = (size_t)((file[40]*(file[58] + file[60])));
	for (size_t i = nb; i < (size_t)(file[52] + file[54]); i++){
		if (i == nb) printf("4 bytes p_type: ");
		if (i == nb + 4) printf("4 bytes p_flags: ");
		if (i == nb + 8) printf("4 bytes p_offset: ");
		if (i == nb + 16) printf("8 bytes p_vaddr: ");
		if (i == nb + 24) printf("8 bytes p_paddr: ");
		if (i == nb + 32) printf("8 bytes p_filesz: ");
		if (i == nb + 40) printf("8 bytes p_memsz: ");
		if (i == nb + 48) printf("8 bytes p_align: ");
		if (lala[i] < 16) printf("0");
		printf("%x ", file[i]);
		if (i == nb + 3) printf("\n");
		if (i == nb + 7) printf("\n");
		if (i == nb + 15) printf("\n");
		if (i == nb + 23) printf("\n");
		if (i == nb + 31) printf("\n");
		if (i == nb + 39) printf("\n");
		if (i == nb + 47) printf("\n");
		if (i == nb + 55) printf("\n");
	}
	printf("\n");
	for (size_t i = nb2 ; i < nb2 + 64; i++){
		printf("%x ", file[i]);
	}
	printf("\n");
	printf("%ld", nb2);
}
	

void printHeader(Elf64_Ehdr  *hdr){
	printf("HEADER\n");
	printf("e_ident_EI_MAG 7f 45 4c 46 (valid ELF magic)\n");
	printf("e_ident: %x\n", hdr->e_ident[0]); // 7f
	printf("e_ident: %x\n", hdr->e_ident[1]); // 'E'
	printf("e_ident: %x\n", hdr->e_ident[2]); // 'L'
	printf("e_ident: %x\n", hdr->e_ident[3]); // 'F'
	printf("//////////////////////////////\n");
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
