def user_method(&block)
    user = "Raushan"
    block.call(user) if block
end

user_method {|user| puts user }