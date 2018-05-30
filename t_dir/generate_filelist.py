import itertools
import os
import glob
import shutil

for x in range(100):
    dirname = 'batch%d' % x
    os.mkdir(dirname)
    for j in range(100):
        filename = "file%03d.txt" % j
        open(filename, "w").write("some text")
        shutil.move(filename, dirname)
    
