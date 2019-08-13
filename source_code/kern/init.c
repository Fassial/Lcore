#include "../arch/arch.h"
#include "../arch/intr.h"
#include "../arch/page.h"
#include "vga/vga.h"
#include "time/time.h"
#include "../tool/tool.h"

void machine_info()
{

}

void init_kernel()
{
	unsigned int pg_end;
	unsigned int *config;

	init_exint();
	// pg_end = init_pgtable();
	// enable_paging(pgd);
	// init_vga((pg_end + 0x0000ffff) & 0xffff0000);
	init_vga(0x00110000);
	machine_info();
	init_time(_CLOCK_INTERVAL);
	enable_intr(_INTR_GLOBAL | _INTR_CLOCK | _INTR_KEYB | _INTR_SPI);
}

