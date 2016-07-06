#coding:utf-8

import sys
import os
import urllib
import urllib2
import threading
import re
import thread
from bs4 import BeautifulSoup

reload(sys)
sys.setdefaultencoding("utf-8")

class foo(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.url = url
        self.path = path

    def run(self):
        handleSmallPage(self.url, self.path)


big_pages = []
big_pages.append("http://www.guomoba.org/guomoba/guomosipai/")
for i in range(2, 37):
    cur_url = 'http://www.guomoba.org/guomoba/guomosipai/' + str(i) + '.html'
    big_pages.append(cur_url)

def openUrl(url):
    flag = 0
    while flag == 0:
        try:
            html = urllib.urlopen(url)
            flag = 1
        except:
            ""
    page = BeautifulSoup(html, "html.parser")
    return page

def downPic(url, filename):
    flag = 0
    while 0 == flag :
        try :
            urllib.urlretrieve(url, filename)
            flag = 1
        except:
            ""

def mkdir(dir):
    try :
        os.mkdir(dir)
    except:
        dir_split = dir.split('/')
        dir_split.pop()
        dir_split.pop()
        dir = '/'.join(dir_split)
        dir += '/'
        if (dir != './') : mkdir(dir)

def handleBigPage(url):
    soup = openUrl(url)
    groups = soup.find_all("a", target="_blank")
    count = 1
    for group in groups:
        img = group.img
        if group.img == None : continue
        # print group.img
        print count
        count += 1

        href = group['href'].strip()
        print href

        dirs = href.split('/')
        year = dirs[3]
        day = dirs[4]
        num = dirs[5].split('.')[0]
        # print dirs
        # print year
        # print day
        # print num
        new_dir = "./" + year + "/" + day + "/" + num + "/"
        print new_dir
        mkdir(new_dir)

        title = group['title'].strip()
        print title

        slt_img_url = img['src'].strip()
        print slt_img_url

def handleSmallPage(url, path):
    soup = openUrl(url)

    last = soup.find('a', class_='a1', text='下一页')
    last = last.previous_sibling.previous_sibling
    lastUrl = 'http://www.guomoba.org' + last['href']
    print lastUrl

    last_page = openUrl(lastUrl)
    pics = last_page.find_all('img', src=re.compile("\d+.jpg"))
    lastPic = pics[len(pics) - 1]['src']
    print lastPic

    lastPicSplit = lastPic.split('/')
    count = int(lastPicSplit.pop().split('.')[0])
    picPreUrl = '/'.join(lastPicSplit) + '/'
    for i in range(1, count + 1):
        if i < 10 :
            curPic = picPreUrl + '0' + str(i) + '.jpg'
        else :
            curPic = picPreUrl + str(i) + '.jpg'
        cur_name = path + str(i) + '.jpg'
        downPic(curPic, cur_name)
        # print curPic
        # print cur_name


handleBigPage("http://www.guomoba.org/guomoba/guomosipai/")
#handleSmallPage('http://www.guomoba.org/guomoba/guomosipai/2016/0523/1659.html', './2016/0523/1659/')
