#!/usr/bin/env ruby

require 'chunky_png'

@palette = ChunkyPNG::Image.from_file('palette.png')
@png = ChunkyPNG::Image.from_file('sonic.png')

@output = []

@map = []

(0..7).each do |c|
	(0..7).each do |d|
		(0..3).each do |a|
			x = (c*4) + a
			y = d

			offset = c*32

			col = offset + (4*d) + a

			idx = (y*32) + x

			@map[idx] = col.to_i
		end
	end
end

#puts @map

@png.pixels.each do |pixel|
	col = @map[@palette.pixels.index(pixel)]
	#@output << "0b" + col.to_s(2).rjust(8,"0")
	@output << "0x" + col.to_s(16).rjust(2,"0")

	#@output << col
end	

@new_output = []

@output.each_slice(32) do |slice|

	@new_output << "\t" + slice.join(',')

end

puts 'static unsigned char my_graphic_name[' + @output.length.to_s + "] = {\n\t" + @new_output.join(",\n") + '};'