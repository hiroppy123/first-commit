class Student
    attr_accessor :name, :age, :birthdate, :state

    def initialize(name, age, birthdate, state)
        @name = name
        @age = age
        @birthdate = birthdate
        @state = state
    end

    def to_s
        "#{name} #{age} #{birthdate} #{state}"
    end
end

n, k = gets.chomp.split.map(&:to_i)

class_list = []
n.times do
    name, age, birthdate, state = gets.chomp.split
    class_list << Student.new(name, age.to_i, birthdate, state)
end

k.times do
    index, new_name = gets.chomp.split
    class_list[index.to_i - 1].name = new_name
end

class_list.sort_by! { |student| student.name.to_i }

puts class_list
