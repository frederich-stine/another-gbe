INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld a, $00
	ld b, $FF
	ld c, $00
	ld d, 3
	ld e, 4
	ld h, 5
	ld l, 6
Loop:
	or a, b
	xor a, b
	and a, b
	and a, a
	jp Loop

