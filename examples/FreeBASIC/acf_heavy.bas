
#Include Once "albom_lib.bi"

Dim As Double ti = 400
Dim As Double te = 600

Const As Integer N = 27

Dim As Double acf(0 To N-1)
Dim As Double acf_lib(0 To N-1)

Dim As FILE Ptr file

Dim As Integer temperatures_length
Dim Shared As Integer temperatures(0 To 200000)  

temperatures_length = library_heavy_list_of_temperatures_get(@temperatures(0))

file = fopen("e:/Lib/LibM+/O=010.dat", "rb")

acf_library_heavy(file, @temperatures(0), temperatures_length, ti, te, @acf_lib(0), N)
acf_3_full(16, 30.5, 30.5, 0.1, 0, ti, te, 1, 0, @acf(0), N, 39.285e-6)


for tau as Integer = 0 To N-1
	Print acf(tau), acf_lib(tau), acf(tau)-acf_lib(tau)
Next


Print
Print "OK"
break
