#==========================================================================================
#Name        :  webscraper.py
#Author      :  cdsoftw
#Version     :  1.0
#Course      :  CSCE 4430.001
#Description :  This python script uses the BeautifulSoup4 and requests libraries to return
#               the 10 most recent top stories from http://www.technewsworld.com/ in the
#               following format: title, date, URL. 
#Copyright   :  Copyright 2016 CDSoftworks ( AMDG )
#==========================================================================================

import requests
import bs4

#open webpage for scraping
response = requests.get('http://www.technewsworld.com/')
soup = bs4.BeautifulSoup(response.text, "html.parser")

#containers
titles = []
dates = []
urls = []

#find top 10 stories, append titles to list
for i in soup.find_all(class_='title')[:10]:
    titles.append(i.text.strip())
    
#append each story's date to list    
for i in soup.find_all(class_='date')[:10]:
    dates.append(i.text.strip())

#append each story's link to list
for i in soup.find_all(class_='title')[:10]:
    urls.append('http://www.technewsworld.com' + i.find('a')['href'])

count = 1
for i, j, k in zip(dates, titles, urls):
    print count, " - ", i, " - ", j, " - ", k
    count += 1