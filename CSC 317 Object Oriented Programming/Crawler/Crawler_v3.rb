require 'rubygems'
require 'nokogiri'  
require 'open-uri' 
#require_relative 'Analyst.rb'

class Crawler

	def initialize

		@total_links = []
		@links_visited = []
		@output = File.open("out.txt", "w")
		#@output2 = File.open("out2.txt", "w")
		# @analyst = Analyst.new 
		@count = 0
	end	

	def print_links
		@total_links.each do |link|
			@output << link << "\n"
		end
	end


	def crawl target
		if not @links_visited.include? target

			# log activity
			@output << "Crawling: (#{target}) \n"
			puts "Crawling: (#{target})"

			# add the target to links visited
			@links_visited << target

			# open page
			page = Nokogiri::HTML(open(target))
			
			# log text into histograms
			#doesnt work yet
			# @analyst.analyze page

			page_links = page.css('a')
			science_links = []
			child_links = []

			# grabs all links and puts them into total_links
			page_links.each do |link|
				if  link['href'] =~ /((^\/science-technology\/).*)|(.*(www.usm.edu)(\/science-technology\/).*)/
					science_links << link['href']
				end
			end
			
			# makes sure each URI is an absolute URI
			science_links.each do |link|
				if link =~ /(http:\/\/www.usm.edu)\/science-technology.*/
					child_links.push(link)
				else 
					link = "http://www.usm.edu" + link
					child_links.push(link)
				end
			end

			# remove duplicate links
			child_links.uniq!

			# child links contains all unique links on the page
			child_links.each do |link|
				crawl(link)
			end
		end
	end
end


c = Crawler.new

c.crawl "http://www.usm.edu/science-technology"

c.print_links