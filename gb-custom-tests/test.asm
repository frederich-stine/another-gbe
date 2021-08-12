INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld b, 1
	ld c, 2
	ld d, 3
	ld e, 4
	ld h, 5
	ld l, 6
Loop:
	add a, b
	sub a, c
	add a, d
	sub a, e
	add a, h
	sub a, l
	jp Loop

