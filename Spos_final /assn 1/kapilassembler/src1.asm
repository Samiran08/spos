	START 200
	MOVER AREG, ="5"
	MOVEM AREG, A
LOOP MOVER AREG, A
	MOVER CREG, B
ADD CREG, ="1"
	LTORG
NEXT1 SUB AREG, ="1"
	ORIGIN LOOP+6
	MULT CREG, B
A DS 2
B DC 1
NEXT2 EQU LOOP
END