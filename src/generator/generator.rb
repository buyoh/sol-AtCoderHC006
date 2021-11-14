N = 10
C = 100
puts "#{N} #{C}"
puts N.times.map { [rand(10..99), rand(10..50)].join(' ') }
