
#Include Once "albom_lib.bi"

Dim s As seansIV_data

seansIV_load("d:/2017-12-26_09-33-00.iv", @s)

Print s.ver
Print s.date1
Print s.nR, s.nP, s.dT

Dim As Integer sum = 0
For i As Integer = 0 To s.nR-1
	sum += s.scans[i].type1 + (i Mod 7)=0
Next
If sum <> 0 Then
	Print sum
EndIf

Dim As Integer file
For k As Integer = 0 To 6
	file = FreeFile()
	Open "out"+ Str(k) +".csv" For Output As #file
	For i As Integer = 0 To s.nP/2
		Print #file,	i*8; "; "; s.scans[k].data1[i]
	Next
	Close #file
Next


Print
Print "OK"
break
