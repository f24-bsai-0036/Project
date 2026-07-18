.model small
.stack 100h
.data
menus db 13,10,'---=== DIGIT BANK ===---',13,10
      db '1. Create Account (ID: 1-3)',13,10
      db '2. Deposit Money',13,10
      db '3. Withdraw Money',13,10
      db '4. Check Balance',13,10
      db '5. Exit Program',13,10
      db 'Enter choice: $'
msgCreate      db 13,10,'Account created successfully!$'
msgExist       db 13,10,'Account ID already exists!$'
msgAskID       db 13,10,'Enter Account ID (1-3): $'
msgAskAmt      db 13,10,'Enter Amount (00-99): $'
msgBal         db 13,10,'Current Balance: $'
msgInvalid     db 13,10,'Invalid Input!$'
msgNoFunds     db 13,10,'Insufficient Balance!$'
msgDepSuccess  db 13,10,'Deposit successful!$'
msgWithSuccess db 13,10,'Withdrawal successful!$'
accounts db 3 dup(0)  
accFlag  db 3 dup(0)  
.code
main proc
    mov AX, @data
    mov DS, AX
Menu:
    mov DX, offset menus
    mov AH, 09h
    int 21h
    mov AH, 01h
    int 21h
    sub AL, 30h      
    cmp AL, 1
    je CreateAccount
    cmp AL, 2
    je Deposit
    cmp AL, 3
    je Withdraw
    cmp AL, 4
    je CheckBalance
    cmp AL, 5
    je ExitProgram
    mov DX, offset msgInvalid
    mov AH, 09h
    int 21h
    jmp Menu
CreateAccount:
    call GetAccountID
    jc Menu             
    mov BL, AL
    mov BH, 0           
    mov AL, accFlag [BX]
    cmp AL, 1
    je AlreadyExists
    mov accFlag [BX], 1
    mov accounts [BX], 0
    mov DX, offset msgCreate
    mov AH, 09h
    int 21h
    jmp Menu
AlreadyExists:
    mov DX, offset msgExist
    mov AH, 09h
    int 21h
    jmp Menu
Deposit:
    call GetAccountID
    jc Menu
    mov BL, AL
    mov BH, 0
    cmp accFlag [BX], 1
    jne NotExists    
    call GetAmountTwoDigits 
    add accounts [BX], AL 
    mov DX, offset msgDepSuccess
    mov AH, 09h
    int 21h
    jmp Menu
Withdraw:
    call GetAccountID
    jc Menu
    mov BL, AL
    mov BH, 0
    cmp accFlag [BX], 1
    jne NotExists
    call GetAmountTwoDigits
    mov CL, AL
    mov AL, accounts [BX]
    cmp AL, CL
    jb NoFunds
    sub accounts [BX], CL
    mov DX, offset msgWithSuccess
    mov AH, 09h
    int 21h
    jmp Menu
NoFunds:
    mov DX, offset msgNoFunds
    mov AH, 09h
    int 21h
    jmp Menu
CheckBalance:
    call GetAccountID
    jc Menu
    mov BL, AL
    mov BH, 0
    cmp accFlag [BX], 1
    jne NotExists
    mov DX, offset msgBal
    mov AH, 09h
    int 21h
    mov AL, accounts [BX]
    mov AH, 0           
    mov CX, 0           
    mov BX, 10          
PushDigits:
    mov DX, 0           
    div BX              
    push DX             
    inc CX              
    cmp AX, 0           
    jne PushDigits      
PopDigits:
    pop DX              
    add DL, 30h         
    mov AH, 02h         
    int 21h
    loop PopDigits      
    jmp Menu
NotExists:
    mov DX, offset msgInvalid
    mov AH, 09h
    int 21h
    jmp Menu
ExitProgram:
    mov AH, 4Ch
    int 21h
main endp
GetAccountID proc 
    mov DX, offset msgAskID
    mov AH, 09h
    int 21h
    mov AH, 01h
    int 21h
    sub AL, 31h      
    cmp AL, 0
    jb ID_Err
    cmp AL, 2
    ja ID_Err
    clc             
    ret
ID_Err:
    mov DX, offset msgInvalid
    mov AH, 09h
    int 21h
    stc             
    ret
GetAccountID endp
GetAmountTwoDigits proc
    push BX 
    mov DX, offset msgAskAmt
    mov AH, 09h
    int 21h
    mov AH, 01h
    int 21h
    sub AL, 30h
    mov BL, 10
    mul BL         
    mov CX, AX    
    mov AH, 01h
    int 21h
    sub AL, 30h
    mov AH, 0
    add CX, AX     
    mov AX, CX     
    pop BX 
    ret
GetAmountTwoDigits endp
end main