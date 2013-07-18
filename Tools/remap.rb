#!/usr/bin/env ruby

map = []

(0..7).each do |c|
	(0..7).each do |d|
		(0..3).each do |a|
			x = (c*4) + a
			y = d

			offset = c*32

			col = offset + (4*d) + a

			idx = y + (x*8)

			map[idx] = '0x' + col.to_s(2).rjust(8,'0')
		end
	end
end

puts map.join(',')

