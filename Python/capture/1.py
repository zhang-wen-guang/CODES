#coding:utf-8

import sys
import os
import urllib
import urllib2
import re
import threadpool
from bs4 import BeautifulSoup

#def downloadImageFromLastPic(url)

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
big_page_urls.append('http://www.gmba.ws/guomoba/guomosipai/index.html')
for index in range(2, 30):
    page = str(index)
    cur_url = 'http://www.gmba.ws/guomoba/guomosipai/' + page + '.html'
    big_page_urls.append(cur_url)

def getUrlsInBigPage(url):
    groups = []
    html = urllib.urlopen(url).read()
    soup = BeautifulSoup(html)
    group_list = soup.find_all('a', target="_blank", href=re.compile("guomosipai"))
    for node in group_list:
        url = 'http://www.gmba.ws' + node["href"]
        title = node['title']
        one_group = OneGroupPic(url, title)
        groups.append(one_group)
    return groups

def getLastUrl(url):
    html = urllib.urlopen(url).read()
    soup = BeautifulSoup(html)
    last = soup.find('a', class_='a1', text='下一页')
    last = last.previous_sibling.previous_sibling
    last = 'http://www.gmba.ws' + last['href']
    return last

def getLastPic(url):
    html = urllib.urlopen(url).read()
    soup = BeautifulSoup(html)
    pics = soup.find_all('img', src=re.compile("\d+.jpg"))
    return pics[len(pics) - 1]['src']

def myUrlretrieve(arg):
    urllib.urlretrieve(arg.url, arg.filename)

def downLoadImg(url, path):
    sp = url.split('/')
    total = int(sp[7].split('.')[0]) + 1
    del sp[7]
    prefix = "/".join(sp)
    arg_list = []
    for i in range(1, total):
        if (i < 10):
            picurl = prefix +"/0"+str(i)+".jpg"
        else:
            picurl = prefix +"/"+str(i)+".jpg"
        filename = path + str(i) + ".jpg"
        arg = threadArg(picurl, filename)
        arg_list.append(arg)
    pool = threadpool.ThreadPool(10)
    reqs = threadpool.makeRequests(myUrlretrieve, arg_list)
    [ pool.putRequest(req) for req in reqs ]
    pool.wait()


for big_page in big_page_urls:
    groups = getUrlsInBigPage(big_page)
    for group in groups:
        last_url = getLastUrl(group.url)
        path = os.getcwd() + '\\' + group.title + '\\'
        os.makedirs(path)
        last_pic = getLastPic(last_url)
        downLoadImg(last_pic, path)
