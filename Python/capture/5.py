#coding:utf-8

import sys
import os
import urllib
import urllib2
import re
import thread
from bs4 import BeautifulSoup


class OneGroupPic:
    def __init__(self, url, title):
        self.url = url
        self.title = title

class threadArg:
    def __init__(self, url, filename):
        self.url = url
        self.filename = filename

#每个大页面的url，每个大页面中包含很多组图
big_page_urls = []
big_page_urls.append('http://www.ggba.pw/guomoba/guomosipai/index.html')
for index in range(2, 36):
    page = str(index)
    cur_url = 'http://www.ggba.pw/guomoba/guomosipai/' + page + '.html'
    big_page_urls.append(cur_url)

"""
for url in big_page_urls:
    print url
"""

#得到每个大页面中的小页面的入口
def getUrlsInBigPage(url):
    groups = []
    html = urllib.urlopen(url).read()
    soup = BeautifulSoup(html)
    group_list = soup.find_all('a', target="_blank", href=re.compile("guomosipai"))
    for node in group_list:
        url = 'http://www.ggba.pw' + node["href"]
        title = node['title']
        one_group = OneGroupPic(url, title)
        groups.append(one_group)
    return groups

"""
cur_big_url = "http://www.ggba.pw/guomoba/guomosipai/20.html"
cur_group = getUrlsInBigPage(cur_big_url)
for group in cur_group:
    print group.title
    print group.url
"""

def getLastUrl(url):
    html = urllib.urlopen(url).read()
    soup = BeautifulSoup(html)
    last = soup.find('a', class_='a1', text='下一页')
    last = last.previous_sibling.previous_sibling
    last = 'http://www.ggba.pw' + last['href']
    return last

"""
cur_gate = "http://www.ggba.pw/guomoba/guomosipai/2015/0427/705.html"
last = getLastUrl(cur_gate);
print last
"""

def getLastPic(url):
    html = urllib.urlopen(url).read()
    soup = BeautifulSoup(html)
    pics = soup.find_all('img', src=re.compile("\d+.jpg"))
    return pics[len(pics) - 1]['src']

"""
cur_page = "http://www.ggba.pw/guomoba/guomosipai/2015/0427/705_56.html"
print getLastPic(cur_page)
"""

def myUrlretrieve(url, filename):
    urllib.urlretrieve(url, filename)

def downLoadImg(url, path):
    sp = url.split('/')
    total = int(sp[7].split('.')[0]) + 1
    del sp[7]
    prefix = "/".join(sp)
    arg_list = []
    for i in range(1, total):
        if (i < 10):
            picurl = prefix + '/0' + str(i) + '.jpg'
        else:
            picurl = prefix + str(i) + '.jpg'
        filename = path + str(i) + '.jpg'
#thread.start_new_thread(myUrlretrieve, (picurl, filename, ))
        urllib.urlretrieve(picurl, filename)

"""
path = "/Users/ZWG/CODES/Python/capture/out/"
page_url = "http://photo.ggba.pw/uploadfile/2015/0427/05/112.jpg"
downLoadImg(page_url, path)
"""

for big_page in big_page_urls:
    groups = getUrlsInBigPage(big_page)
    for group in groups:
        last_url = getLastUrl(group.url)
        path = os.getcwd() + '\\' + group.title + '\\'
        os.makedirs(path)
        last_pic = getLastPic(last_url)
        downLoadImg(last_pic, path)
