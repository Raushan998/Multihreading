require 'thread'
require 'faker'

class Person
    attr_reader :gender, :name
    def initialize(gender, name)
        @gender = gender
        @name = name
    end
end


class Bathroom
    MAX_CAPACITY = 3

    def initialize
        @counter = 0
        @current_gender = nil
        @mutex = Mutex.new
        @cond = ConditionVariable.new
    end

    def male_use_bathroom(person)
        enter!(:male, person)
        leave!(:male, person)
    end

    def female_use_bathroom(person)
        enter!(:female, person)
        leave!(:female, person)
    end

    private

    def enter!(gender, person)
        @mutex.synchronize do
            @cond.wait(@mutex) while 
            (@counter == MAX_CAPACITY) || 
            (@current_gender != gender && @current_gender)
            @counter += 1
            @current_gender = gender
            puts "#{person.name} is #{person.gender} who is using the bathroom  and also the counter is #{@counter}"
        end

        sleep(rand(0.1..0.5))
    end

    def leave!(gender, person)
        # sleep(rand(1..5)*0.2)
        @mutex.synchronize do
            @counter -= 1
            puts "#{person.name} is #{person.gender} who has left the bathroom and also the counter is #{@counter}"
            if @counter == 0
                @current_gender = nil
                @cond.broadcast
            else
                @cond.signal
            end
        end
    end
end



bathroom = Bathroom.new
male    = Person.new(:male,   "Joe")
female  = Person.new(:female, "Jane")

threads = []

# spawn a mix of 8 people arriving
100.times do |i|
  threads << Thread.new do
    if i.even?
      bathroom.male_use_bathroom(male)
    else
      bathroom.female_use_bathroom(female)
    end
  end
end

threads.each(&:join)