class BplusTree
    def initialize(degree = 3)
        @degree = degree
        @right = nil
        @left = nil
        @root = nil
        @right_ptr = nil
    end

    def add(element)
        @root = element unless @root
        shift_element(element)
    end

    def shift_element(element)
    end
end