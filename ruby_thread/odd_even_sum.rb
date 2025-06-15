# require 'thread'
require 'parallel'

def calculate_odd_sum start_ptr, end_ptr
  sum = 0
  while start_ptr <= end_ptr
    sum += start_ptr if start_ptr.odd?
    start_ptr += 1
  end
  
  sum
end

def calculate_even_sum start_ptr, end_ptr
  sum = 0
  while start_ptr <= end_ptr
    sum += start_ptr if start_ptr.even?
    start_ptr+=1 
  end
  sum
end


start_ptr, end_ptr = 0, 1000000009
current_time = Time.now

# results = Parallel.map([:odd, :even], in_processes: 2) do |type|
#   if type == :odd
#     calculate_odd_sum(start_ptr, end_ptr)
#   else
#     calculate_even_sum(start_ptr, end_ptr)
#   end
# end

# odd_sum, even_sum = results
# puts "Odd Sum: #{odd_sum}"
# puts "Even Sum: #{even_sum}"
# puts "Duration: #{Time.now - current_time}"
# start_ptr,end_ptr = 0, 10000009
# current_time = Time.now
odd_sum = calculate_odd_sum(start_ptr, end_ptr)
even_sum = calculate_even_sum(start_ptr, end_ptr)
# # t1 = Thread.new{ calculate_odd_sum(start_ptr, end_ptr) }
# # t2 = Thread.new{ calculate_even_sum(start_ptr, end_ptr) }
# # t1.join
# # t2.join
# # odd_sum = t1.value
# # even_sum = t2.value
after_time = Time.now
puts "Odd Sum: #{odd_sum}"
puts "Even Sum: #{even_sum}"
puts "Duration: #{(after_time-current_time).to_f.round(2)}"
