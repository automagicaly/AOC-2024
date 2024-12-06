print("AOC 2024 - day 3")
local function read_input()
    io.input("day3.input")
    return io.read("a")
end

sum = 0
input = read_input()
print(input .. "\n\n")
input = regex_replace(input, "don't\\(\\).*?do\\(\\)", "do()")
print(input)
for a, b in string.gmatch(input, "mul%((%d?%d?%d),(%d?%d?%d)%)") do
    sum = sum + (math.tointeger(a) * math.tointeger(b))
end
print(sum)
