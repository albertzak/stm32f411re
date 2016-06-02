int i;

int main() {

	// Step 1:
	// Enable Clock for GPIO A via Reset & Clock Control (RCC)
	// GPIO A is part of Advanced Hyper Bus 1 (AHB)
	// Turn on AHB1 via AHB1ENR (Enable Register)
	// Address of RCC is 0x40023800
	// Address offset of GPIOA is 0x30
	// Bit 0 of AHB1ENR = 1 enables clock on GPIOA

	*((unsigned long *)0x40023830) |= (1<<0);

	// Step 2:
	// Set Pin5 of GPIOA as output
	// All pins are inputs by default
	// to avoid bus collisions when powering up
	// Set GPIO Mode Register for port A Pin 5,
  // which is at Bit 11 and Bit 10to 01 (Output)
	// Bit 11 is 0 by default, so it's enough to modify Bit 10

	*((unsigned long *)0x40020000) |= (1<<10);

	// Step 2.5:
	// GPIO State is "Push-Pull" by default
	// Output speed doesn't matter either
	// No need to change anyhting here

	// Step 3:
	// Write "1" to output data register GPIOA_ODR Bit 5 to 1
	// Or use Bit Set/Reset Register (which are read-only!)
	*((unsigned long *)0x40020018) = (1<<5);


	// Keep uC running indefinitely
	while(1) {
		// Sleep
		for(i = 0; i < 500000; i++);

		// XOR Output Data Register with 1,
		// this toggles the LED
		*((unsigned long *)0x40020014) ^= (1<<5);
	}

}
