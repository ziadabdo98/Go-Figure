;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;credits;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                                                                    ;
;		    1-All the code in the files rand.inc and randcol.inc is taken from                       ;
;		      https://programmersheaven.com/discussion/219366/a-random-number-generator-routine      ;
;                                                                                                    ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



INCLUDE DRAWFIGS.inc								;contains procedures used to draw all the figures
.model small
.stack 64
.386

.data

PLAYERNAME			DB			15,?,15 DUP('$')
MODE				DB			2					;0 for ABOUT, 1 for GAME, 2 for MAIN
GAMETYPE			DB			0					;0 for by color, 1 for by figure
FIGURES				DB			8 DUP(?)			;Array of the figures drawn on the screen, will be chosen at random
figurecount			db			0
SELECTION			DB			0					;What mode is selected in the main menu
XPOS				DB			?					;these are used when passing parameters to macros
YPOS				DB			?                   ;these are used when passing parameters to macros
COLOR				DB			?                   ;these are used when passing parameters to macros
x					dw			?					;x value of mouse clicks
y					dw			?					;y value of mouse clicks
clickedcolor		db			?					;the color of the clicked pixel
clickedfigureindex	db			?					;index of clicked figure in array of figures
clickedfigure		db			?					;enum  of click figure
numcolortoclick		db			?					;the number of figures that match the color requirement
numfiguretoclick	db			?					;the number of figures that match the shape requirement
colortoclick		db			?					;the color which the user is required to click on. Same index as color count list
figuretoclick		db			?					;the figure which the user is required to click on. Same index as figure count list
lives				db			?					;number of lives of the player
startinglives		db			32H					;number of starting lives
timerbuffer			dw			0					;used in animating the timer bar
timerpos			dw			479					;the x position where the timer ends at
TIMERBUFFERLIMIT	DW			1FFH				;increasing this decreases speed of timer

;--------------------------------------color count------------------------------------;
BLUECOUNT			DB			0			;1
GREENCOUNT			DB			0           ;2
CYANCOUNT			DB			0           ;3
REDCOUNT			DB			0           ;4
PINKCOUNT			DB			0           ;5
BROWNCOUNT			DB			0			;6
;--------------------------------------color count------------------------------------;

;--------------------------------------colors------------------------------------;
BLUECOLOR			DB			'BLUE$'
GREENCOLOR			DB			'GREEN$'
CYANCOLOR			DB			'CYAN$'
REDCOLOR			DB			'RED$'
PINKCOLOR			DB			'PINK$'
BROWNCOLOR			DB			'BROWN$'
;--------------------------------------colors------------------------------------;

;--------------------------------------figure count-----------------------------------;
SQUARECOUNT			DB			0			;0
TRIANGLECOUNT		DB			0           ;1
PARALLELOGRAMCOUNT	DB			0           ;2
ARROWCOUNT			DB			0           ;3
HEXAGONCOUNT		DB			0           ;4
CROSSCOUNT			DB			0           ;5
;--------------------------------------figure count-----------------------------------;

;--------------------------------------figures-----------------------------------;
SQUAREfig			DB			'SQUARE$'
TRIANGLEfig			DB			'TRIANGLE$'
PARALLELOGRAMfig	DB			'PARALLELOGRAM$'
ARROWfig			DB			'ARROW$'
HEXAGONfig			DB			'HEXAGON$'
CROSSfig			DB			'CROSS$'
;--------------------------------------figures-----------------------------------;

;---------------------------------------GAME------------------------------------------;
PAUSED				DB			'Game is paused, ESC to quit to main menu, SPACE to continue$'
GAMETYPESTR			DB			'Select game mode...$'
TYPECOLOR			DB			'1 - By color$'
TYPEFIGURE			DB			'2 - By shape$'
instructions		DB			'Press 1,2 to select, Press ESC to quit to main menu$'
FIGURESSTR			DB			'FIGURE$'
LIVESSTR			DB			"'s Lives: $"
LOSTMESSAGE0		DB			'SORRY $'
LOSTMESSAGE1		DB			'LOOKS LIKE YOU LOST :($'
LOSTMESSAGE2		DB			"BUT YOU CAN ALWAYS TRY AGAIN ;)$"
LOSTMESSAGE3		DB			'PRESS ESC TO QUIT GAME, PRESS SPACE TO GO TO MAIN MENU$'
WONMESSAGE0			DB			'CONGRATULATIONS $'
WONMESSAGE1			DB			'YOU WON!!!!!!$'
WONMESSAGE2			DB			'HOPE YOU ENJOYED THE GAME $'
ESCTOPAUSE			DB			'Press ESC to pause game$'
TUTORIALSTR			DB			'TUTORIAL$'
TUTORIALSTR0		DB			1AH,'CLICK ON THE REQUIRED FIGURE BEFORE THE TIMER RUNS OUT$'
TUTORIALSTR1		DB			1AH,'EACH TIIME YOU CLICK ON THE WRONG FIGURE YOU LOSE ONE LIFE$'
TUTORIALSTR2		DB			1AH,'IF YOUR LIFE COUNT REACHES ZERO YOU LOSE$'
TUTORIALSTR3		DB			'CLICK ANYWHERE WITH THE MOUSE WHEN READY!!!$'
TIMIERSTR0			DB			'CHOOSE THE TIMER SPEED$'
TIMIERSTR1			DB			'1 - RELAXED SPEED    2 - MEDIUM SPEED    3 - FAST SPEED    4 - INSANE SPEED!!!$'
TIMIERSTR2			DB			'Press 1,2,3,4 to select, Press ESC to quit to main menu$'
;---------------------------------------GAME------------------------------------------;

;---------------------------------------MENU------------------------------------------;
ENTERNAME			DB			'Enter your name:$'
PRESSENTER			DB			'Press Enter key to continue$'
MAINSCREEN1			DB			'More about Go Figure$'
MAINSCREEN2			DB			'Play GO FIGURE!!$'
MAINSCREEN3			DB			"Exit Go Figure :($"
HI					DB			'Hi $'
WELCOMEMESSAGE		DB			'Welcome to GO FIGURE, use Up/Down arrows to move, Enter to select!!!$'
CLICKMESSAGE		DB			'Click on a$'
;---------------------------------------MENU------------------------------------------;

;---------------------------------------ABOUT------------------------------------------;
ABOUT			DB				'    GO FIGURE is a game designed to teach kids shapes and colors, with a fun',10,13,' twist to it.',10,10,10,13
				DB				'    The game displays 8 random figures on the screen each of them having a',10,13,' random color, '
				DB				'The player is then asked to click on a figure with a specific',10,13,' property that the player chooses before game.',10,10,10,13
				DB				"    It could be either by color or by shape. But don't let the simplicity fool",10,13," you, as you are racing against a clock timer.",10,10,10,10,13
				DB				'                       Thank you for playing Go Figure ',01,'$'
ABOUTIN			DB				'PRESS ANY KEY TO GO TO MAIN MENU$'
;---------------------------------------AVOUT------------------------------------------;

;---------------------------------------PHOTO-----------------------------------------;
FILENAMEINTRO 		DB 			'pong.bmp',0
FILENAMEOUTTRO 		DB 			'outro.bmp',0
FILEHANDLE 			DW 			?
HEADER 				DB 			54 DUP (0)
PALETTE 			DB 			256*4 DUP (0)
SCRLINE 			DB 			320 DUP (0)
ERRORMSG 			DB 			'Error', 13, 10,'$'
;---------------------------------------PHOTO-----------------------------------------;

;---------------------------------------SOUND-----------------------------------------;
PIT 				DB 			43H
PIT2 				DB 			42H
DELAYSOUND 			DW 			25					;Delay for sample rate - if song sounds too slow or too fast, change this
FILENAMESOUND 		DB 			"p.wav", 0 			;Raw headerless mono 8-bit 44100hz wave file -
FILEHANDLESOUNDS	   			DW 0
COUNTER 			DW 			0FFFFH
ERRORMSGSOUNDS 		DB 			"Error.$"
BUFFER				DB 			0
;---------------------------------------SOUND-----------------------------------------;


INCLUDE GUI.inc										;contains procedures used to draw everything
; INCLUDE IMAGE.inc									;contains procedures used to draw images
; INCLUDE SOUND.inc									;contains procedures used to play sound
INCLUDE INPUT.inc									;contains procedures used to get inputs
INCLUDE rand.inc									;contains procedures used to randomize figures
INCLUDE randcol.inc									;contains procedures used to randomize colors

main proc
		mov ax,@data
		mov ds,ax
		
		call intro
		
		WHILE:			
		CALL USERINPUT							;CHANGES MEMORY VALUES AND REGISTERS ACCORDING TO USER INPUT
		CALL UPDATEGUI							;UPDATES GUI USING VALUES FROM THE MEMORY THAT CHANGED FROM THE USERINPUT PROCEDURES
		JMP WHILE
		
		mov ax,4c00h
		int 21h
		ret
main endp


UPDATEGUI PROC				;checks mode and calls appropriate proc
		
		CMP mode,0H
		jz TOABOUT
		
		CMP mode,01H
		jz GAME
		
		CMP mode,02H
		jz MAINSCREENUI
		
	TOABOUT:
		CALL ABOUTGUI
		RET
		
	GAME:	
		CALL GAMEGUI
		ret
		
	MAINSCREENUI:
		CALL MENUGUI
		RET
		
UPDATEGUI endp
	
USERINPUT PROC				;checks mode and calls appropriate proc
		
		CMP mode,0H
		jz ABOUTINP
		
		CMP mode,01H
		jz gamemodeinput
		
		CMP mode,02H
		jz mainmenuinput
		
	ABOUTINP:
		CALL ABOUTINPUT
		ret
		
	gamemodeinput:
		call gameinput
		ret
		
	mainmenuinput:
		CALL menuinput
		ret
		
USERINPUT ENDP


end main