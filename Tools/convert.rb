#!/usr/bin/env ruby

require 'chunky_png'

@palette = ChunkyPNG::Image.from_file('palette.png')
@png = ChunkyPNG::Image.from_file('nightscene.png')

@output = []

@png.pixels.each do |pixel|
	@output << "0x" + @palette.pixels.index(pixel).to_s(2).rjust(8,"0")
end	

p @output.join(',')
