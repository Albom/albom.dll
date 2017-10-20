
#Include Once "albom_lib.bi"

Const As Integer L = 8

Dim As Double in0(0 To L-1) => {1, 1, 1, 1, 0, 0, 0, 0}
Dim As Double in1(0 To L-1)

Dim As Double out0(0 To L-1)
Dim As Double out1(0 To L-1)

Dim As Double out0_2(0 To L-1)
Dim As Double out1_2(0 To L-1)


for i as Integer = 0 To L-1
	Print Using "##.### "; in0(i);
Next
Print
for i as Integer = 0 To L-1
	Print Using "##.### "; in1(i);
Next
Print

fourier_FFT_d(@in0(0), @in1(0), @out0(0), @out1(0), L)

Print "FFT"
for i as Integer = 0 To L-1
	Print Using "##.### "; out0(i);
Next
Print
for i as Integer = 0 To L-1
	Print Using "##.### "; out1(i);
Next
Print

Print "IFFT"
fourier_IFFT_d(@out0(0), @out1(0), @out0_2(0), @out1_2(0), L)
for i as Integer = 0 To L-1
	Print Using "##.### "; out0_2(i);
Next
Print
for i as Integer = 0 To L-1
	Print Using "##.### "; out1_2(i);
Next

Print
Print
Print "OK"
break
