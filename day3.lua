print("AOC 2024 - day 3")
local function read_input()
    io.input("day3.input")
    return io.read("a")
end

sum = 0
for a, b in string.gmatch(read_input(), "mul%((%d?%d?%d),(%d?%d?%d)%)") do
    sum = sum + (math.tointeger(a) * math.tointeger(b))
end
print(sum)
