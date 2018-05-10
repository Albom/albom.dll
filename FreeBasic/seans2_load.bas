
#Include Once "albom_lib.bi"


Dim s As seans2_data
seans2_load("d:/S210317.001", @s)

Dim tau As Integer 

tau = 0

For h As Integer = 0 To 679
	For tau = 0 To 18
	Print s.dat1(h, tau); " ";
	Next
	print
Next

Print
Print "OK"
break
