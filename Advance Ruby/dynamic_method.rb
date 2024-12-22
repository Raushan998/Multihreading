class User
    ACTIVE = 0
    INACTIVE = 1
    attr_accessor :status

    [:active, :inactive].each do |method|
        define_method method do |&block|
            block.call if block
            status == User.const_get(method.upcase) 
        end
    end
end

block = proc { puts "Hello World"}
user = User.new
user.status = 1
puts user.active { puts "Hello World"}
puts user.inactive
puts user.status