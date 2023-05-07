
DELETE MACRO POSX,POSY, COLOR
		local loop1,loop2
		
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,1
		mov di,ax						;now di contains the starting x postion from posx
		mov bp,di
		add bp,158						;now bp has ending x position of square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,41						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion from posx
		mov bx,dx
		add bx,78						;now bx has ending y position of square
		
		
		MOV AL,[color]					;color of player 2 is red
		MOV AH,0CH						;interrupt condition		
		
		loop1:
			MOV CX,di
			
			loop2:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,bp
			JNZ loop2
			INC DX
			CMP DX,BX
		JNZ loop1
		
ENDM DELETE

SQUARE MACRO POSX,POSY, COLOR
		local loop1,loop2
		
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,10
		mov di,ax						;now di contains the starting x postion from posx
		mov bp,di
		add bp,140						;now bp has ending x position of square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion from posx
		mov bx,dx
		add bx,70						;now bx has ending y position of square
		
		
		MOV AL,[color]					;color of player 2 is red
		MOV AH,0CH						;interrupt condition		
		
		loop1:
			MOV CX,di
			
			loop2:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,bp
			JNZ loop2
			INC DX
			CMP DX,BX
		JNZ loop1
		
ENDM SQUARE
;=============================================================;
TRIANGLE MACRO POSX,POSY, COLOR
		local loop1,loop2
		
	
		xor ah,ah
		mov al,xpos
		mov cl,160
		mul cl
		add ax,80
		mov bp,ax
		add bp,80						;now bp has ending x position of cell
		mov di,ax						;now di contains the x postion of top of triangle
		
		xor ah,ah
		mov al,ypos
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion postion of top of triangle
		mov bx,dx
		add bx,70						;now bx has ending y position of triangle

		
		MOV AH,0CH						;draw pixel int condition
		MOV AL,color					;using the color in al
		
		MOV CX,di						;start drawing from di
		mov si,cx			
		loop1:			
			
			loop2:			
				INT 10H			
				INC CX			
				CMP CX,si					
			Jbe loop2
			
			inc si
			mov cx,di
			sub cx,si
			add cx,di
			
			
			INC DX
			CMP DX,bx
		JNZ loop1
		
ENDM TRIANGLE
;=============================================================;
PARALLELOGRAM MACRO POSX,POSY, COLOR
		local loop1,loop2
		
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		mov bp,ax
		add bp,80						;now bp has ending x position of cell
		add ax,120
		mov di,ax						;now di contains the x postion of top of triangle
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion postion of top of triangle
		mov bx,dx
		add bx,70						;now bx has ending y position of triangle
		
		MOV AH,0CH						;draw pixel int condition
		MOV AL,[color]					;using the color in al
		
		MOV CX,di						;start drawing from di
		mov si,cx			
		loop1:			
			
			loop2:			
				INT 10H			
				INC CX			
				CMP CX,si					
			Jbe loop2
			
			inc si
			
			sub cx,110
			INC DX
			push si
			push cx
			
			qloop2:			
				INT 10H			
				INC CX			
				CMP CX,si					
			Jbe qloop2
				
			INC DX
			pop cx
			pop si
			CMP DX,bx
		JNZ loop1
		
ENDM PARALLELOGRAM
;=============================================================;
ARROW MACRO POSX,POSY, COLOR	
		local loop1,loop2,loop3,loop4,loop5,loop6,loop7,loop8
		
		
		square POSX,POSY,COLOR			;start by drawing rectangle, then draw black shapes on it
		
		
		;-------this is responsible for cutting top left rectangle from square-------;
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,10
		mov di,ax						;now di contains the starting x postion from posx
		mov bp,di
		add bp,93						;now bp has ending x position of square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion from posx
		mov bx,dx
		add bx,23						;now bx has ending y position of square
		
		
		MOV AL,0						;color of player 2 is red
		MOV AH,0CH						;interrupt condition		
		
		loop1:
			MOV CX,di
			
			loop2:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,bp
			JNZ loop2
			INC DX
			CMP DX,BX
		JNZ loop1
		; ;-------this is responsible for cutting top left rectangle from square-------;
		
		
		
		; ;-------this is responsible for cutting bottom left rectangle from square-------;
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,10
		mov di,ax						;now di contains the starting x postion from posx
		mov bp,di
		add bp,93						;now bp has ending x position of square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,92						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion from posx
		mov bx,dx
		add bx,23						;now bx has ending y position of square
		
		
		MOV AL,0						;color of player 2 is red
		MOV AH,0CH						;interrupt condition		
		
		loop3:
			MOV CX,di
			
			loop4:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,bp
			JNZ loop4
			INC DX
			CMP DX,BX
		JNZ loop3
		;-------this is responsible for cutting bottom left rectangle from square-------;
		
		
		
		;-------this is responsible for cutting top right triangle from square-------;		
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,80
		mov bp,ax
		add bp,70						;now bp has ending x position of cell
		mov di,ax						;now di contains the x postion of top of triangle
		add di,23
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion postion of top of triangle
		mov bx,dx
		add bx,70						;now bx has ending y position of triangle
		
		
		MOV AH,0CH						;draw pixel int condition
		MOV AL,0						;using the color in al
		
		MOV CX,di						;start drawing from di
		loop5:			
			mov si,cx			
			
			loop6:			
				INT 10H			
				INC CX			
				CMP CX,bp					
			Jbe loop6
			inc si
			mov cx,si
			INC DX
			CMP si,bp
		Jb loop5
		;-------this is responsible for cutting top right triangle from square-------;		
		
		
		
		;-------this is responsible for cutting bottom right triangle from square-------;		
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,80
		mov bp,ax
		add bp,70						;now bp has ending x position of square
		mov di,ax						;now di contains the x postion of top of triangle
		add di,23
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion postion of top of triangle
		mov bx,dx
		add bx,70						;now bx has ending y position of triangle
		mov dx,bx						;dx is end y
		
		
		MOV AH,0CH						;draw pixel int condition
		MOV AL,0						;using the color in al
		
		MOV CX,di						;start drawing from di
		loop7:			
			mov si,cx			
			
			loop8:			
				INT 10H			
				INC CX			
				CMP CX,bp					
			Jbe loop8
			inc si
			mov cx,si
			dec DX
			CMP si,bp
		Jb loop7
		;-------this is responsible for cutting bottom right triangle from square-------;		
		
ENDM ARROW

HEXAGON MACRO POSX,POSY, COLOR
		local loop1,loop2,loop3,loop4,loop5,loop6,loop7,loop8
		
		square POSX,POSY,COLOR			;start by drawing rectangle, then draw black shapes on it
		
		;-------this is responsible for cutting top right triangle from square-------;		
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,80
		mov bp,ax
		add bp,70						;now bp has ending x position of cell
		mov di,ax						;now di contains the x postion of top of triangle
		add di,23
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion postion of top of triangle
		mov bx,dx
		add bx,70						;now bx has ending y position of triangle
		
		
		MOV AH,0CH						;draw pixel int condition
		MOV AL,0						;using the color in al
		
		MOV CX,di						;start drawing from di
		loop1:			
			mov si,cx			
			
			loop2:			
				INT 10H			
				INC CX			
				CMP CX,bp					
			Jb loop2
			inc si
			mov cx,si
			INC DX
			CMP si,bp
		Jb loop1
		;-------this is responsible for cutting top right triangle from square-------;		
		
		
		
		;-------this is responsible for cutting bottom right triangle from square-------;		
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,80
		mov bp,ax
		add bp,70						;now bp has ending x position of square
		mov di,ax						;now di contains the x postion of top of triangle
		add di,23
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion postion of top of triangle
		mov bx,dx
		add bx,70						;now bx has ending y position of triangle
		mov dx,bx						;dx is end y
		
		
		MOV AH,0CH						;draw pixel int condition
		MOV AL,0						;using the color in al
		
		MOV CX,di						;start drawing from di
		loop3:			
			mov si,cx			
			
			loop4:			
				INT 10H			
				INC CX			
				CMP CX,bp					
			Jb loop4
			inc si
			mov cx,si
			dec DX
			CMP si,bp
		Jb loop3
		;-------this is responsible for cutting bottom right triangle from square-------;	
		
		
		
		;-------this is responsible for cutting top left triangle from square-------;		
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,10
		mov di,ax						;now di contains the starting x postion from posx
		mov bp,di
		add bp,46						;now bp has ending x position of one third the square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion from posx
		mov bx,dx
		add bx,70						;now bx has ending y position of square
		
		
		MOV AH,0CH						;draw pixel int condition
		MOV AL,0						;using the color in al
		
		MOV CX,di						;start drawing from di
		mov si,bp			
		loop5:			
			
			loop6:			
				INT 10H			
				INC CX			
				CMP CX,si					
			Jb loop6
			dec si
			mov cx,di
			inc DX
			CMP si,di
		Ja loop5
		;-------this is responsible for cutting top left triangle from square-------;		
		
		
		
		;-------this is responsible for cutting bottom left triangle from square-------;				
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,10
		mov di,ax						;now di contains the starting x postion from posx
		mov bp,di
		add bp,46						;now bp has ending x position of square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion from posx
		mov bx,dx
		add bx,70						;now bx has ending y position of square
		mov dx,bx
		
		MOV AH,0CH						;draw pixel int condition
		MOV AL,0						;using the color in al
		
		MOV CX,di						;start drawing from di
		mov si,bp			
		loop7:			
			
			loop8:			
				INT 10H			
				INC CX			
				CMP CX,si					
			Jb loop8
			dec si
			mov cx,di
			dec DX
			CMP si,di
		Ja loop7
		;-------this is responsible for cutting bottom left triangle from square-------;				
		
ENDM HEXAGON

CROSS MACRO POSX,POSY, COLOR
		local loop1,loop2,loop3,loop4,loop5,loop6,loop7,loop8,
		
		square POSX,POSY,COLOR			;start by drawing rectangle, then draw black shapes on it
		
		
		;-------this is responsible for cutting top left square from square-------;	
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,10
		mov di,ax						;now di contains the starting x postion from posx
		mov bp,di
		add bp,46						;now bp has ending x position of square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion from posx
		mov bx,ax
		add bx,23						;now bx has ending y position of square
		
		
		MOV AL,0						;color of player 2 is red
		MOV AH,0CH						;interrupt condition		
		
		loop1:
			MOV CX,di
			
			loop2:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,bp
			JNZ loop2
			INC DX
			CMP DX,BX
		JNZ loop1
		;-------this is responsible for cutting top left square from square-------;	


		
		;-------this is responsible for cutting top right square from square-------;	
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,10	
		mov di,ax						
		mov bp,ax
		add di,93						;now di is at two thirds of the square
		add bp,140						;now bp has ending x position of square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						;now dx contains the starting y postion from posx
		mov bx,ax
		add bx,23						;now bx has ending y position of square
		
		
		MOV AL,0						;color of player 2 is red
		MOV AH,0CH						;interrupt condition		
		
		loop3:
			MOV CX,di
			
			loop4:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,bp
			JNZ loop4
			INC DX
			CMP DX,BX
		JNZ loop3
		;-------this is responsible for cutting top right square from square-------;	

		
		
		;-------this is responsible for cutting bottom left square from square-------;	
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,10	
		mov di,ax						
		mov bp,ax
		add bp,46						;now bp has ending x position of square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						
		add dx,46						;now dx contains the starting y postion from posx
		mov bx,ax
		add bx,70						;now bx has ending y position of square
		
		
		MOV AL,0						;color of player 2 is red
		MOV AH,0CH						;interrupt condition		
		
		loop5:
			MOV CX,di
			
			loop6:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,bp
			JNZ loop6
			INC DX
			CMP DX,BX
		JNZ loop5
		;-------this is responsible for cutting bottom left square from square-------;	


		
		;-------this is responsible for cutting bottom right square from square-------;	
		xor ah,ah
		mov al,[posx]
		mov cl,160
		mul cl
		add ax,10	
		mov di,ax						
		mov bp,ax
		add di,93						;now di is at two thirds of the square
		add bp,140						;now bp has ending x position of square
		
		xor ah,ah
		mov al,[posy]
		mov cl,80
		mul cl
		add ax,45						;40 is the vertical offset, 5 is space for drawing
		mov dx,ax						
		add dx,46						;now dx contains the starting y postion from posx
		mov bx,ax
		add bx,70						;now bx has ending y position of square
		
		
		MOV AL,0						;color of player 2 is red
		MOV AH,0CH						;interrupt condition		
		
		loop7:
			MOV CX,di
			
			loop8:
				push bx
				mov bh,0
				INT 10H
				pop bx
				INC CX
				CMP CX,bp
			JNZ loop8
			INC DX
			CMP DX,BX
		JNZ loop7
		;-------this is responsible for cutting bottom right square from square-------;	

ENDM CROSS
