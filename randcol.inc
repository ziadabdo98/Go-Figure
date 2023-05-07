.386

.DATA
align 4
randomcol_32 label dword
dd 0ffff879Eh  ; any seed except 0

.CODE
setrandomcolseed proc

		MOV AH,00H			
		INT 1AH	
		add randomcol_32,EDX
		
		ret
setrandomcolseed endp

randomcol proc

		push edx
		mov eax,[randomcol_32]
		mov edx,0019660Dh
		mul edx
		add eax,3C6EF35Fh
		mov [randomcol_32],eax
		pop edx
		
		ret
randomcol endp