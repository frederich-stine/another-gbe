INCLUDE "hardware.inc"

SECTION "Header", ROM0[$100]

	jp EntryPoint

	ds $150 - @, 0 ; Make room for the header

EntryPoint:
	ld a, $00
	ld b, $00
	ld c, $10
FunA:
	call FunB
	jp Done
FunB:
	dec c
	call nz, FunC
	cp c
	jp nz, FunB
FunC:
	inc b
	ret
Done:
	jp Done
