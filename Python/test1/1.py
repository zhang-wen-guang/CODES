#coding:utf-8
import urllib
import urllib2
from HTMLParser import HTMLParser

class MyHTMLParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.links = []
        self.titles = []
 
    def handle_starttag(self, tag, attrs):
        #print "Encountered the beginning of a %s tag" % tag
        if tag == "a":
            if len(attrs) == 0: pass
            else:
                for (variable, value)  in attrs:
                    if variable == "href" and len(value) == 39:
                        self.links.append(value)

class FindLastPage(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)

    def handle_starttag(self, tag, attrs):
        if tag == "div":
            print "attrs"

def HandleUrltoHtml(url):
    file = urllib.urlopen(url)
    return file.read()


#url = "http://photo.gmba.ws"
url = "http://www.gmba.ws/guomoba/guomosipai/"
path = "01.txt"  
#urllib.urlretrieve("http://photo.gmba.ws/uploadfile/2016/0112/03/01.jpg", '01.jpg')

page = urllib.urlopen(url)
html = page.read()
#print html
hp = MyHTMLParser()
hp.feed(html)
hp.close()
#print(hp.links)
f = file(path,"wb")
# for link in hp.links:
# 	f.write(link)
# 	f.write("\r\n")
first_url = 'http://www.gmba.ws' + hp.links[0]
#f.write(HandleUrltoHtml(first_url))
first_html = HandleUrltoHtml(first_url)
FindLastPage(first_html)


f.close()