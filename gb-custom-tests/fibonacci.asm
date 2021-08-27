INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld a, $00
	ld b, $01
	ld c, b
	ld hl, $0500
Fibonacci:
	add b
	ld [hl+], a
	ld b, c
	ld c, a
	cp 233
	call nz, Fibonacci
Done:
	jp Done
