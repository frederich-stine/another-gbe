INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld h, $01
	ld l, $50
Loop:
	ld a, [hl]
	ld b, [hl]
	ld c, [hl]
	ld d, [hl]
	ld e, [hl]
	ld h, [hl]
	jp Loop
