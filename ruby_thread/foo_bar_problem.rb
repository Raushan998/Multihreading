require 'thread'

class PrintFooBar
  def initialize(n)
    @n = n
    @mutex = Mutex.new
    @cond = ConditionVariable.new
    @foo_turn = false
  end
  
  def print_foo
    print "Foo\n"
  end
  
  def print_bar
    print "Bar\n"
  end
  
  def foo
      @n.times{
        # puts "Hello World -- Foo"
        @mutex.synchronize  do
          @cond.wait(@mutex) if @foo_turn
          print_foo
          @foo_turn = true
          @cond.signal
        end
      }
  end
  
  def bar
    @n.times{
        # puts "Hello World -- Bar"
        @mutex.synchronize  do
          @cond.wait(@mutex) unless @foo_turn
          print_bar
          @foo_turn = false
          @cond.signal
        end
    }
  end
end

foo_bar = PrintFooBar.new(3)
t1 = Thread.new { foo_bar.foo }
t2 = Thread.new { foo_bar.bar }

t1.join
t2.join