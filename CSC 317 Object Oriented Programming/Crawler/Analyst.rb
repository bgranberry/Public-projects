class Analyst
	def initialize 
		@local_histrograms = Hash.new
		@global_histogram = Hash.new(0)
		@output = File.open("out_test.txt", "w")
	end

	def analyze doc
		current_page = Page_histogram.new doc
		@local_histrograms[current_page.page] = current_page.histogram

		current_page.histogram.keys.each { |word| @global_histogram[word] += current_page.histogram[word]}

		# @output << @local_histrograms.values
		@output << @global_histogram
	end
end