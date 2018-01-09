
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
file = FreeFile()
Open "out.csv" For Output As #file
For i As Integer = 0 To s.nP/4
	Print #file,	s.scans[0].data1[i], ";", s.scans[1].data1[i],  ";", s.scans[2].data1[i], ";", _ 
						s.scans[3].data1[i], ";", s.scans[4].data1[i],  ";", s.scans[5].data1[i], ";", _
						s.scans[6].data1[i]  
Next
Close #file
	

Print
Print "OK"
break
