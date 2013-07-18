#!/usr/bin/env ruby

require 'chunky_png'

@palette = ChunkyPNG::Image.from_file('palette.png')
@png = ChunkyPNG::Image.from_file('nightscene.png')

@output = []

@map = []

(0..7).each do |c|
	(0..7).each do |d|
		(0..3).each do |a|
			x = (c*4) + a
			y = d

			offset = c*32

			col = offset + (4*d) + a

			idx = y + (x*8)

			@map[idx] = col.to_i
		end
	end
end

#puts @map

@png.pixels.each do |pixel|
	col = @map[@palette.pixels.index(pixel)]
	@output << "0x" + col.to_s(2).rjust(8,"0")
end	

p @output.join(',')