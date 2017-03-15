
#Include Once "albom_lib.bi"

for f as Double = 0 To 5000 Step 200
	Print spectrum_3_full(1, 4, 16, 0, 0, 1000, 1000, 1, 0, f)
Next


Print
Print "OK"
break
