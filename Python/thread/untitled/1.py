#coding:utf-8

import sys

#http://img2.kanrenti.org/photoL/7316/34.jpg
lastPic = "http://img2.kanrenti.org/photoL/7316/34.jpg"
lastPic = "http://img2.kanrenti.org/photoL/7320/22.jpg"
lastPic = "http://img2.kanrenti.org/photoL/7266/46.jpg"
lastPic = "http://531.1000yishu.com/201606/040/60.jpg"
lastPic = "http://photo.ggba.pw/uploadfile/2015/0409/04/96.jpg"
lastPic = "http://photo.ggba.pw/uploadfile/2015/0507/29/84.jpg"

lastPicSplit = lastPic.split('/')
count = int(lastPicSplit.pop().split('.')[0]) + 1
prefix = '/'.join(lastPicSplit)+'/'
print count
print prefix

filename = "xx4"
filename += ".html"
output = open(filename, "w")

output.write("<html>\n")
output.write("<body>\n")
output.write("<div align=\"center\">\n")

#<img src="http://photo.ggba.pw/uploadfile/2015/0926/35/01.jpg"/>
for i in range(1, count):
    if i < 10:
        curPage = '0' + str(i) + ".jpg\n"
    else:
        curPage = str(i)+".jpg\n"
    output.write("<img src=\""+prefix+curPage+"\"/>")

output.write("</div>\n")
output.write("</body>\n")
output.write("</html>\n")
