[BITS 32]
	MOV		AL,'A'
	CALL	2*8:0x44c4

fin:
	HLT
	JMP	fin
