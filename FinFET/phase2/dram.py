#!/usr/bin/python

import subprocess

filein = open("dram.sp", "r")

Ctimes = 11
Wtimes = 2
rtl = [[0 for h in range(11)] for k in range(2)]
iavg = [[0 for h in range(11)] for k in range(2)]
pavg = [[0 for h in range(11)] for k in range(2)]

for i in range(Wtimes):
    w = 4 * i + 1
    for j in range(Ctimes):
        data = ""
        C = 50000**(j / 10.0)
        C = round(C, 4)

        for line in filein:
            if(line.find("LoadCap") == 7):
                line = ".param LoadCap = " + str(C) + "f\n"
            if(line.find("numfin") == 7):
                line = ".param numfin = " + str(w) + "\n"
            data += line

        filename = "dram_" + str(w) + "_" + str(j + 1) + ".sp"
        fileout = open(filename, "w")
        fileout.write(data)
        fileout.close()

        subprocess.call(["hspice", filename])
        filein2 = open("dram_" + str(w) + "_" + str(j + 1) + ".mt0", "r")

        index = 0 
        for line2 in filein2:
            index += 1
            if (index == 5):
                words = line2.split()
                break

        rtl[i][j] = words[0]
        iavg[i][j] = words[1]
        pavg[i][j] = words[2]

        filein2.close()
        filein.seek(0, 0)

fileout2 = open("dram.txt", "w")

for row in range(2):
    for col in range(11):
        fileout2.write(rtl[row][col])
        fileout2.write(" ")
    fileout2.write("\n")
fileout2.write("\n")

for row in range(2):
    for col in range(11):
        fileout2.write(iavg[row][col])
        fileout2.write(" ")
    fileout2.write("\n")
fileout2.write("\n")

for row in range(2):
    for col in range(11):
        fileout2.write(pavg[row][col])
        fileout2.write(" ")
    fileout2.write("\n")

fileout2.close()
filein.close()