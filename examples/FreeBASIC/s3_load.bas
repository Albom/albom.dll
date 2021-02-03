
#Include Once "albom_lib.bi"

Sub load(fileName As String)
	
	Dim s As seans3_data
	Dim As Integer file 

	seans3_load(fileName, @s)

	Print s.day1, s.month1, s.year1
	Print s.hour1, s.minute1, s.second1

	Print s.nR, s.nP, s.Freq


	file = FreeFile()
	Open fileName+".csv" For Output As #file
	
	For i As Integer = 0 To s.nP-1
		Print #file, i*30.555, "; ", s.Dat1[i+s.nP*30]
	Next
	
	Close #file
	

	seans3_close(@s)

End Sub

load("d:/NDA-100/22092014_16_30_07.dat")
Print
load("d:/PPA-25/22092014_16_30_59.dat")

Print
Print "OK"
break
