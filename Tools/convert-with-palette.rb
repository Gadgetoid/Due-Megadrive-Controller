#!/usr/bin/env ruby

require 'chunky_png'

@palette = ChunkyPNG::Image.from_file('palette.png')
@png = ChunkyPNG::Image.from_file('sonic_left.png')

@index = [0xe3,0x24,0x07,0x06,0x01,0xff,0xe4,0xb6,0xfe,0x6d,0xa0,0x88,0xf5,0xcc,0xf8,0xf0]

@output = ''

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
	#puts pixel
	col = @map[@palette.pixels.index(pixel)]
	#@output << "0b" + col.to_s(2).rjust(8,"0")
	col = @index.index(col)

	@output << col.to_s(2).rjust(4,"0")

	#@output << col
end	

@new_output = []

@output.split('').each_slice(8) do |slice|

	@new_output <<  '0x' + slice.join.to_i(2).to_s(16).rjust(2,'0')
	#@new_output << "\t" + slice.join(',')

end

@final_output = []

@new_output.each_slice(17) do |slice| 
	@final_output << slice.join(',')
end

puts 'static unsigned char my_graphic_name[' + @new_output.length.to_s + "] = {\n" + @final_output.join(",\n") + '};'