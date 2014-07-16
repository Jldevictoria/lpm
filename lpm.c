/* 
 * Lightweight Pcimem Library
 * Made by Joseph DeVictoria (2014)
 * Based off pcimem by Bill Farrow
 * License: GNU General Public License V2
 */

#include "lpm.h"

void pci_card_init(struct pci_card *card){
	card->fd = open(card->filename, O_RDWR | O_SYNC);
	card->map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, card->fd, card->target & ~MAP_MASK);
	card->virt_addr = card->map_base + (card->target & MAP_MASK);
	return;
}

unsigned pci_card_read(char* fname, char* raddr){
	struct pci_card fusion;
	fusion.filename = fname;
	fusion.target = strtoul(raddr, 0, 0);
	pci_card_init(&fusion);
	fusion.read_result = *((unsigned *) fusion.virt_addr);
	return fusion.read_result;
}

void pci_card_write(char* fname, char* raddr, unsigned wval){
	struct pci_card fusion;
	fusion.filename = fname;
	fusion.target = strtoul(raddr, 0, 0);
	pci_card_init(&fusion);
	*((unsigned *) fusion.virt_addr) = wval;
	return;
}
