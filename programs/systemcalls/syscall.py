import webbrowser
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import ListedColormap

f = open("system calls.txt")
s = f.readlines()
s1 = []
f.close()

message = """<html>
<body>"""

part = """ """

for sp in s:
    message += """<hr><p> """
    message += """<p> %s </p>""" %sp
    message +="""<br>"""
    message+= """</font></p>"""
message += """</body></head>"""
f = open('syscall.html', 'w')
f.write(message)
f.close()
filename = 'syscall.html'
webbrowser.open_new_tab(filename)
