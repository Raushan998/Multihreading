require 'thread'

count = 0
threads = []

def output(num)
    sleep 1
    puts num
end

start = Time.now
(1..10).each do |num|
   threads << Thread.new { output(num) }
end
threads.each(&:join)

diff = Time.now.to_f - start.to_f
puts "#{diff} seconds to complete."